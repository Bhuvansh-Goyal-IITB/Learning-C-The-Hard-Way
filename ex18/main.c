#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*compare_cb)(int, int);

void die(const char *message) {
  if (errno) {
    perror(message);
  } else {
    printf("ERROR: %s\n", message);
  }

  exit(1);
}

int *bubble_sort(int *numbers, int count, compare_cb compare) {
  int *output = malloc(sizeof(int) * count);
  if (!output) {
    die("Memory Error.");
  }

  memcpy(output, numbers, sizeof(int) * count);

  for (int i = 0; i < count; i++) {
    for (int j = 0; j < count - 1; j++) {
      if (compare(output[j], output[j + 1]) > 0) {
        int temp = output[j + 1];
        output[j + 1] = output[j];
        output[j] = temp;
      }
    }
  }

  return output;
}

void test_sorting(int *numbers, int count, compare_cb compare) {
  int *sorted = bubble_sort(numbers, count, compare);

  if (!sorted) {
    die("Failed to sort using the given function.");
  }

  for (int i = 0; i < count; i++) {
    printf("%d ", sorted[i]);
  }
  printf("\n");

  free(sorted);
}

int sorted_order(int a, int b) { return a - b; }
int reverse_order(int a, int b) { return b - a; }
int strange_order(int a, int b) {
  if (a == 0 || b == 0) {
    return 0;
  } else {
    return a % b;
  }
}

int main(int argc, char *argv[]) {
  if (argc < 2) {
    printf("USAGE: %s 1 2 ...\n", argv[0]);
    return 1;
  }

  int count = argc - 1;

  int *numbers = malloc(count * sizeof(int));
  if (!numbers) {
    die("Memory Error.");
  }

  for (int i = 0; i < count; i++) {
    numbers[i] = atoi(argv[i + 1]);
  }

  test_sorting(numbers, count, sorted_order);
  test_sorting(numbers, count, reverse_order);
  test_sorting(numbers, count, strange_order);

  free(numbers);

  return 0;
}
