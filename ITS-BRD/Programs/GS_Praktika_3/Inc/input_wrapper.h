#ifndef _INPUT_WRAPPER_H
#define _INPUT_WRAPPER_H

#include "BMP_types.h"
#include "stdbool.h"
#include "input.h"

get_next_line_24(char *line, bool compressed);

get_next_line_8(char *line, bool compressed);

get_next_line_(char *line, bool compressed);

void get_BT_palette(struct tagRGBQUAD[]);

void decompress_line(char *line);

void init_next_picture();

void read_palette();

int get_width();

int get_height();

#endif