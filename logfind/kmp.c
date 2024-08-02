#include <stdlib.h>
#include <string.h>

#include "bit_buffer.h"
#include "kmp.h"
#include "vector.h"

int generate_lps_array(int **lps, const char *str, int n) {
  *lps = (int *)calloc(1, n * sizeof(int));
  check_mem(lps);

  int i = 1, j = 0;
  while (i < n) {
    if (str[j] == str[i]) {
      (*lps)[i] = j + 1;
      ++j;
      ++i;
    } else {
      if (j > 0) {
        j = (*lps)[j - 1];
      } else {
        (*lps)[i] = 0;
        ++i;
      }
    }
  }

  return 0;
error:
  return -1;
}

int kmp(bit_buffer *color_mask, vc *line, const char *str) {
  int str_len = strlen(str);
  int res = 0;
  int matched = 0;

  if (str_len > line->size - 1) {
    return 0;
  }

  if (str_len == line->size - 1 && strcmp(str, line->arr) != 0) {
    return 0;
  }

  int *lps;
  res = generate_lps_array(&lps, str, str_len);
  check(res == 0, "Failed to generate lps array.");

  int i = 0, j = 0;
  while (i < line->size) {
    char ch;
    vc_at(line, i, &ch);

    if (ch == str[j]) {
      ++i;
      ++j;

      if (j == str_len) {
        j = lps[str_len - 1];
        set_range(color_mask, i - str_len, i - 1);
        matched = 1;
      }
    } else {
      if (j > 0) {
        j = lps[j - 1];
      } else {
        ++i;
      }
    }
  }
  if (lps) free(lps);
  return matched;
error:
  if (lps) free(lps);
  return -1;
}
