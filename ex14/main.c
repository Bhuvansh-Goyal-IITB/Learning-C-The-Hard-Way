#include <ctype.h>
#include <stdio.h>

int can_print_it(char);
void print_letters(char[]);

void print_arguments(int argc, char* argv[]) {
  for (size_t i = 0; i < argc; i++) {
    print_letters(argv[i]);
  }
}

void print_letters(char word[]) {
  for (size_t i = 0; word[i] != '\0'; i++) {
    char letter = word[i];

    if (can_print_it(letter)) {
      printf("'%c' == %d, ", letter, letter); 
    }
  }

  printf("\n");
}

int can_print_it(char ch) {
  return isalpha(ch) || isblank(ch);
}

int main(int argc, char* argv[]) {
  print_arguments(argc, argv);
  return 0;
}
