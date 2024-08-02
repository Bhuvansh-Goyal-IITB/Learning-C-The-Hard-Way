#include <stdio.h>
#include <stdlib.h>

#include "../common/dbg.h"
#include "bit_buffer.h"

int create_bit_buffer(bit_buffer **b, int num_bits) {
  *b = (bit_buffer *)calloc(1, sizeof(bit_buffer));
  check_mem(*b);

  int num_bytes = num_bits / 8;
  if (num_bits % 8 != 0) {
    num_bytes++;
  }
  (*b)->buffer = (unsigned char *)calloc(1, num_bytes);
  check_mem((*b)->buffer);

  (*b)->num_bits = num_bits;
  (*b)->num_bytes = num_bytes;

  return 0;
error:
  return -1;
}

int is_set(bit_buffer *b, int index) {
  if (index >= b->num_bits) {
    sentinel("Index out of bounds.");
  }
  unsigned char mask = 128 >> (index % 8);
  if ((b->buffer[index / 8] & mask) == mask) {
    return 1;
  }
  return 0;
error:
  return -1;
}

int set_range(bit_buffer *b, int start, int end) {
  if (start > end || start >= b->num_bits || end >= b->num_bits) {
    sentinel("Index out of bounds.");
  }

  int start_byte = start / 8;
  int end_byte = end / 8;

  for (int i = start_byte; i <= end_byte; i++) {
    if (start_byte == end_byte) {
      b->buffer[i] |= ((255 >> (start % 8)) & (255 << (7 - (end % 8))) & 255);
    } else {
      if (i == start_byte) {
        b->buffer[i] |= (255 >> (start % 8));
      } else if (i == end_byte) {
        b->buffer[i] |= ((255 << (7 - (end % 8))) & 255);
      } else {
        b->buffer[i] |= 255;
      }
    }
  }
  return 0;
error:
  return -1;
}

void print_bit_buffer(bit_buffer *b) {
  for (int i = 0; i < b->num_bytes; i++) {
    unsigned char byte = b->buffer[i];
    for (int j = 7; j >= 0; j--) {
      if ((byte & (1 << j)) == (1 << j)) {
        printf("1");
      } else {
        printf("0");
      }
    }
    printf(" ");
  }

  printf("\n");
}

void bit_buffer_cleanup(bit_buffer *b) {
  if (b == NULL) return;
  if (b->buffer) free(b->buffer);
  free(b);
}
