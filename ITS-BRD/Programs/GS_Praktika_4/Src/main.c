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

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
	initITSboard(); // Initialisierung des ITS Boards
    init_display(); // Initialisierung des Displays

	lcdPrintS("Viel Spass mit dem ITS Board.");
	printf("Viel Spass mit dem ITS Board.\r\n");
	delay(3000);

}

// EOF
