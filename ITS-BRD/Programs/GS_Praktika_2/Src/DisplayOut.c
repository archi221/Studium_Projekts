#include "DisplayOut.h"
#include <stdlib.h>
#include <stdio.h>

int init_display(){
	
	lcdGotoXY( 0, 1);
	lcdPrintS("Drehwinkel:");
	lcdGotoXY( 0, 2);
 	lcdPrintS("Winkelg. :");
	setValues(0, 0);
	return SUCCESS;
	}

	int setValues(double Winkel, double Winkelgeschwindigkeit){
	char buffer1[10] = {0};
	char buffer2[10] = {0};
	snprintf(buffer1, 10, "%4.2f", Winkel);
	snprintf(buffer2, 10, "%4.2f", Winkelgeschwindigkeit);
	for (int i = 0; 10 > i; i++) {
		lcdGotoXY( 12 + i, 1);
		lcdPrintC(buffer1[i]);
		if (buffer1[i+1] == 0) {
			break;
		}
	}
	for (int i = 0; 10 > i; i++) {
		lcdGotoXY( 11 + i, 2);
		lcdPrintC(buffer2[i]);
		if (buffer2[i+1] == 0) {
			break;
		}
	}
	return SUCCESS;
	}

void	testing(int test) {
	lcdGotoXY( 0, 3);
	lcdPrintInt(test);
}




