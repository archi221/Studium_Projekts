#include "input_wrapper.h"
#include "LCD_GUI.h"
#include "LCD_wrapper.h"
#include <stdint.h>
#include "errorhandler.h"
#include <stdlib.h>

static Coordinate starting_point;

static uint16_t LCD_line_colors[LCD_BREITE];

void wrap_line (int von, int höhe, int anzahl, RGBTRIPLE *line) {
    starting_point.x = von;
    starting_point.y = höhe ;

    for (int j = 0; j < anzahl; ++j) {
        LCD_line_colors[j] = 0;
        LCD_line_colors[j] |= ((int) (line[j].rgbtRed / TO_4_BIT)) << 11;
        LCD_line_colors[j] |= ((int) (line[j].rgbtGreen / TO_5_BIT)) << 5;
        LCD_line_colors[j] |= (int) (line[j].rgbtBlue / TO_4_BIT);
    }
    GUI_WriteLine(starting_point, anzahl, LCD_line_colors);

}

void *get_line_adress() {
    return line;
}
