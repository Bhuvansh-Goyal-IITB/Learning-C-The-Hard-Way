#ifndef __darray_h__
#define __darray_h__

#include <debug.h>
#include <stdlib.h>

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

#define check_invariants(A)                                          \
  check((A) != NULL, "array shouldn't be NULL.");                    \
  check((A)->contents != NULL, "array contents shouldn't be NULL."); \
  check((A)->min_capacity <= (A)->capacity,                          \
        "array capacity should be >= min_capacity.");                \
  check((A)->size <= (A)->capacity, "array size should be <= capacity.");

static inline size_t DArray_size(DArray* array) {
  check(array != NULL, "array shouldn't be NULL.");
  return array->size;
error:
  return -1;
}

static inline size_t DArray_capacity(DArray* array) {
  check(array != NULL, "array shouldn't be NULL.");
  return array->capacity;
error:
  return -1;
}

static inline void* DArray_first(DArray* array) {
  check(array != NULL, "array shouldn't be NULL.");
  check(array->contents != NULL, "array contents shouldn't be NULL.");
  return array->contents[0];
error:
  return NULL;
}

static inline void* DArray_last(DArray* array) {
  check(array != NULL, "array shouldn't be NULL.");
  check(array->contents != NULL, "array contents shouldn't be NULL.");
  return array->size > 0 ? array->contents[array->size - 1] : NULL;
error:
  return NULL;
}

static inline void* DArray_get(DArray* array, size_t i) {
  check(array != NULL, "array shouldn't be NULL.");
  check(array->contents != NULL, "array contents shouldn't be NULL.");
  check(i < array->size, "darray attempt to get past max.");
  return array->contents[i];
error:
  return NULL;
}

static inline void* DArray_new(DArray* array) {
  void* el = NULL;
  check(array != NULL, "array shouldn't be NULL.");
  check(array->element_size > 0,
        "element size should be > 0 to use DArray_new.");
  el = calloc(1, array->element_size);
  check(el != NULL, "failed to make new element.");
  return el;
error:
  return NULL;
}

#endif
