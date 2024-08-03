#include <stdio.h>

#include "../common/colorprint.h"
#include "bit_buffer.h"
#include "file.h"
#include "kmp.h"
#include "vector.h"

int load_line(FILE *fp, vc *s) {
  int res = 0;

  while (!feof(fp)) {
    char ch = fgetc(fp);
    if (ch != '\n' && ch != EOF) {
      res = vc_push(s, ch);
      check(res == 0, "Failed to push into vc.");
      continue;
    }
    break;
  }
  if (s->size > 0) {
    vc_push(s, '\0');
  }

  return 0;
error:
  return -1;
}

int load_config_file(char *file_path, vvc *b) {
  FILE *fp = NULL;

  vc *line = NULL;
  int res = 0;

  fp = fopen(file_path, "r");
  check(fp != NULL, "Failed to open file: %s", file_path);

  res = create_vc(&line);
  check(res == 0, "Failed to create string.");

  while (!feof(fp)) {
    res = load_line(fp, line);
    check(res == 0, "Failed to load line.");

    if (line->size > 0) {
      vvc_push(b, line);
    } else {
      vc_cleanup(line);
    }

    res = create_vc(&line);
    check(res == 0, "Failed to create string.");
  }

  if (fp) fclose(fp);
  vc_cleanup(line);
  return 0;
error:
  if (fp) fclose(fp);
  vc_cleanup(line);
  return -1;
}

void free_vbit_buffer_elements(vbit_buffer *v) {
  if (v == NULL) return;
  for (int i = 0; i < v->size; i++) {
    bit_buffer *b;
    vbit_buffer_at(v, i, &b);
    bit_buffer_cleanup(b);
  }
}

void free_vvc_elements(vvc *v) {
  if (v == NULL) return;
  for (int i = 0; i < v->size; i++) {
    vc *curr;
    vvc_at(v, i, &curr);
    vc_cleanup(curr);
  }
}

void color_print(vc *line, bit_buffer *color_mask) {
  int is_highlight_on = 1;
  if (is_set(color_mask, 0) == 1) {
    printf(BRIGHT_RED_ANSI);
    is_highlight_on = 1;
  }

  for (int i = 0; i < line->size - 1; i++) {
    int set_bit = is_set(color_mask, i);
    if (is_highlight_on == 1 && set_bit == 0) {
      printf(RESET);
      is_highlight_on = 0;
    } else if (is_highlight_on == 0 && set_bit == 1) {
      printf(BRIGHT_RED_ANSI);
      is_highlight_on = 1;
    }

    char ch;
    vc_at(line, i, &ch);
    printf("%c", ch);
  }
  printf(RESET);
  printf("\n");
}

int process_file(vc *file_name, char **search_strings, int search_strings_count,
                 int or_logic) {
  vvc *print_buffer = NULL;
  vbit_buffer *color_mask_buffer = NULL;
  bit_buffer *matched_buffer = NULL;

  FILE *fp = NULL;
  vc *line = NULL;

  bit_buffer *color_mask = NULL;

  int res = 0;

  res = create_vc(&line);
  check(res == 0, "Failed to create vc.");

  fp = fopen(file_name->arr, "r");
  check(fp != NULL, "Could'nt open %s", file_name->arr);

  if (or_logic == 0) {
    res = create_vvc(&print_buffer);
    check(res == 0, "Failed to create vvc.");

    res = create_vbit_buffer(&color_mask_buffer);
    check(res == 0, "Failed to create vbit_buffer.");

    res = create_bit_buffer(&matched_buffer, search_strings_count);
    check(res == 0, "Failed to create bit_buffer.");
  }

  while (!feof(fp)) {
    res = load_line(fp, line);
    check(res == 0, "Failed to load line.");

    if (line->size == 0) {
      vc_cleanup(line);

      res = create_vc(&line);
      check(res == 0, "Failed to create vc.");
      continue;
    }

    res = create_bit_buffer(&color_mask, line->size - 1);
    check(res == 0, "Failed to create bit buffer.");

    int any_match = 0;
    for (int i = 0; i < search_strings_count; i++) {
      res = kmp(color_mask, line, search_strings[i]);
      check(res >= 0, "Failed to do kmp.");

      if (res == 1) {
        any_match = 1;
        if (or_logic == 0) {
          set_bit(matched_buffer, i);
        }
      }
    }

    if (any_match == 1) {
      if (or_logic == 0) {
        vvc_push(print_buffer, line);
        vbit_buffer_push(color_mask_buffer, color_mask);
      } else {
        printf("%s:", file_name->arr);
        color_print(line, color_mask);

        vc_cleanup(line);
        bit_buffer_cleanup(color_mask);
      }
    } else {
      vc_cleanup(line);
      bit_buffer_cleanup(color_mask);
    }

    color_mask = NULL;
    res = create_vc(&line);
    check(res == 0, "Failed to create vc.");
  }

  if (or_logic == 0) {
    int all_matched = 1;
    for (int i = 0; i < matched_buffer->num_bits; i++) {
      if (is_set(matched_buffer, i) == 0) {
        all_matched = 0;
        break;
      }
    }

    if (all_matched == 1) {
      for (int i = 0; i < print_buffer->size; i++) {
        vc *curr_line;
        vvc_at(print_buffer, i, &curr_line);

        bit_buffer *curr_color_mask;
        vbit_buffer_at(color_mask_buffer, i, &curr_color_mask);

        printf("%s:", file_name->arr);
        color_print(curr_line, curr_color_mask);
      }
    }
  }

  if (fp) fclose(fp);
  vc_cleanup(line);
  bit_buffer_cleanup(color_mask);
  bit_buffer_cleanup(matched_buffer);

  free_vvc_elements(print_buffer);
  vvc_cleanup(print_buffer);

  free_vbit_buffer_elements(color_mask_buffer);
  vbit_buffer_cleanup(color_mask_buffer);
  return 0;
error:
  if (fp) fclose(fp);
  vc_cleanup(line);
  bit_buffer_cleanup(color_mask);
  bit_buffer_cleanup(matched_buffer);

  free_vvc_elements(print_buffer);
  vvc_cleanup(print_buffer);

  free_vbit_buffer_elements(color_mask_buffer);
  vbit_buffer_cleanup(color_mask_buffer);
  return -1;
}
