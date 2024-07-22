#include <stdio.h>

int main(int argc, char *argv[]) {
  int ages[] = {20, 17, 12, 10};
  char *names[] = {"Krishna", "Pankaj", "Anupam", "Vihaan"};

  int count = sizeof(ages) / sizeof(int);
  int i = 0;

  for (i = 0; i < count; i++) {
    printf("%s is %d years old\n", names[i], ages[i]);
  }

  printf("---\n");

  int *cur_age = ages;
  char **cur_name = names;

  for (i = 0; i < count; i++) {
    printf("%s is %d years old\n", *(cur_name + i), *(cur_age + i));
  }

  printf("---\n");

  for (i = 0; i < count; i++) {
    printf("%s is %d years old\n", cur_name[i], cur_age[i]);
  }

  printf("---\n");

  for (cur_age = ages, cur_name = names; (cur_age - ages) < count;
       cur_name++, cur_age++) {
    printf("%s is %d years old\n", *cur_name, *cur_age);
  }

  return 0;
}
