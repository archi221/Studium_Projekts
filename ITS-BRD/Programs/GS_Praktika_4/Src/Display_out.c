#include "Display_out.h"

void init_display() {
    lcdGotoXY( 0, 1);
    lcdPrintS("Drehwinkel:");
    lcdGotoXY( 0, 2);
    lcdPrintS("Winkelgeschwindigkeit:");
}

void print_sensoren(uint64_t *sensoren, int anzahl);

void print_messungen(int *messungen, int anzahl);
