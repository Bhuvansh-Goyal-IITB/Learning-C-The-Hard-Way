#include <stdio.h>
#include <stdlib.h>

#include "../common/dbg.h"
#include "file.h"
#include "vector.h"

int get_config_file_path(char **config_file_path) {
  const char *home_dir = getenv("HOME");
  const char *file = "/.logfind";

  *config_file_path =
      (char *)calloc(1, (strlen(home_dir) + strlen(file) + 1) * sizeof(char));
  check_mem(config_file_path);

  strcpy(*config_file_path, home_dir);
  strcat(*config_file_path, file);

  return 0;
error:
  return -1;
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    log_err("USAGE: %s [-o for or logic] [search strings]", argv[0]);
    return 1;
  }

  int res = 0;

  vvc *config_buffer = NULL;
  char *config_file_path = NULL;

  res = create_vvc(&config_buffer);
  check(res == 0, "Failed to create config buffer.");

  res = get_config_file_path(&config_file_path);
  check(res == 0, "Failed to create config file path.");

  res = load_config_file(config_file_path, config_buffer);
  check(res == 0, "Failed to load %s", config_file_path);

  int or_logic = strcmp(argv[1], "-o") == 0 ? 1 : 0;

  char **search_strings = argv + 1;
  int search_strings_count = argc - 1;

  if (or_logic == 1) {
    search_strings++;
    search_strings_count--;
  }

  for (int i = 0; i < config_buffer->size; i++) {
    vc *file_name;
    vvc_at(config_buffer, i, &file_name);

    process_file(file_name, argv + 1, argc - 1, or_logic);
  }

  free_vvc_elements(config_buffer);
  vvc_cleanup(config_buffer);
  free(config_file_path);
  return 0;
error:
  free_vvc_elements(config_buffer);
  vvc_cleanup(config_buffer);
  if (config_file_path) free(config_file_path);
  return 1;
}
