// clang-format off
#include "minunit.h"
// clang-format on

#include <darray_algos.h>

int testcmp(char** a, char** b) { return strcmp(*a, *b); }

DArray* create_words() {
  DArray* result = DArray_create(0, 5);
  char* words[] = {"asdfasfd", "werwar", "13234", "asdfasfd", "oioj"};

  for (int i = 0; i < 5; i++) {
    int rc = DArray_push(result, words[i]);
    check(rc == 0, "array push failed.");
  }

  return result;
error:
  DArray_destroy(result);
  return NULL;
}

void run_sort_test(int (*func)(DArray*, DArray_compare), const char* name) {
  DArray* words = create_words();
  mu_assert(words != NULL, "failed to create words array.");
  mu_assert(DArray_is_sorted(words, (DArray_compare)strcmp) == 0,
            "words shouldn't be sorted at the start.");

  debug("--- Testing %s sorting algorithm", name);
  int rc = func(words, (DArray_compare)testcmp);
  mu_assert(rc == 0, "sort failed.");
  mu_assert(DArray_is_sorted(words, (DArray_compare)strcmp) == 1,
            "array is not sorted after %s", name);

error:
  DArray_destroy(words);
  return;
}

void test_qsort() { run_sort_test(DArray_qsort, "qsort"); }

void all_tests() {
  mu_run_test(test_qsort);
error:
  return;
}

RUN_TESTS(all_tests);
