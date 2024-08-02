#ifndef __file_h__
#define __file_h__

#include "vector.h"

int load_line(FILE *fp, vc *s);
int load_config_file(char *file_path, vvc *b);
void free_vvc_elements(vvc *v);
int process_file(vc *file_name, char **search_args, int search_args_count,
                 int or_logic);

#endif
