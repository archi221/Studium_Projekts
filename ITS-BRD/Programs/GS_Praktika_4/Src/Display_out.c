#include "Display_out.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "stdio.h"
#include <inttypes.h>

char buffer[30];

void init_display() {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY( 0, 0);
    lcdPrintS("Sensoren");
    lcdGotoXY( 9, 0);
    lcdPrintS("PDROM");
    lcdGotoXY( 30, 0);
    lcdPrintS("Temp.  [C]");
}

void print_sensoren(sensor *sensoren, int anzahl) {
		uint64_t pdrom = 0;
    for (int i = 0; i < anzahl; ++i) {
        lcdGotoXY( 0, i + 1);
				
				lcdGotoXY( 9, i + 1);
				for (int j = 0; j < 8; ++j) {
						pdrom |= ((uint64_t) sensoren[i].pdrom[j] << (j * 8));
				}
				sprintf(buffer, "0x%" PRIx64, pdrom);
        lcdPrintS(buffer);
				snprintf(buffer, 9, "%3.6f", sensoren[i].temperatur);
				lcdGotoXY( 30, i + 1);
        lcdPrintS(buffer);			
    }
}