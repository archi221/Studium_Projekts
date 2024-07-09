#ifndef _DISPLAYOUT_H
#define	_DISPLAYOUT_H

#include "error_handeling.h"
#include "LCD_GUI.h"
#include "lcd.h"

void testing(int test);

int init_display();

void setValues(double Winkel,double Winkelgeschwindigkeit);

void reset_display();

#endif 
