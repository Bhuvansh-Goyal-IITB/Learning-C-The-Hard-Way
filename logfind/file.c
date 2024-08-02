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

int process_file(vc *file_name, char **search_args, int search_args_count,
                 int or_logic) {
  vvc *print_buffer = NULL;
  vbit_buffer *color_mask_buffer = NULL;

  FILE *fp = NULL;
  vc *line = NULL;

  bit_buffer *color_mask = NULL;

  int res = 0;

  res = create_vc(&line);
  check(res == 0, "Failed to create vc.");

  fp = fopen(file_name->arr, "r");
  check(fp != NULL, "Could'nt open %s", file_name->arr);

  if (or_logic == 1) {
    res = create_vvc(&print_buffer);
    check(res == 0, "Failed to create vvc.");
    res = create_vbit_buffer(&color_mask_buffer);
    check(res == 0, "Failed to create vbit_buffer.");
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

    for (int i = 0; i < search_args_count; i++) {
      res = kmp(color_mask, line, search_args[i]);
      check(res >= 0, "Failed to do kmp.");

      if (res == 1) {
        printf("%s:%s\n", file_name->arr, line->arr);
      }
    }

    bit_buffer_cleanup(color_mask);
    color_mask = NULL;
    vc_cleanup(line);
    res = create_vc(&line);
    check(res == 0, "Failed to create vc.");
  }

  if (fp) fclose(fp);
  vc_cleanup(line);
  bit_buffer_cleanup(color_mask);

  free_vvc_elements(print_buffer);
  vvc_cleanup(print_buffer);

  free_vbit_buffer_elements(color_mask_buffer);
  vbit_buffer_cleanup(color_mask_buffer);
  return 0;
error:
  if (fp) fclose(fp);
  vc_cleanup(line);
  bit_buffer_cleanup(color_mask);

  free_vvc_elements(print_buffer);
  vvc_cleanup(print_buffer);

  free_vbit_buffer_elements(color_mask_buffer);
  vbit_buffer_cleanup(color_mask_buffer);
  return -1;
}
