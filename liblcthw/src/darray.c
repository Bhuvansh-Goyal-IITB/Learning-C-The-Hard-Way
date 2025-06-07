#include <darray.h>
#include <debug.h>

DArray* DArray_create(size_t element_size, size_t min_capacity) {
  DArray* array = calloc(1, sizeof(DArray));
  check_mem(array);

  check(min_capacity > 0, "min_capacity should be > 0.");
  array->capacity = array->min_capacity = min_capacity;
  array->element_size = element_size;

  array->contents = calloc(min_capacity, sizeof(void*));
  check_mem(array->contents);

  return array;
error:
  free(array);
  return NULL;
}

void DArray_destroy(DArray* array) {
  if (array == NULL) return;
  free(array->contents);
  free(array);
}

void DArray_clear(DArray* array) {
  if (array == NULL || array->contents == NULL) return;
  for (size_t i = 0; i < array->size; i++) {
    free(array->contents[i]);
  }
}

void DArray_clear_destroy(DArray* array) {
  DArray_clear(array);
  DArray_destroy(array);
}

int DArray_expand(DArray* array) {
  check_invariants(array);

  size_t new_capacity = array->capacity * 2;

  void** contents = realloc(array->contents, new_capacity * sizeof(void*));
  check_mem(contents);

  array->contents = contents;
  array->capacity = new_capacity;

  return 0;
error:
  return 1;
}

int DArray_contract(DArray* array) {
  check_invariants(array);

  size_t new_capacity = array->capacity / 2;

  if (array->size <= new_capacity && array->min_capacity <= new_capacity) {
    void** contents = realloc(array->contents, new_capacity * sizeof(void*));
    check_mem(contents);

    array->contents = contents;
    array->capacity = new_capacity;
  }

  return 0;
error:
  return 1;
}

int DArray_push(DArray* array, void* el) {
  check_invariants(array);

  array->contents[array->size++] = el;

  if (array->size >= array->capacity) {
    int rc = DArray_expand(array);
    check(rc == 0, "array expand failed.");
  }

  return 0;
error:
  return 1;
}

void* DArray_pop(DArray* array) {
  check_invariants(array);

  void* el = DArray_last(array);

  if (el != NULL) {
    array->contents[--array->size] = NULL;

    if (array->size <= array->capacity / 4) {
      int rc = DArray_contract(array);
      check(rc == 0, "array contract failed.");
    }
  }

  return el;
error:
  return NULL;
}

static int DArray_swap(DArray* array, size_t i, size_t j) {
  check(i < array->size && j < array->size, "index out of bounds.");

  if (i == j) return 0;

  void* tmp = array->contents[i];
  array->contents[i] = array->contents[j];
  array->contents[j] = tmp;

  return 0;
error:
  return 1;
}

int DArray_insert(DArray* array, void* el, size_t i) {
  check_invariants(array);
  check(i <= array->size, "i should be less than or equal to array size.");

  int rc = DArray_push(array, el);
  check(rc == 0, "array push failed.");

  for (size_t n = 0, k = array->size - 1; n < array->size - 1 - i; n++, k--) {
    rc = DArray_swap(array, k, k - 1);
    check(rc == 0, "array swap failed.");
  }

  return 0;
error:
  return 1;
}

void* DArray_remove(DArray* array, size_t i) {
  check_invariants(array);
  check(i < array->size, "i should be less than array size.");

  int rc = DArray_swap(array, i, array->size - 1);
  check(rc == 0, "array swap failed.");

  void* el = DArray_pop(array);
  check(el != NULL, "array pop failed.");

  for (size_t n = 0, k = i; n < array->size - 1 - i; n++, k++) {
    rc = DArray_swap(array, k, k + 1);
    check(rc == 0, "array swap failed.");
  }

  return el;
error:
  return NULL;
}
