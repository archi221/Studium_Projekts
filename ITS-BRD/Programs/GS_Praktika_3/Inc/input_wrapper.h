#ifndef _INPUT_H
#define _INPUT_H

#include "BMP_types.h"
#include "stdbool.h"

void get_BM_file_header();

void get_BM_info_header();

void get_BT_palette(struct tagRGBQUAD[]);

void get_next_line(void (*func)(char *a, bool compressed));

void decompress_line(char *line);

#endif