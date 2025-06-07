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

void debug_print(List* list) {
  int i = 0;
  debug("------------------");
  LIST_FOREACH(list, first, next, cur) {
    debug("%d) %s", i, (char*)cur->value);
    i++;
  }
  debug("------------------");
}

void test_create() {
  list = List_create();
  mu_assert(list != NULL, "Failed to create list.");

error:
  return;
}

void test_destroy() {
  List_destroy(list);

  return;
}

void test_push_pop() {
  int rc = List_push(list, test1);
  mu_assert(rc == 0, "list push failed.");
  mu_assert(List_last(list) == test1, "Wrong last value.");

  rc = List_push(list, test2);
  mu_assert(rc == 0, "list push failed.");
  mu_assert(List_last(list) == test2, "Wrong last value.");

  rc = List_push(list, test3);
  mu_assert(rc == 0, "list push failed.");
  mu_assert(List_last(list) == test3, "Wrong last value.");
  mu_assert(List_count(list) == 3, "Wrong count on push.");

  char* val = List_pop(list);
  mu_assert(val == test3, "Wrong value on pop.");

  val = List_pop(list);
  mu_assert(val == test2, "Wrong value on pop.");

  val = List_pop(list);
  mu_assert(val == test1, "Wrong value on pop.");
  mu_assert(List_count(list) == 0, "Wrong count on pop.");

error:
  return;
}

void test_unshift() {
  int rc = List_unshift(list, test1);
  mu_assert(rc == 0, "list unshift failed.");
  mu_assert(List_first(list) == test1, "Wrong first value.");

  rc = List_unshift(list, test2);
  mu_assert(rc == 0, "list unshift failed.");
  mu_assert(List_first(list) == test2, "Wrong first value.");

  rc = List_unshift(list, test3);
  mu_assert(rc == 0, "list unshift failed.");
  mu_assert(List_first(list) == test3, "Wrong first value.");
  mu_assert(List_count(list) == 3, "Wrong count on unshift.");

error:
  return;
}

void test_remove() {
  char* val = List_remove(list, list->first->next);
  mu_assert(val == test2, "Wrong removed element.");
  mu_assert(List_count(list) == 2, "Wrong count after remove.");
  mu_assert(List_first(list) == test3, "Wrong first after remove.");
  mu_assert(List_last(list) == test1, "Wrong last after remove.");

error:
  return;
}

void test_shift() {
  mu_assert(List_count(list) != 0, "Wrong count before shift.");

  char* val = List_shift(list);
  mu_assert(val == test3, "Wrong value on shift.");

  val = List_shift(list);
  mu_assert(val == test1, "Wrong value on shift.");
  mu_assert(List_count(list) == 0, "Wrong count after shift.");

error:
  return;
}

void test_insert_sorted() {
  mu_assert(List_count(list) == 0, "Wrong count before insert sorted.");

  int rc = 0;

  for (int i = 0; i < NUM_SORTED_VALUES; i++) {
    List_push(list, sorted_values[i]);
  }

  mu_assert(List_count(list) == NUM_SORTED_VALUES,
            "Wrong count after pushing sorted values.");

  rc = List_insert_sorted(list, "d", (List_compare)strcmp);
  check(rc == 0, "List insert sorted failed.");

  check(List_count(list) == NUM_SORTED_VALUES + 1,
        "List count is wrong after Liss insert sorted.");
  check(List_is_sorted(list, (List_compare)strcmp) == 1,
        "List is not sorted after List insert sorted.");

error:
  return;
}

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
  return;
}

RUN_TESTS(all_tests);
