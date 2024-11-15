#include <assert.h>
#include <stdio.h>

#include "../common/dbg.h"

void copy(const char *from, char *to) {
  int i = 0;
  while ((to[i] = from[i]) != '\0') ++i;
}

int safecopy(int len_from, const char *from, int len_to, char *to) {
  assert(from != NULL && to != NULL && "from and to can't be NULL");

  if (len_from < 0 || len_to <= 0) {
    return -1;
  }

  int max = len_from > len_to - 1 ? len_to - 1 : len_from;

  int i = 0;
  for (; i < max; i++) {
    to[i] = from[i];
  }

  to[i] = '\0';
  return i;
}

int main(int argc, char **argv) {
  char from[] = "0123456789";
  int from_len = sizeof(from);

  char to[] = "0123456";
  int to_len = sizeof(to);

  debug("Copying from %s:%d to %s:%d", from, from_len, to, to_len);

  int rc = safecopy(from_len, from, to_len, to);
  check(rc > 0, "Safe copy failed!");
  check(to[to_len - 1] == '\0', "String not terminated");

  debug("Result is %s:%d", to, to_len);

  rc = safecopy(from_len * -1, from, to_len, to);
  check(rc == -1, "Safe copy shoud fail");
  check(to[to_len - 1] == '\0', "String not terminated");

  rc = safecopy(from_len, from, 0, to);
  check(rc == -1, "Safe copy shoud fail");
  check(to[to_len - 1] == '\0', "String not terminated");

  return 0;
error:
  return -1;
}
