#ifndef _INPUT_WRAPPER_H
#define _INPUT_WRAPPER_H

#include "BMP_types.h"
#include "stdbool.h"
#include "input.h"

#define LCD_BREITE 480
#define LCD_HÖHE 320
#define ESCAPE 0
#define LINE_END 0
#define BITMAP_END 1
#define DELTA 2
#define _3_BYTES 3

/**
* @brief This function prints all pixel of a picture line after line to the LCD
 * display for the 24 bit format.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
*/
void get_next_line_24(RGBTRIPLE *line);

/**
 * @brief This function prints all pixel of a picture line after line to the LCD
 * display for the 8 bit format.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
void get_next_line_8(RGBTRIPLE *line);

/**
 * @brief This function prints all pixel of a picture line after line to the LCD
 * display for the 8 bit format.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
void get_next_line_8_pressed(RGBTRIPLE *line);

/**
 * @brief This function puts all pixel up to the anzahl in the line array at
 * the point where the counter variable is. It only works for the 8 bit format.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
void get_line(RGBTRIPLE *line, int anzahl);

/**
 * @brief This function points to the corresponding get_next_line function.
 * @param array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
extern void (*get_next_line)(RGBTRIPLE *line);

/**
 * @brief This function reads the next 2 byte from the current file until the
 * line end is reached
 * @param None
 * @retval Next byte of the current file or EOF (32 bit value for -1)
 */
void find_end_of_line();

/**
 * @brief This function initializes the next picture to be displayed and sets
 * the get_next_line function to the corresponding function.
 * @param None
 * @retval NOK if an error happens otherwise EOK
 */
int init_next_picture();

/**
 * @brief This function calls the print line function for the current line
 * @param von starting point of the line
 * @param höhe the height of the line
 * @param line array of RGBTRIPLE which represents the color of each pixel in one line
 * @retval None
 */
void call_wrap_line(int von, int höhe, RGBTRIPLE *line);

int get_width();

int get_height();

#endif