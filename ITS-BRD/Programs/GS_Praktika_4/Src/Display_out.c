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
    lcdGotoXY( 8, 0);
    lcdPrintS("PDROM");
    lcdGotoXY( 27, 0);
    lcdPrintS("Temp.  [C]");
}

void print_sensoren(sensor *sensoren, int anzahl) {
		
    for (int i = 0; i < anzahl; ++i) {
        lcdGotoXY( 0, i + 1);
        lcdPrintS(sensoren[i].typ);
				lcdGotoXY( 8, i + 1);
				sprintf(buffer, "0x%" PRIx64, sensoren[i].pdrom);
        lcdPrintS(buffer);
				snprintf(buffer, 7, "%3.6f", sensoren[i].temperatur);
				lcdGotoXY( 27, i + 1);
        lcdPrintS(buffer);			
    }
}