// clang-format off
#include "minunit.h"
// clang-format on

#include <radixmap.h>
#include <time.h>

static RadixMap* map = NULL;

#define RADIXMAP_MAX 4

void test_create() {
  map = RadixMap_create(RADIXMAP_MAX);
  mu_assert(map != NULL, "RadixMap is NULL.");
  mu_assert(map->contents != NULL, "RadixMap contents is NULL.");
  mu_assert(map->temp != NULL, "RadixMap temp is NULL.");
  mu_assert(map->end == 0, "invalid RadixMap end, expected: 0, got: %lu.",
            map->end);
  mu_assert(map->max == RADIXMAP_MAX,
            "invalid RadixMap max, expected: %d, got: %lu.", RADIXMAP_MAX,
            map->end);
error:
  return;
}

void test_sort() {
  RMElement* prev_contents = map->contents;
  RMElement* prev_temp = map->temp;

  map->contents = NULL;
  map->temp = NULL;

  map->contents = calloc(map->max, sizeof(RMElement));
  mu_assert(map->contents != NULL, "RadixMap contents is NULL.");
  map->temp = calloc(map->max, sizeof(RMElement));
  mu_assert(map->temp != NULL, "RadixMap temp is NULL.");

  for (size_t i = 0; i < map->max; i++) {
    uint32_t key = (uint32_t)(rand() | rand() << 16);
    map->contents[i].data.key = key;
    map->contents[i].data.value = i;
    map->end++;
  }

  int rc = RadixMap_sort(map);
  mu_assert(rc == 0, "RadixMap sort failed.");
  mu_assert(RadixMap_is_sorted(map) == 1,
            "RadixMap is not sorted after RadixMap sort.");
error:
  free(map->contents);
  free(map->temp);

  map->contents = prev_contents;
  map->temp = prev_temp;
  map->end = 0;
}

void test_add() {
  for (size_t i = 0; i < map->max; i++) {
    uint32_t key = (uint32_t)(rand() | rand() << 16);
    size_t prev_end = map->end;
    mu_assert(RadixMap_add(map, key, i) == 0,
              "failed to add new element to RadixMap, key: %u, value: %lu.",
              key, i);
    mu_assert(map->end == prev_end + 1,
              "incorrent RadixMap end after adding, expected: %lu, got: %lu.",
              prev_end + 1, map->end);
    mu_assert(RadixMap_is_sorted(map),
              "RadixMap is not sorted after RadixMap add.");
  }
error:
  return;
}

void test_find_delete() {
  while (map->end > 0) {
    RMElement* el = RadixMap_find(map, map->contents[map->end / 2].data.key);
    mu_assert(el != NULL,
              "returned value from RadixMap find is NULL (expected to get "
              "valid result).");

    size_t prev_end = map->end;
    int rc = RadixMap_delete(map, el);
    mu_assert(rc == 0, "RadixMap delete failed.");
    mu_assert(map->end == prev_end - 1,
              "incorrent RadixMap end after deleting, expected: %lu, got: %lu.",
              prev_end - 1, map->end);
    mu_assert(RadixMap_is_sorted(map),
              "RadixMap is not sorted after RadixMap delete.");
  }

  mu_assert(map->end == 0,
            "incorrent RadixMap end after deleting all elements, expected: 0, "
            "got: %lu.",
            map->end);
error:
  return;
}

void test_destroy() { RadixMap_destroy(map); }

void all_tests() {
  srand(time(NULL));

  mu_run_test(test_create);
  mu_run_test(test_sort);
  mu_run_test(test_add);
  mu_run_test(test_find_delete);
  mu_run_test(test_destroy);

  return;
error:
  RadixMap_destroy(map);
}

RUN_TESTS(all_tests);
