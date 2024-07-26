#include <stdio.h>
#include <stdio_ext.h>

#include "dbg.h"

#define MAX_DATA 10

typedef enum EyeColor {
  BLUE_EYES,
  GREEN_EYES,
  BROWN_EYES,
  BLACK_EYES,
  OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {"Blue", "Green", "Brown", "Black", "Other"};

typedef struct Person {
  int age;
  float income;
  EyeColor eyes;
  char first_name[MAX_DATA];
  char last_name[MAX_DATA];
} Person;

int main() {
  Person you;

  memset(you.first_name, -1, sizeof(you.first_name));
  memset(you.last_name, -1, sizeof(you.first_name));

  char *in = NULL;

  printf("What's your first name? ");
  in = fgets(you.first_name, MAX_DATA, stdin);
  __fpurge(stdin);
  if (in == NULL) printf("\n");
  check(in != NULL, "Failed to read first name.");

  if (you.first_name[MAX_DATA - 1] == 0) {
    you.first_name[MAX_DATA - 2] = '\n';
  }

  printf("What's your last name? ");
  in = fgets(you.last_name, MAX_DATA, stdin);
  __fpurge(stdin);
  if (in == NULL) printf("\n");
  check(in != NULL, "Failed to read last name.");

  if (you.last_name[MAX_DATA - 1] == 0) {
    you.last_name[MAX_DATA - 2] = '\n';
  }

  printf("How old are you? ");

  int rc = fscanf(stdin, "%d", &you.age);
  check(rc > 0, "You have to enter a number.");

  printf("What color are your eyes:\n");
  for (int i = 0; i <= OTHER_EYES; i++) {
    printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
  }
  printf("> ");

  int eyes;
  rc = fscanf(stdin, "%d", &eyes);
  check(rc > 0, "You have to enter a number.");

  you.eyes = --eyes;

  check(0 <= you.eyes && you.eyes <= OTHER_EYES,
        "Do it right, that's not an option.");

  printf("How much do you make an hour? ");
  rc = fscanf(stdin, "%f", &you.income);
  check(rc > 0, "Enter a floating point number.");

  printf("----- RESULTS -----\n");
  printf("First Name: %s", you.first_name);
  printf("Last Name: %s", you.last_name);
  printf("Age: %d\n", you.age);
  printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
  printf("Income: %.2f\n", you.income);

  return 0;
error:
  return 1;
}
