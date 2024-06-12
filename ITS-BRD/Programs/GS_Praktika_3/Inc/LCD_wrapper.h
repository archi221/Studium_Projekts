#ifndef _LCD_WRAPPER_H
#define _LCD_WRAPPER_H

#include "BMP_types.h"
#include "stdbool.h"
#include "input.h"

#define LCD_BREITE 480
#define TO_4_BIT 8.2258
#define TO_5_BIT 4.0476

void wrap_line();

void* get_line_adress();

#endif