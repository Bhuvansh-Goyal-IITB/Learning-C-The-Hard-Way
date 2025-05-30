#undef NDEBUG
#ifndef __minunit_h__
#define __minunit_h__

#include <stdio.h>
#include <stdlib.h>

#include "debug.h"

static int tests_run = 0;

#define mu_assert(test, message) \
  do {                           \
    if (!(test)) {               \
      log_err(message);          \
      return message;            \
    }                            \
  } while (0)

#define mu_run_test(test)        \
  do {                           \
    char *message = test();      \
    tests_run++;                 \
    if (message) return message; \
  } while (0)

#define RUN_TESTS(name)                      \
  int main(int argc, char *argv[]) {         \
    (void)argc;                              \
    debug("-----RUNNING: %s", argv[0]);      \
    printf("-----\nRUNNING: %s\n", argv[0]); \
    char *result = name();                   \
    if (result != 0) {                       \
      printf("FAILED: %s\n", result);        \
    } else {                                 \
      printf("ALL TEST PASSED\n");           \
    }                                        \
    printf("Tests run: %d\n", tests_run);    \
    exit(result != 0);                       \
  }

extern int tests_run;

#endif
