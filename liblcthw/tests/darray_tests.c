// clang-format off
#include "minunit.h"
// clang-format on

#include <darray.h>

static DArray* array = NULL;

#define NUM_VALUES 1000

static int values[NUM_VALUES];

static int* test_element = NULL;

void test_create() {
  array = DArray_create(sizeof(int), 100);
  mu_assert(array != NULL, "failed to create DArray.");
  mu_assert(array->contents != NULL, "DArray contents is NULL.");
  mu_assert(array->size == 0, "incorrect DArray size, expected: 0, got: %lu.",
            array->size);
  mu_assert(array->element_size == sizeof(int),
            "incorrect DArray element_size, expected: %lu, got: %lu.",
            sizeof(int), array->element_size);
  mu_assert(array->capacity == 100,
            "incorrect DArray capacity, expected: 100, got: %lu.",
            array->capacity);
  mu_assert(array->min_capacity == 100,
            "incorrect DArray min_capacity, expected: 100, got: %lu.",
            array->min_capacity);

error:
  return;
}

void test_new() {
  test_element = DArray_new(array);
  check(test_element != NULL, "failed to create new element.");
error:
  return;
}

void test_push() {
  int rc = 0;

  for (int i = 0; i < NUM_VALUES; i++) {
    values[i] = i * 333;
    rc = DArray_push(array, values + i);
    mu_assert(rc == 0, "DArray push failed.");
  }

  mu_assert(DArray_size(array) == 1000,
            "incorrect DArray size after push, expected: 1000, got: %lu.",
            DArray_size(array));
  mu_assert(DArray_capacity(array) == 1600,
            "incorrect DArray capacity after push, expected: 1600, got: %lu.",
            DArray_capacity(array));
error:
  return;
}

void test_insert() {
  int rc = DArray_insert(array, test_element, 500);
  mu_assert(rc == 0, "DArray insert failed.");

  mu_assert(DArray_size(array) == 1001,
            "incorrect DArray size after insert, expected: 1001, got: %lu.",
            DArray_size(array));
  mu_assert(DArray_capacity(array) == 1600,
            "incorrect DArray capacity after insert, expected: 1600, got: %lu.",
            DArray_capacity(array));
error:
  return;
}

void test_get() {
  int* val = DArray_get(array, 500);
  mu_assert(val != NULL, "value at DArray index 500 is NULL.");
  mu_assert(val == test_element,
            "incorrect value at DArray index 500, expected: %d, got: %d.",
            *test_element, *val);
error:
  return;
}

void test_remove() {
  int* val = DArray_remove(array, 500);
  mu_assert(DArray_size(array) == 1000,
            "incorrect DArray size after remove, expected: 1000, got: %lu.",
            DArray_size(array));
  mu_assert(DArray_capacity(array) == 1600,
            "incorrect DArray capacity after remove, expected: 1600, got: %lu.",
            DArray_capacity(array));

  mu_assert(val != NULL, "removed value is NULL.");
  mu_assert(val == test_element,
            "incorrect removed value, expected: %d, got: %d.", *test_element,
            *val);

  free(val);
  test_element = NULL;
error:
  return;
}

void test_pop() {
  for (int i = NUM_VALUES - 1; i >= 0; i--) {
    int* val = DArray_pop(array);
    mu_assert(val != NULL, "DArray pop failed.");
    mu_assert(val == values + i,
              "incorrect popped value, expected: %d, got: %d.", values[i],
              *val);
  }

  mu_assert(DArray_size(array) == 0,
            "incorrect DArray size after pop, expected: 0, got: %lu.",
            DArray_size(array));
  mu_assert(DArray_capacity(array) == 100,
            "incorrect DArray capacity after pop, expected: 100, got: %lu.",
            DArray_capacity(array));
error:
  return;
}

void test_expand_contract() {
  int rc = DArray_expand(array);
  mu_assert(rc == 0, "DArray expand failed.");

  mu_assert(DArray_size(array) == 0,
            "incorrect DArray size after expand, expected: 0, got: %lu.",
            DArray_size(array));
  mu_assert(DArray_capacity(array) == 200,
            "incorrect DArray capacity after expand, expected: 200, got: %lu.",
            DArray_capacity(array));

  rc = DArray_contract(array);
  mu_assert(rc == 0, "DArray contract failed.");

  mu_assert(DArray_size(array) == 0,
            "incorrect DArray size after contract, expected: 0, got: %lu.",
            DArray_size(array));
  mu_assert(
      DArray_capacity(array) == 100,
      "incorrect DArray capacity after contract, expected: 100, got: %lu.",
      DArray_capacity(array));

  rc = DArray_contract(array);
  mu_assert(rc == 0, "DArray contract failed.");

  mu_assert(DArray_size(array) == 0,
            "incorrect DArray size after contract, expected: 0, got: %lu.",
            DArray_size(array));
  mu_assert(
      DArray_capacity(array) == 100,
      "incorrect DArray capacity after contract, expected: 100, got: %lu.",
      DArray_capacity(array));
error:
  return;
}

void test_destroy() { DArray_destroy(array); }

void all_tests() {
  mu_run_test(test_create);
  mu_run_test(test_new);
  mu_run_test(test_push);
  mu_run_test(test_insert);
  mu_run_test(test_get);
  mu_run_test(test_remove);
  mu_run_test(test_pop);
  mu_run_test(test_expand_contract);
  mu_run_test(test_destroy);

  return;
error:
  DArray_destroy(array);
  free(test_element);
}

RUN_TESTS(all_tests);
