#ifndef __bit_buffer_h__
#define __bit_buffer_h__

typedef struct bit_buffer {
  unsigned char *buffer;
  int num_bits;
  int num_bytes;
} bit_buffer;

int create_bit_buffer(bit_buffer **b, int num_bits);
int is_set(bit_buffer *b, int index);
int set_range(bit_buffer *b, int start, int end);
void print_bit_buffer(bit_buffer *b);
void bit_buffer_cleanup(bit_buffer *b);

#endif
