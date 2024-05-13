#ifndef __ZEITMESSUNG__H__
#define __ZEITMESSUNG__H__
#include "init.h"
#include "lcd.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "stm32f4xx_hal.h"
 
 
/**
* Initialisiert den Timer
*/
void initZeitmessung();
 
/**
* Liefert eine Zeitspanne 
*/
double getZeitstempel();
 
/**
* Liefert die Zeitspanne zwischen Zeitstempel
* @return Zeit in Sekunde
*/
double getZeitspanne();
 
#endif