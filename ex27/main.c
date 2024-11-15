#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

void copy(const char *from, char *to) {
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

int safecopy(int len_from, char *from, int len_to, char *to) {
	assert(from != NULL && to != NULL && "From and To can't be null");
	
  int max = len_from > len_to - 1 ? len_to - 1 : len_from;

  if (len_from < 0 || len_to <= 0) {
    return -1;
  }

  int i = 0;
  for (; i < max; i++) {
    to[i] = from[i];
  }

  to[i] = '\0';
  return i;
}

int main() {
  char str1[] = "Hello this is a string";
  char *str2 = calloc(1, 23);

  safecopy(23, str1, 23, str2);

  printf("%s\n", str2);
}
