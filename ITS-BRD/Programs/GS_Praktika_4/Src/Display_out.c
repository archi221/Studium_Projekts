#include "Display_out.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "stdio.h"
#include <inttypes.h>
#include <string.h>

static uint64_t lastpdroms[5];
static int last_anzahl = 0;
static char buffer[30];

void init_display() {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY(0, 0);
    lcdPrintS("Sensoren");
    lcdGotoXY(9, 0);
    lcdPrintS("PDROM");
    lcdGotoXY(30, 0);
    lcdPrintS("Temp.  [C]");
}

void print_sensoren(sensor *sensoren, int anzahl) {
    uint64_t pdrom = 0;
    for (int i = 0; i < anzahl; ++i) {
			  for (int j = 0; j < 8; ++j) {
            pdrom |= ((uint64_t) sensoren[i].pdrom[7 - j] << (j * 8));
        }
				if (lastpdroms[i] != pdrom) {
					lastpdroms[i] = pdrom;
					lcdGotoXY(0, i + 1);
					if (sensoren[i].pdrom[0] == 0x28) {
							strncpy(buffer, "DS18S20", 8);
					} else if (sensoren[i].pdrom[0] == 0x10) {
							strncpy(buffer, "DS18S20", 8);
					} else {
							strncpy(buffer, "unknown", 8);
					}
					lcdPrintS(buffer);
					lcdGotoXY(9, i + 1);
					sprintf(buffer, "0x%"PRIx64, pdrom);
					lcdPrintS(buffer);
			}
        
        snprintf(buffer, 9, "%3.6f", sensoren[i].temperatur);
        lcdGotoXY(30, i + 1);
        lcdPrintS(buffer);
    }
		if (last_anzahl > anzahl) {
			for (int i = 0; i < (last_anzahl - anzahl); ++i) {
				lcdGotoXY(0, i + anzahl + 1);
				lcdPrintlnS("                        ");
				lastpdroms[i + anzahl] = 0;
			}
		}
		last_anzahl = anzahl;
}