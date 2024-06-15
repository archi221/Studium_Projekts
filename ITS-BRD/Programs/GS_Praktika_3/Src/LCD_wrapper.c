#include "input_wrapper.h"
#include "LCD_GUI.h"
#include "LCD_wrapper.h"
#include <stdint.h>
#include "errorhandler.h"
#include <stdlib.h>

static RGBTRIPLE line[LCD_BREITE];//nur bis 480 pixel breite

static Coordinate starting_point;

static uint16_t LCD_line_colors[LCD_BREITE];
			
void wrap_line() {
	starting_point.x = 0;
	
	for (int i = 0; i < get_height(); i++) {
			get_next_line(line);
			for (int j = 0; j < get_width(); ++j) {
					LCD_line_colors[j] = 0;
					LCD_line_colors[j] |= ((int)(line[j].rgbtRed / TO_4_BIT)) << 11;
					LCD_line_colors[j] |= ((int)(line[j].rgbtGreen / TO_5_BIT)) << 5;
					LCD_line_colors[j] |= (int)(line[j].rgbtBlue / TO_4_BIT);
			}
			starting_point.y = (LCD_HOEHE - 1) - i;
			ERR_HANDLER((LCD_HOEHE < starting_point.y) && (starting_point.y > LCD_BREITE),
									"starting_point: außerhalb des displays");
			GUI_WriteLine(starting_point, get_width(), LCD_line_colors);
	}
}

void* get_line_adress() {
	return line;
}
