#ifndef __vector_h__
#define __vector_h__

#include <stdlib.h>
#include <string.h>

#include "../common/dbg.h"
#include "bit_buffer.h"

#define VECTOR_DEF(type, name)                 \
  typedef struct name {                        \
    type *arr;                                 \
    int size;                                  \
    int capacity;                              \
  } name;                                      \
  int create_##name(name **v);                 \
  int name##_push(name *v, type e);            \
  int name##_at(name *v, int i, type *result); \
  void name##_cleanup(name *v)

#define VECTOR(type, name)                                           \
  int create_##name(name **v) {                                      \
    *v = (name *)calloc(1, sizeof(name));                            \
    check_mem(*v);                                                   \
    (*v)->arr = NULL;                                                \
    (*v)->size = 0;                                                  \
    (*v)->capacity = 0;                                              \
    return 0;                                                        \
  error:                                                             \
    return -1;                                                       \
  }                                                                  \
  int name##_push(name *v, type e) {                                 \
    if (v->size == v->capacity) {                                    \
      int old_capacity = v->capacity;                                \
      v->capacity = v->capacity == 0 ? 1 : 2 * v->capacity;          \
      type *new_arr = (type *)calloc(1, sizeof(type) * v->capacity); \
      check_mem(new_arr);                                            \
      if (v->arr) {                                                  \
        memcpy(new_arr, v->arr, old_capacity * sizeof(type));        \
        free(v->arr);                                                \
      }                                                              \
      v->arr = new_arr;                                              \
    }                                                                \
    v->arr[v->size++] = e;                                           \
    return 0;                                                        \
  error:                                                             \
    return -1;                                                       \
  }                                                                  \
  int name##_at(name *v, int i, type *result) {                      \
    if (i >= v->size) {                                              \
      sentinel("Index out of bounds");                               \
    }                                                                \
    *result = v->arr[i];                                             \
    return 0;                                                        \
  error:                                                             \
    return -1;                                                       \
  }                                                                  \
  void name##_cleanup(name *v) {                                     \
    if (v == NULL) return;                                           \
    if (v->arr) free(v->arr);                                        \
    free(v);                                                         \
  }

VECTOR_DEF(char, vc);
VECTOR_DEF(vc *, vvc);
VECTOR_DEF(int, vi);
VECTOR_DEF(bit_buffer *, vbit_buffer);

#endif
