#include "DisplayOut.h"
#include <stdlib.h>
#include <stdio.h>

char letzter_winkel[6] = {0};
char letzte_winkelgeschwindigkeit[5] = {0};

int init_display(){
	lcdGotoXY( 0, 1);
	lcdPrintS("Drehwinkel:");
	lcdGotoXY( 0, 2);
 	lcdPrintS("Winkelgeschwindigkeit:");
	setValues(0, 0);
	setValues(333.1, 10);
	setValues(0, 0);
	return SUCCESS;
	}

	int setValues(double Winkel, double Winkelgeschwindigkeit) {
	char winkel[6] = {0};
	char winkelgeschwindigkeit[5] = {0};
	snprintf(winkel, 6, "%3.1f", Winkel);
	snprintf(winkelgeschwindigkeit, 5, "%3.1f", Winkelgeschwindigkeit);
	for (int i = 0; 6 > i; i++) {
		if (winkel[i] != letzter_winkel[i]) {
			lcdGotoXY( 12 + i, 1);
			if (winkel[i] == 0) {
				lcdPrintC('0');
			}else {
				lcdPrintC(winkel[i]);
			}
			letzter_winkel[i] = winkel[i];
		}
	}
	for (int i = 0; 5 > i; i++) {
		if (winkelgeschwindigkeit[i] != letzte_winkelgeschwindigkeit[i]) {
			lcdGotoXY( 23 + i, 2);
			if (winkel[i] == 0) {
				lcdPrintC('0');
			}else {
			lcdPrintC(winkelgeschwindigkeit[i]);
			}
			letzte_winkelgeschwindigkeit[i] = winkelgeschwindigkeit[i];
		}
	}
	return SUCCESS;
	}

void	testing(int test) {
	lcdGotoXY( 0, 8);
	lcdPrintInt(test);
}




