#ifndef _INPUT_WRAPPER_H
#define _INPUT_WRAPPER_H

#include "BMP_types.h"
#include "stdbool.h"
#include "input.h"

#define LCD_BREITE 480

void get_next_line_24(RGBTRIPLE *line);

void get_next_line_8(RGBTRIPLE *line);

void get_next_line_(RGBTRIPLE *line);

void get_BT_palette(struct tagRGBQUAD[]);

void decompress_line(RGBTRIPLE *line);

void init_next_picture();

void read_palette();

int get_width();

int get_height();

#endif