#ifndef __vector_h__
#define __vector_h__

#include <stdlib.h>
#include <string.h>

#include "../common/dbg.h"

#define VECTOR(type, name)                                    \
  typedef struct name {                                       \
    type *arr;                                                \
    int size;                                                 \
    int capacity;                                             \
  } name;                                                     \
  name create_##name() {                                      \
    name v = {.arr = NULL, .size = 0, .capacity = 0};         \
    return v;                                                 \
  }                                                           \
  void name##_push(name *v, type e) {                         \
    if (v->size == v->capacity) {                             \
      int old_capacity = v->capacity;                         \
      v->capacity = v->capacity == 0 ? 1 : 2 * v->capacity;   \
      type *new_arr = calloc(1, sizeof(type) * v->capacity);  \
      check_mem(new_arr);                                     \
      if (v->arr) {                                           \
        memcpy(new_arr, v->arr, old_capacity * sizeof(type)); \
        free(v->arr);                                         \
      }                                                       \
      v->arr = new_arr;                                       \
    }                                                         \
    v->arr[v->size++] = e;                                    \
    return;                                                   \
  error:                                                      \
    if (v->arr) free(v->arr);                                 \
    return;                                                   \
  }                                                           \
  int name##_at(name *v, int i, type *result) {               \
    if (i >= v->size) {                                       \
      sentinel("Index out of bounds");                        \
    }                                                         \
    *result = v->arr[i];                                      \
    return 0;                                                 \
  error:                                                      \
    if (v->arr) free(v->arr);                                 \
    return -1;                                                \
  }                                                           \
  void name##_cleanup(name *v) {                              \
    if (v->arr) free(v->arr);                                 \
  }

#endif
