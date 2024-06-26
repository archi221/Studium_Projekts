#include "input_wrapper.h"
#include "LCD_GUI.h"
#include "LCD_wrapper.h"
#include <stdint.h>
#include "errorhandler.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "input.h"
#include "input_wrapper.h"
#include "LCD_wrapper.h"
#include "input_pin.h"

static Coordinate starting_point;

static uint16_t LCD_line_colors[LCD_BREITE];

void wrap_line(int von, int höhe, int anzahl, RGBTRIPLE *line) {
    starting_point.x = von;
    starting_point.y = (LCD_HÖHE - 1) - höhe;
    char buffer[40];
    sprintf(buffer, "höhe: %d height; %d zu gross", höhe, get_height());
    ERR_HANDLER(höhe >= get_height(), buffer);
    sprintf(buffer, "von: %d  anzahl; %d width: %d zu gross", von, anzahl, get_width());
    ERR_HANDLER((von + anzahl) > get_width(), buffer);
    for (int j = 0; j < anzahl; ++j) {
        LCD_line_colors[j] = 0;
        LCD_line_colors[j] |= ((int) (line[j].rgbtRed >> 3)) << 11;
        LCD_line_colors[j] |= ((int) (line[j].rgbtGreen >> 2)) << 5;
        LCD_line_colors[j] |= (int) (line[j].rgbtBlue >> 3);
    }
    GUI_WriteLine(starting_point, anzahl, LCD_line_colors);
}

