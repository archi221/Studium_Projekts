#include "input_wrapper.h"
#include "LCD_GUI.h"
#include "LCD_wrapper.h"
#include <stdint.h>
#include "errorhandler.h"

static RGBTRIPLE line[LCD_BREITE];//nur bis 480 pixel breite

static Coordinate starting_point;

starting_point.x = 0;

void wrap_line() {
    int width = get_width();
    for (int i = get_height(); i > 0; --i) {
        uint16_t LCD_line_COLORS[width];
        get_next_line_(line);
        for (int j = 0; j < width; ++j) {
            LCD_line_COLORS[j] |= ((double) line[j].rgbtRed / TO_4_BIT) << 11;
            LCD_line_COLORS[j] &= 0xF800;
            LCD_line_COLORS[j] |= ((double) line[j].rgbtGreen / TO_5_BIT) << 5;
            LCD_line_COLORS[j] &= 0xFFE0;
            LCD_line_COLORS[j] |= (double) line[j].rgbtBlue / TO_4_BIT;
        }
        starting_point.y = i;
        ERR_HANDLER((LCD_HÖHE < starting_point.y) && (starting_point.y > LCD_BREITE),
                    "starting_point: außerhalb des displays")
        ERR_HANDLER(width == sizeof(LCD_line_COLORS) / sizeof(uint16_t),
                    "LCD_line_COLORS: hat eine falsche größe")
        GUI_WriteLine(starting_point, width, LCD_line_COLORS);
    }
}
