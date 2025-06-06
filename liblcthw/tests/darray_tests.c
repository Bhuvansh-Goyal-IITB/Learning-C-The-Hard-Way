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
  mu_assert(array != NULL, "failed to create array");
  mu_assert(array->contents != NULL, "array contents should not be NULL");
  mu_assert(array->size == 0, "array size should be 0.");
  mu_assert(array->element_size == sizeof(int),
            "array element_size should be %lu.", sizeof(int));
  mu_assert(array->capacity == 100, "array capacity should be 100.");
  mu_assert(array->min_capacity == 100, "array min_capacity should be 100.");
error:
  return;
}

void test_new() {
  test_element = DArray_new(array);
  check(test_element != NULL, "failed to create test_element.");
error:
  return;
}

void test_push() {
  int rc = 0;

  for (int i = 0; i < NUM_VALUES; i++) {
    values[i] = i * 333;
    rc = DArray_push(array, values + i);
    mu_assert(rc == 0, "array push failed.");
  }

  mu_assert(DArray_size(array) == 1000,
            "array size should be 1000 after push.");
  mu_assert(DArray_capacity(array) == 1600,
            "array capacity should be 1600 after push.");
error:
  return;
}

void test_insert() {
  int rc = DArray_insert(array, test_element, 500);
  mu_assert(rc == 0, "array insert failed.");

  mu_assert(DArray_size(array) == 1001,
            "array size should be 1001 after insert.");
  mu_assert(DArray_capacity(array) == 1600,
            "array capacity should be 1600 after insert.");
error:
  return;
}

void test_get() {
  int* val = DArray_get(array, 500);
  mu_assert(val != NULL, "val should not be NULL.");
  mu_assert(val == test_element, "val should be equal to test_element.");
error:
  return;
}

void test_remove() {
  int* val = DArray_remove(array, 500);
  mu_assert(DArray_size(array) == 1000,
            "array size should be 1000 after remove.");
  mu_assert(DArray_capacity(array) == 1600,
            "array capacity should be 1600 after remove.");

  mu_assert(val != NULL, "val should not be NULL.");
  mu_assert(val == test_element, "val should be equal to test_element.");

  free(val);
  test_element = NULL;
error:
  return;
}

void test_pop() {
  for (int i = NUM_VALUES - 1; i >= 0; i--) {
    int* val = DArray_pop(array);
    mu_assert(val != NULL, "array pop failed.");
    mu_assert(val == values + i, "val should be equal to values + %d", i);
  }

  mu_assert(DArray_size(array) == 0, "array size should be 0 after pop.");
  mu_assert(DArray_capacity(array) == 100,
            "array capacity should be 100 after pop.");
error:
  return;
}

void test_expand_contract() {
  int rc = DArray_expand(array);
  mu_assert(rc == 0, "array expand failed.");

  mu_assert(DArray_size(array) == 0, "array size should be 0 after expand.");
  mu_assert(DArray_capacity(array) == 200,
            "array capacity should be 200 after expand.");

  rc = DArray_contract(array);
  mu_assert(rc == 0, "array contract failed.");

  mu_assert(DArray_size(array) == 0, "array size should be 0 after contract.");
  mu_assert(DArray_capacity(array) == 100,
            "array capacity should be 100 after contract.");

  rc = DArray_contract(array);
  mu_assert(rc == 0, "darray contract failed.");

  mu_assert(DArray_size(array) == 0, "array size should be 0 after contract.");
  mu_assert(DArray_capacity(array) == 100,
            "array capacity should be 100 after contract.");
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
