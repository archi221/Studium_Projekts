#ifndef __ZEITMESSUNG__H__
#define __ZEITMESSUNG__H__
#include "init.h"
#include "lcd.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "stm32f4xx_hal.h"
 
#define TIME_TO_SEK (1.0/90.0) * 1000
 
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