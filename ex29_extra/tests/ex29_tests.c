#include <dlfcn.h>

#include "debug.h"

typedef int (*print_msg_func)(const char*);
typedef int (*case_func)(const char*, int len);
typedef int (*fail_func)();

int main() {
  const char* lib_file = "./build/libex29.so";
  const char* func_to_run = "print_a_message";
  const char data[] = "hello";

  void* lib = dlopen(lib_file, RTLD_NOW);
  check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

  int rc = 0;

  print_msg_func test_func_1 = dlsym(lib, func_to_run);
  check(test_func_1 != NULL, "Did not find %s function in the library %s: %s",
        func_to_run, lib_file, dlerror());

  rc = test_func_1(data);
  check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

  func_to_run = "uppercase";
  case_func test_func_2 = dlsym(lib, func_to_run);
  check(test_func_2 != NULL, "Did not find %s function in the library %s: %s",
        func_to_run, lib_file, dlerror());

  rc = test_func_2(data, sizeof(data));
  check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

  func_to_run = "lowercase";
  test_func_2 = dlsym(lib, func_to_run);
  check(test_func_2 != NULL, "Did not find %s function in the library %s: %s",
        func_to_run, lib_file, dlerror());

  rc = test_func_2(data, sizeof(data));
  check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);

  func_to_run = "fail_on_purpose";
  fail_func test_func_3 = dlsym(lib, func_to_run);
  check(test_func_3 != NULL, "Did not find %s function in the library %s: %s",
        func_to_run, lib_file, dlerror());

  rc = test_func_3();
  check(rc == 1, "Function %s return %d for data: %s", func_to_run, rc, data);

  rc = dlclose(lib);
  check(rc == 0, "Failed to close %s", lib_file);

  return 0;
error:
  return 1;
}
