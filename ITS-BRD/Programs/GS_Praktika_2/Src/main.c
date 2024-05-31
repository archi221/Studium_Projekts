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
#include "lcd.h"
#include "output.h"
#include "timer.h"
#include "DisplayOut.h"
#include "zeitmessung.h"
#include "main.h"
#include "FSM.h"
#include "output.h"
#include "calculations.h"
#include <stdio.h>

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */
int main(void){
	initITSboard();                 // Initialisierung des ITS Boards
	GUI_init(DEFAULT_BRIGHTNESS);   // Initialisierung des LCD Boards mit Touch
	initZeitmessung();	// Initialisierung des Timers
	init_display();  // Initialisierung der Dysplay ausgabe
	get_first_phase();// auf erste phase warten
	//super loop
	while (true) {
			if (set_fsm_state()) {
				lcdGotoXY( 0, 9);
				lcdPrintS("Error Press button 6 to Reset");
				while(get_error_input()){}
				lcdGotoXY( 0, 9);
				lcdPrintS("                            ");
				reset_display();
				reset_calculations();
				reset_fsm();
				get_first_phase();
			}
	}
}
// EOF
