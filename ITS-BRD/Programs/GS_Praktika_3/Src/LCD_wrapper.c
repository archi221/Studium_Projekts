#include "input_wrapper.h"
#include "LCD_GUI.h"
#include "LCD_wrapper.h"
#include <stdint.h>
#include "errorhandler.h"
#include <stdlib.h>

static RGBTRIPLE line[LCD_BREITE];//nur bis 480 pixel breite

static Coordinate starting_point;
			
void wrap_line() {
	starting_point.x = 0;
	int width = get_width();
	uint16_t *LCD_line_COLORS = malloc(sizeof(uint16_t) * width);
	for (int i = get_height(); i > 0; --i) {
			get_next_line(line);
			for (int j = 0; j < width; ++j) {
					LCD_line_COLORS[j] |= (int)(line[j].rgbtRed / TO_4_BIT) << 11;
					LCD_line_COLORS[j] |= (int)(line[j].rgbtGreen / TO_5_BIT) << 5;
					LCD_line_COLORS[j] |= (int)(line[j].rgbtBlue / TO_4_BIT);
			}
			starting_point.y = i;
			ERR_HANDLER((LCD_HÖHE < starting_point.y) && (starting_point.y > LCD_BREITE),
									"starting_point: außerhalb des displays");
			ERR_HANDLER(width == (sizeof(*LCD_line_COLORS) / sizeof(uint16_t)),
									"LCD_line_COLORS: hat eine falsche größe");
			GUI_WriteLine(starting_point, width, LCD_line_COLORS);
	}
	free(LCD_line_COLORS);
}

void* get_line_adress() {
	return line;
}
