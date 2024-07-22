#include <stdio.h>

int main() {
  int areas[] = { 10, 12, 13, 14 };
  char name[] = "Zed";
  char full_name[] = { 'Z', 'e', 'd', ' ', 'A', '.', ' ', 'S', 'h', 'a', 'w', '\0' };

  printf("The size of an in int: %ld\n", sizeof(int));
  printf("The size of an in areas: %ld\n", sizeof(areas));
  printf("The number of ints in areas: %ld\n", sizeof(areas) / sizeof(int));

  printf("The size of char: %ld\n", sizeof(char));
  printf("The size of name: %ld\n", sizeof(name));
  printf("The number of char in name: %ld\n", sizeof(name) / sizeof(char));

  printf("The size of full_name: %ld\n", sizeof(full_name));
  printf("The number of char in full_name: %ld\n", sizeof(full_name) / sizeof(char));

  printf("name=\"%s\", full_name=\"%s\"\n", name, full_name);

  return 0;
}
