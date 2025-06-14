#ifndef __darray_h__
#define __darray_h__

#include <debug.h>
#include <stdlib.h>

typedef int (*DArray_compare)(const void* a, const void* b);

typedef struct DArray {
  size_t size;
  size_t capacity;
  size_t min_capacity;
  size_t element_size;
  void** contents;
} DArray;

DArray* DArray_create(size_t element_size, size_t min_capacity);

void DArray_destroy(DArray* array);
void DArray_clear(DArray* array);
void DArray_clear_destroy(DArray* array);

int DArray_expand(DArray* array);
int DArray_contract(DArray* array);
int DArray_push(DArray* array, void* el);
int DArray_insert(DArray* array, void* el, size_t i);
void* DArray_pop(DArray* array);
void* DArray_remove(DArray* array, size_t i);

#define check_invariants(A)                                                    \
  check((A) != NULL, "DArray is NULL.");                                       \
  check((A)->contents != NULL, "DArray contents is NULL.");                    \
  check((A)->min_capacity > 0,                                                 \
        "invalid DArray min_capacity, expected: > 0, got: %lu.",               \
        (A)->min_capacity);                                                    \
  check((A)->min_capacity <= (A)->capacity,                                    \
        "invalid DArray capacity, expected: >= %lu (min_capacity), got: %lu.", \
        (A)->min_capacity, (A)->capacity);                                     \
  check((A)->size <= (A)->capacity,                                            \
        "invalid DArray size, expected: <= %lu (capacity), got: %lu.",         \
        (A)->capacity, (A)->size);

static inline size_t DArray_size(DArray* array) {
  check(array != NULL, "DArray is NULL.");
  return array->size;
error:
  return -1;
}

static inline size_t DArray_capacity(DArray* array) {
  check(array != NULL, "DArray is NULL.");
  return array->capacity;
error:
  return -1;
}

static inline void* DArray_first(DArray* array) {
  check(array != NULL, "DArray is NULL.");
  check(array->contents != NULL, "DArray contents is NULL.");
  return array->contents[0];
error:
  return NULL;
}

static inline void* DArray_last(DArray* array) {
  check(array != NULL, "DArray is NULL.");
  check(array->contents != NULL, "DArray contents is NULL.");
  return array->size > 0 ? array->contents[array->size - 1] : NULL;
error:
  return NULL;
}

static inline void* DArray_get(DArray* array, size_t i) {
  check(array != NULL, "DArray is NULL.");
  check(array->contents != NULL, "DArray contents is NULL.");
  check(i < array->size, "invalid index, expected: < %lu (size), got: %lu.",
        array->size, i);
  return array->contents[i];
error:
  return NULL;
}

static inline void* DArray_new(DArray* array) {
  void* el = NULL;
  check(array != NULL, "DArray is NULL.");
  check(array->element_size > 0,
        "invalid element_size to use DArray_new, expected: > 0, got: %lu.",
        array->element_size);
  el = calloc(1, array->element_size);
  check(el != NULL, "failed to make new element.");
  return el;
error:
  return NULL;
}

static inline int DArray_is_sorted(DArray* array, DArray_compare cmp) {
  check_invariants(array);

  if (array->size == 0) return 1;

  for (size_t i = 0; i < array->size - 1; i++) {
    if (cmp(array->contents[i], array->contents[i + 1]) > 0) {
      return 0;
    }
  }

  return 1;
error:
  return -1;
}

#endif
