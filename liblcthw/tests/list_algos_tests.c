// clang-format off
#include "minunit.h"
// clang-format on

#include <list_algos.h>

char* values[] = {"bbcc", "xXXX", "1234", "abcd", "xjvef",
                  "NDSS", "acdd", "jvef", "SS",   "uga"};

#define NUM_VALUES 10

List* create_words() {
  List* words = List_create();
  check(words != NULL, "List creation failed.");

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
  check(words != NULL, "Creation of words list failed.");

  int rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort failed.");
  mu_assert(words != NULL, "Bubble sort made the list NULL.");
  mu_assert(words->count == NUM_VALUES,
            "Number or elements after bubble sort is different.");
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "Words are not sorted after bubble sort.");

  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort of already sorted failed.");
  mu_assert(words != NULL, "Bubble sort made the list NULL.");
  mu_assert(words->count == NUM_VALUES,
            "Number or elements after bubble sort is different.");
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "Words should be sort if already bubble sorted.");

  List_destroy(words);

  words = List_create();
  rc = List_bubble_sort(words, (List_compare)strcmp);
  mu_assert(rc == 0, "Bubble sort failed on empty list.");
  mu_assert(words != NULL, "Bubble sort made the list NULL.");
  mu_assert(words->count == 0,
            "Number or elements after bubble sort is different.");
  mu_assert(List_is_sorted(words, (List_compare)strcmp) == 1,
            "Words should be sorted if empty.");

error:
  List_destroy(words);
  return;
}

void test_merge_sort() {
  List* words = create_words();
  List* res = NULL;
  List* res2 = NULL;

  check(words != NULL, "Creation of words list failed.");

  res = List_merge_sort(words, (List_compare)strcmp);
  mu_assert(res != NULL, "Merge sort made the list NULL.");
  mu_assert(res->count == NUM_VALUES,
            "Number or elements after merge sort is different.");
  mu_assert(List_is_sorted(res, (List_compare)strcmp) == 1,
            "Words are not sorted after merge sort.");

  res2 = List_merge_sort(res, (List_compare)strcmp);
  mu_assert(res2 != NULL, "Merge sort made the list NULL.");
  mu_assert(res2->count == NUM_VALUES,
            "Number or elements after merge sort is different.");
  mu_assert(List_is_sorted(res2, (List_compare)strcmp) == 1,
            "Should still be sorted after merge sort.");
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
