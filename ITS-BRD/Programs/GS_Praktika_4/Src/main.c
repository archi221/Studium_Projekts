/**
 ******************************************************************************
 * @file    main.c
 * @author  TI Team
 *          HAW-Hamburg
 *          Labor für technische Informatik
 *          Berliner Tor  7
 *          D-20099 Hamburg
 * @version 1.1
 *
 * @date    17. Juli 2020
 * @brief   Rahmen fuer C Programme, die auf dem ITSboard ausgefuehrt werden.
 *
 *					25.04.2022 Tobias De Gasperis: printf hinzugefuegt
 ******************************************************************************
 */

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "LCD_Demos.h"
#include "lcd.h"
#include "fontsFLASH.h"
#include "LCD_Touch.h"
#include "error.h"
#include "Display_out.h"
#include "IO.h"
#include "sensoren.h"
#include "zeitmessung.h"
#include "errorhandler.h"

#define A1

unsigned char comands[20];
sensor sensoren[5];
int anzahl_sensoren = 0;
/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
	
int main(void){
	initITSboard(); // Initialisierung des ITS Boards
  init_display(); // Initialisierung des Displays
	initZeitmessung();
	#ifdef A1
	init_mode(OPEN_DRAIN);
	LOOP_ON_ERR(EOK == write_reset(), "init_mode: kein sklave");
	comands[0] = 0x3;
	comands[1] = 0x3;
	write_bytes(comands, 2);
	read_bytes(sensoren[0].pdrom, 8);
	for (int i = 0; i < 7; i++) {
		sensoren[0].sensor[i] = (char)sensoren[0].pdrom[i];
		sensoren[0].sensor[i] = 'a';
		sensoren[0].pdrom[i] = 'a';
	}
	anzahl_sensoren++;
	sensoren[0].temperatur = 0;
	print_sensoren(sensoren, anzahl_sensoren);
	#endif
	#ifdef A2
	#else
	#endif
}

// EOF
