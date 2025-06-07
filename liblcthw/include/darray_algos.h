#ifndef __darray_algos_h__
#define __darray_algos_h__

#include <darray.h>

typedef int (*DArray_compare)(const void* a, const void* b);

int DArray_qsort(DArray* array, DArray_compare cmp);
// int DArray_headpsort(DArray* array, DArray_compare cmp);
// int DArray_mergesort(DArray* array, DArray_compare cmp);

#endif
