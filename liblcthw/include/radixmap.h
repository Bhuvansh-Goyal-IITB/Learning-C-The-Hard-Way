#ifndef __radixmap_h__
#define __radixmap_h__

#include <debug.h>
#include <stdint.h>
#include <stdlib.h>

typedef union RMElement {
  uint64_t raw;
  struct {
    uint32_t key;
    uint32_t value;
  } data;
} RMElement;

typedef struct RadixMap {
  size_t max;
  size_t end;
  RMElement* contents;
  RMElement* temp;
} RadixMap;

RadixMap* RadixMap_create(size_t max);

void RadixMap_destroy(RadixMap* map);

int RadixMap_sort(RadixMap* map);

RMElement* RadixMap_find(RadixMap* map, uint32_t key);

int RadixMap_add(RadixMap* map, uint32_t key, uint32_t value);

int RadixMap_delete(RadixMap* map, RMElement* el);

#define check_invariants(A)                                                  \
  check((A) != NULL, "RadixMap is NULL.");                                   \
  check((A)->contents != NULL, "RadixMap contents is NULL.");                \
  check((A)->temp != NULL, "RadixMap temp is NULL.");                        \
  check((A)->max > 0, "invalid RadixMap max, expected: > 0, got: %lu.",      \
        (A)->max);                                                           \
  check((A)->end <= (A)->max,                                                \
        "invalid RadixMap end, expected: <= %lu (max), got: %lu.", (A)->max, \
        (A)->end);

static inline int RadixMap_is_sorted(RadixMap* map) {
  check_invariants(map);

  if (map->end == 0) return 1;

  for (size_t i = 0; i < map->end - 1; i++) {
    if (map->contents[i].data.key > map->contents[i + 1].data.key) {
      debug("index (%lu) key: %u, index (%lu) key: %u.", i,
            map->contents[i].data.key, i + 1, map->contents[i + 1].data.key);
      return 0;
    }
  }

  return 1;
error:
  return -1;
}

#endif
