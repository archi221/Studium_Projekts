#ifndef _LCD_WRAPPER_H
#define _LCD_WRAPPER_H

#include "BMP_types.h"
#include "stdbool.h"
#include "input.h"

#define LCD_BREITE 480
#define LCD_HOEHE 320
#define TO_4_BIT 8.2258
#define TO_5_BIT 4.0476

/**
 * @brief This function prints all pixel of a picture line after line to the LCD
 * display for the 24 bit format.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
void wrap_line(int von, int höhe, int anzahl, RGBTRIPLE *line);

#endif