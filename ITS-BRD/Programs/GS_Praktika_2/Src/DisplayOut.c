#include "DisplayOut.h"
#include <stdlib.h>
#include <stdio.h>
#include "FSM.h"

static char letzter_winkel[8] = {0};
static char letzte_winkelgeschwindigkeit[8] = {0};

int init_display(){
	lcdSetFont(12);
	lcdGotoXY( 0, 1);
	lcdPrintS("Drehwinkel:");
	lcdGotoXY( 0, 2);
 	lcdPrintS("Winkelgeschwindigkeit:");
	reset_display();
	return SUCCESS;
}

int setValues(double Winkel, double Winkelgeschwindigkeit) {
char winkel[8] = {0};
char winkelgeschwindigkeit[8] = {0};
int errno = 0;
snprintf(winkel, 7, "%3.1f", Winkel);
snprintf(winkelgeschwindigkeit, 7, "%3.1f", Winkelgeschwindigkeit);
for (int i = 0; 5 > i; i++) {
	if (winkel[i] != letzter_winkel[i]) {
		lcdGotoXY( 12 + i, 1);
		if (winkel[i] == 0) {
			lcdPrintC('0');
			letzter_winkel[i] = '0';
		}else {
			lcdPrintC(winkel[i]);
			letzter_winkel[i] = winkel[i];
		}
		if (!errno){
			errno = set_fsm_state_while_print();
		}
	}
}
for (int i = 0; 5 > i; i++) {
	if (winkelgeschwindigkeit[i] != letzte_winkelgeschwindigkeit[i]) {
		lcdGotoXY( 23 + i, 2);
		if (winkelgeschwindigkeit[i] == 0) {
			lcdPrintC('0');
			letzte_winkelgeschwindigkeit[i] = '0';
		}else {
			lcdPrintC(winkelgeschwindigkeit[i]);
			letzte_winkelgeschwindigkeit[i] = winkelgeschwindigkeit[i];
		}
		if (!errno){
			errno = set_fsm_state_while_print();
		}
	}
}
return errno;
}

void reset_display() {
	for (int i = 0; 7 > i; i++) {
		letzter_winkel[i] = 0;
		letzte_winkelgeschwindigkeit[i] = 0;
		lcdGotoXY( 12 + i, 1);
		if (i == 1) {
			lcdPrintC('.');
		}else if (i < 5) {
			lcdPrintC('0');
		}
		lcdGotoXY( 23 + i, 2);
		if (i == 1) {
			lcdPrintC('.');
		}else if (i < 5) {
			lcdPrintC('0');
		}
	}
}
	
void	testing(int test) {
	lcdGotoXY( 0, 8);
	lcdPrintInt(test);
}




