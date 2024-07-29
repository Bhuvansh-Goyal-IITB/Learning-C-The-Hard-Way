#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/dbg.h"
#include "vector.h"

VECTOR(char, string);
VECTOR(string *, buffer);

int load_config_file(FILE *fp, buffer *b) {
  string *line;
  int res = 0;

  res = create_string(&line);

  check(res == 0, "Failed to create string.");
  while (!feof(fp)) {
    char ch = fgetc(fp);
    if (ch != '\n') {
      res = string_push(line, ch);
      check(res == 0, "Failed to push into string.");
    } else {
      res = buffer_push(b, line);
      check(res == 0, "Failed to push into buffer.");
      create_string(&line);
      check(res == 0, "Failed to create string.");
    }
  }

  if (line->arr) free(line->arr);
  free(line);
  return 0;
error:
  if (line->arr) free(line->arr);
  free(line);
  return -1;
}

void destroy_buffer(buffer *b) {
  if (b == NULL) return;

  for (int i = 0; i < b->size; i++) {
    string *curr;
    buffer_at(b, i, &curr);

    if (curr->arr) free(curr->arr);
    free(curr);
  }

  if (b->arr) free(b->arr);
  free(b);
}

int main() {
  FILE *fp = NULL;
  int res = 0;

  const char *home_dir = getenv("HOME");
  const char *file = "/.logfind";

  buffer *config_buffer;
  res = create_buffer(&config_buffer);
  check(res == 0, "Failed to create buffer.");

  char *logfind_path =
      calloc(1, (strlen(home_dir) + strlen(file) + 1) * sizeof(char));
  check_mem(logfind_path);

  strcpy(logfind_path, home_dir);
  strcat(logfind_path, file);

  fp = fopen(logfind_path, "r");
  check(fp != NULL, "Could'nt open %s", logfind_path);

  res = load_config_file(fp, config_buffer);
  check(res == 0, "Failed to load %s", logfind_path);

  destroy_buffer(config_buffer);
  free(logfind_path);
  fclose(fp);
  return 0;
error:
  destroy_buffer(config_buffer);
  if (logfind_path) free(logfind_path);
  if (fp) fclose(fp);
  return 1;
}
