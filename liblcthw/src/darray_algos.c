#include <darray_algos.h>

int DArray_qsort(DArray *array, DArray_compare cmp) {
  check_invariants(array);
  qsort(array->contents, array->size, sizeof(void *), cmp);
  return 0;
error:
  return -1;
}
