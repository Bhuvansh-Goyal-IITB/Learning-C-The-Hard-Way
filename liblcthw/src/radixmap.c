#include <radixmap.h>

RadixMap* RadixMap_create(size_t max) {
  RadixMap* map = calloc(1, sizeof(RadixMap));
  check_mem(map);

  map->contents = calloc(max, sizeof(RMElement));
  check_mem(map->contents);

  map->temp = calloc(max, sizeof(RMElement));
  check_mem(map->temp);

  check(max > 0, "invalid RadixMap max, expected: > 0, got: %lu.", max);
  map->max = max;

  return map;
error:
  RadixMap_destroy(map);
  return NULL;
}

void RadixMap_destroy(RadixMap* map) {
  if (map == NULL) return;
  free(map->contents);
  free(map->temp);
  free(map);
}

#define ByteOf(x, y) ((uint8_t*)(x))[(y)]

static inline void radix_sort(short offset, size_t max, uint64_t* source,
                              uint64_t* dest) {
  size_t count[256] = {0};

  for (uint64_t* sp = source; sp < source + max; sp++) {
    count[ByteOf(sp, offset)]++;
  }

  size_t s = 0, c = 0;
  for (size_t* cp = count; cp < count + 256; cp++) {
    c = *cp;
    *cp = s;
    s += c;
  }

  for (uint64_t* sp = source; sp < source + max; sp++) {
    size_t* cp = count + ByteOf(sp, offset);
    dest[(*cp)++] = *sp;
  }
}

int RadixMap_sort(RadixMap* map) {
  check_invariants(map);

  uint64_t* source = (uint64_t*)&map->contents[0].raw;
  uint64_t* temp = (uint64_t*)&map->temp[0].raw;

  radix_sort(0, map->end, source, temp);
  radix_sort(1, map->end, temp, source);
  radix_sort(2, map->end, source, temp);
  radix_sort(3, map->end, temp, source);

  return 0;
error:
  return -1;
}

RMElement* RadixMap_find(RadixMap* map, uint32_t key) {
  check_invariants(map);
  RMElement* result = NULL;

  size_t s = 0;
  size_t e = map->max - 1;

  while (s <= e) {
    size_t mid = s + ((e - s) / 2);

    if (map->contents[mid].data.key < key) {
      s = mid + 1;
    } else if (map->contents[mid].data.key > key) {
      e = mid - 1;
    } else {
      result = &map->contents[mid];
      break;
    }
  }

  return result;
error:
  return NULL;
}

int RadixMap_add(RadixMap* map, uint32_t key, uint32_t value) {
  check_invariants(map);
  check(map->end < map->max, "RadixMap is full.");
  check(key < UINT32_MAX, "invalid key, expected: < UINT32_MAX (%u), got: %u.",
        UINT32_MAX, key);

  RMElement el = {.data.key = key, .data.value = value};
  map->contents[map->end++] = el;

  if (map->end > 1) {
    int rc = RadixMap_sort(map);
    check(rc == 0, "RadixMap sort failed.");
  }

  return 0;
error:
  return -1;
}

int RadixMap_delete(RadixMap* map, RMElement* el) {
  check_invariants(map);
  check(el != NULL, "element is NULL.");

  el->data.key = UINT32_MAX;

  if (map->end > 1) {
    int rc = RadixMap_sort(map);
    check(rc == 0, "RadixMap sort failed.");
  }

  map->end--;

  return 0;
error:
  return -1;
}
