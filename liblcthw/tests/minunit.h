#undef NDEBUG
#ifndef __minunit_h__
#define __minunit_h__

#include <debug.h>
#include <stdio.h>
#include <stdlib.h>

static int tests_run = 0;
static char *error_message = NULL;

#define mu_assert(test, M, ...)                            \
  do {                                                     \
    if (!(test)) {                                         \
      log_err(M, ##__VA_ARGS__);                           \
      int rc = asprintf(&error_message, M, ##__VA_ARGS__); \
      if (rc == -1) error_message = "asprintf failed.";    \
      goto error;                                          \
    }                                                      \
  } while (0)

#define mu_run_test(test)          \
  do {                             \
    test();                        \
    tests_run++;                   \
    if (error_message) goto error; \
  } while (0)

#define RUN_TESTS(name)                      \
  int main(int argc, char *argv[]) {         \
    (void)argc;                              \
    debug("-----RUNNING: %s", argv[0]);      \
    printf("-----\nRUNNING: %s\n", argv[0]); \
    name();                                  \
    if (error_message != 0) {                \
      printf("FAILED: %s\n", error_message); \
    } else {                                 \
      printf("ALL TEST PASSED\n");           \
    }                                        \
    printf("Tests run: %d\n", tests_run);    \
    int exit_code = (error_message != 0);    \
    free(error_message);                     \
    exit(exit_code);                         \
  }

#endif
