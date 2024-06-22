#include "Display_out.h"

void init_display() {
    GUI_init(DEFAULT_BRIGHTNESS);
    lcdGotoXY( 0, 0);
    lcdPrintS("Sensoren");
    lcdGotoXY( 8, 0);
    lcdPrintS("PDROM");
    lcdGotoXY( 27, 0);
    lcdPrintS("Temp.  [C]");
}

void print_sensoren(uint64_t *sensoren, int anzahl) {
    for (int i = 0; i < anzahl; ++i) {
        lcdGotoXY( 0, i + 1);
        lcdPrintS(sensoren[i]);
    }
}

void print_messungen(double *messungen, int anzahl) {
    for (int i = 0; i < anzahl; ++i) {
        lcdGotoXY( 27, i + 1);
        lcdPrintS(messungen[i]);
    }
}