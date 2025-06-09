// clang-format off
#include "minunit.h"
// clang-format on

#include <list.h>

static List* list = NULL;

char* test1 = "test1 data";
char* test2 = "test2 data";
char* test3 = "test3 data";

char* sorted_values[] = {"1", "a", "b", "c"};

#define NUM_SORTED_VALUES 4

void test_create() {
  list = List_create();
  mu_assert(list != NULL, "failed to create List.");

error:
  return;
}

void test_push_pop() {
  int rc = List_push(list, test1);
  mu_assert(rc == 0, "List push failed.");
  mu_assert(List_last(list) == test1,
            "incorrect last value after push, expected: %s, got: %s.", test1,
            (char*)List_last(list));

  rc = List_push(list, test2);
  mu_assert(rc == 0, "List push failed.");
  mu_assert(List_last(list) == test2,
            "incorrect last value after push, expected: %s, got: %s.", test2,
            (char*)List_last(list));

  rc = List_push(list, test3);
  mu_assert(rc == 0, "List push failed.");
  mu_assert(List_last(list) == test3,
            "incorrect last value after push, expected: %s, got: %s.", test3,
            (char*)List_last(list));
  mu_assert(List_count(list) == 3,
            "incorrect List count after push, expected: %d, got: %lu.", 3,
            List_count(list));

  char* val = List_pop(list);
  mu_assert(val == test3, "incorrect popped value, expected: %s, got: %s.",
            test3, val);

  val = List_pop(list);
  mu_assert(val == test2, "incorrect popped value, expected: %s, got: %s.",
            test2, val);

  val = List_pop(list);
  mu_assert(val == test1, "incorrect popped value, expected: %s, got: %s.",
            test1, val);

  mu_assert(List_count(list) == 0,
            "incorrect List count after pop, expected: %d, got: %lu.", 0,
            List_count(list));

error:
  return;
}

void test_unshift() {
  int rc = List_unshift(list, test1);
  mu_assert(rc == 0, "List unshift failed.");
  mu_assert(List_first(list) == test1,
            "incorrect first value after unshift, expected: %s, got: %s.",
            test1, (char*)List_first(list));

  rc = List_unshift(list, test2);
  mu_assert(rc == 0, "List unshift failed.");
  mu_assert(List_first(list) == test2,
            "incorrect first value after unshift, expected: %s, got: %s.",
            test2, (char*)List_first(list));

  rc = List_unshift(list, test3);
  mu_assert(rc == 0, "List unshift failed.");
  mu_assert(List_first(list) == test3,
            "incorrect first value after unshift, expected: %s, got: %s.",
            test3, (char*)List_first(list));

  mu_assert(List_count(list) == 3,
            "incorrect List count after unshift, expected: %d, got: %lu.", 3,
            List_count(list));

error:
  return;
}

void test_remove() {
  char* val = List_remove(list, list->first->next);
  mu_assert(val == test2, "incorrect removed value, expected: %s, got: %s.",
            test2, val);
  mu_assert(List_count(list) == 2,
            "incorrect List count after remove, expected: %d, got: %lu.", 2,
            List_count(list));

  mu_assert(List_first(list) == test3,
            "incorrect first value after remove, expected: %s, got: %s.", test3,
            (char*)List_first(list));

  mu_assert(List_last(list) == test1,
            "incorrect last value after remove, expected: %s, got: %s.", test1,
            (char*)List_last(list));

error:
  return;
}

void test_shift() {
  mu_assert(List_count(list) != 0,
            "incorrect List count before shift, expected: %d, got: %lu.", 2,
            List_count(list));

  char* val = List_shift(list);
  mu_assert(val == test3, "incorrect value on shift, expected: %s, got: %s.",
            test3, val);

  val = List_shift(list);
  mu_assert(val == test1, "incorrect value on shift, expected: %s, got: %s.",
            test1, val);

  mu_assert(List_count(list) == 0,
            "incorrect List count after shift, expected: %d, got: %lu.", 0,
            List_count(list));

error:
  return;
}

void test_insert_sorted() {
  mu_assert(
      List_count(list) == 0,
      "incorrect List count before insert_sorted, expected: %d, got: %lu.", 0,
      List_count(list));

  int rc = 0;

  for (int i = 0; i < NUM_SORTED_VALUES; i++) {
    List_push(list, sorted_values[i]);
  }

  mu_assert(List_count(list) == NUM_SORTED_VALUES,
            "incorrect List count after push, expected: %d, got: %lu.",
            NUM_SORTED_VALUES, List_count(list));

  rc = List_insert_sorted(list, "d", (List_compare)strcmp);
  check(rc == 0, "List insert_sorted failed.");

  check(List_count(list) == NUM_SORTED_VALUES + 1,
        "incorrect List count after insert_sorted, expected: %d, got: %lu.",
        NUM_SORTED_VALUES + 1, List_count(list));
  check(List_is_sorted(list, (List_compare)strcmp) == 1,
        "List is not sorted after insert_sorted.");

error:
  return;
}

void test_destroy() { List_destroy(list); }

void all_tests() {
  mu_run_test(test_create);
  mu_run_test(test_push_pop);
  mu_run_test(test_unshift);
  mu_run_test(test_remove);
  mu_run_test(test_shift);
  mu_run_test(test_insert_sorted);
  mu_run_test(test_destroy);

  return;
error:
  List_destroy(list);
}

RUN_TESTS(all_tests);
