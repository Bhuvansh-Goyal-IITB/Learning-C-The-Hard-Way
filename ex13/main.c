#include <stdio.h>

int main(int argc, char* argv[]) {
  int i = 0;
  int y = 1;

  for (i = 1; i < argc; i++) {
    printf("arg %d: %s\n", i, argv[i]);
  }

  char* states[] = { "Gujarat", "Maharashtra", "Uttar Pradesh", "Rajasthan" };

  printf("address of char*: %p\n", states);
  printf("size of char*: %ld\n", sizeof(char*));
  int num_states = sizeof(states) / sizeof(char*);

  for (i = 0; i < num_states; i++) {
    printf("state %d: %s\n", i, states[i]);
  }

  return 0;
}
