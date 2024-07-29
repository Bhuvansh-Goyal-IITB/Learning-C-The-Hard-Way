#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../common/dbg.h"

int main() {
  FILE *fp;

  const char *home_dir = getenv("HOME");
  const char *file = "/.logfind";

  char *logfind_path =
      calloc(1, (strlen(home_dir) + strlen(file) + 1) * sizeof(char));

  strcpy(logfind_path, home_dir);
  strcat(logfind_path, file);

  fp = fopen(logfind_path, "r");
  check(fp != NULL, "Could'nt open %s", logfind_path);

  free(logfind_path);
  fclose(fp);
  return 0;
error:
  if (logfind_path) free(logfind_path);
  if (fp) fclose(fp);
  return 1;
}
