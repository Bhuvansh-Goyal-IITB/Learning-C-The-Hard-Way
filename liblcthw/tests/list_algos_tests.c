// clang-format off
#include "minunit.h"
// clang-format on

#include <list_algos.h>

char* values[] = {"bbcc", "xXXX", "1234", "abcd", "xjvef",
                  "NDSS", "acdd", "jvef", "SS",   "uga"};

#define NUM_VALUES 10

List* create_words() {
  List* words = List_create();
  check(words != NULL, "failed to create List.");

  for (int i = 0; i < NUM_VALUES; i++) {
    int rc = List_push(words, values[i]);
    check(rc == 0, "List push failed.");
  }

  return words;
error:
  List_destroy(words);
  return NULL;
}

void test_bubble_sort() {
  List* words = create_words();
  check(words != NULL, "failed to create List.");

  int rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "bubble sort failed.");
  mu_assert(words != NULL, "List is NULL after bubble sort.");
  mu_assert(List_count(words) == NUM_VALUES,
            "incorrect List count after bubble sort, expected: %d, got: %lu.",
            NUM_VALUES, List_count(words));
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "List is not sorted after bubble sort.");

  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "bubble sort of already sorted List failed.");
  mu_assert(words != NULL, "List is NULL after bubble sort.");
  mu_assert(List_count(words) == NUM_VALUES,
            "incorrect List count after bubble sort, expected: %d, got: %lu.",
            NUM_VALUES, List_count(words));
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "already sorted List is not sorted after bubble sort.");

  List_destroy(words);

  words = List_create();
  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "bubble sort failed on empty List.");
  mu_assert(words != NULL, "List is NULL after bubble sort.");
  mu_assert(List_count(words) == 0,
            "incorrect List count after bubble sort, expected: %d, got: %lu.",
            0, List_count(words));
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "empty List is not sorted after bubble sort.");

error:
  List_destroy(words);
  return;
}

void test_merge_sort() {
  List* words = create_words();
  List* res = NULL;
  List* res2 = NULL;

  check(words != NULL, "failed to create List.");

  res = List_merge_sort(words, (List_compare)strcmp);
  mu_assert(res != NULL, "List is NULL after merge sort.");
  mu_assert(List_count(res) == NUM_VALUES,
            "incorrect List count after merge sort, expected: %d, got: %lu.",
            NUM_VALUES, List_count(res));
  mu_assert(List_is_sorted(res, (List_compare)strcmp) == 1,
            "List is not sorted after merge sort.");

  res2 = List_merge_sort(res, (List_compare)strcmp);
  mu_assert(res2 != NULL, "List is NULL after merge sort.");
  mu_assert(List_count(res2) == NUM_VALUES,
            "incorrect List count after merge sort, expected: %d, got: %lu.",
            NUM_VALUES, List_count(res2));
  mu_assert(List_is_sorted(res2, (List_compare)strcmp) == 1,
            "already sorted List is not sorted after merge sort.");
error:
  List_destroy(res2);
  List_destroy(res);
  List_destroy(words);

  return;
}

void all_tests() {
  mu_run_test(test_bubble_sort);
  mu_run_test(test_merge_sort);

error:
  return;
}

RUN_TESTS(all_tests);
