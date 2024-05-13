#include "DisplayOut.h"


int init_display(){
	
	lcdGotoXY( 0, 1);
	lcdPrintS("Drehwinkel:");
	lcdGotoXY( 0, 2);
 	lcdPrintS("Winkelg. :");
	setValues(0, 0);
	return SUCCESS;
	}

	int setValues(int Winkel, int Winkelgeschwindigkeit){
	lcdGotoXY( 12, 1);
	lcdPrintInt(Winkel);
	lcdGotoXY( 11, 2);
	lcdPrintInt(Winkelgeschwindigkeit);
	return SUCCESS;
	}






