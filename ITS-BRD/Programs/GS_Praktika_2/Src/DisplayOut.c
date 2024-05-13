#include "DisplayOut.h"


int init_display(){
	
	lcdGotoXY( 0, 0);
	lcdPrintS("Drehwinkel:");
	lcdGotoXY( 0, 10);
 	lcdPrintS("Winkelg. ");
	
	return SUCCESS;
	}

	int setValues(int Winkel, int Winkelgeschwindigkeit){
	lcdGotoXY( 70, 0);
	lcdPrintInt(Winkel);
	lcdGotoXY( 70, 10);
	lcdPrintInt(Winkelgeschwindigkeit);
	return SUCCESS;
	}






