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
#include "output.h"
#include "FSM.h"
#include <stdbool.h>
#include "Interrrupts.h"
#include "calculations.h"
#include "output.h"
#include "Zeitmessung.h"
#include "DisplayOut.h"

volatile int errno;
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
	errno = 0;
	init_output();
	init_interrupts();
	while (true) {
		uint32_t time = get_time();
		int pulse = get_pulse_count();
		uint32_t time_test = get_time();
		int pulse_test = get_pulse_count();
		if ((pulse_test != pulse) || (time_test != time)) {
			time = get_time();
			pulse = get_pulse_count();
		}
		set_all(pulse, get_dircetion());
		if (time >= WARTEZEIT) {
			print(pulse);
		}
		if (errno) {
			kill_interrupts();
			errno = 0;
			while(get_error_input()){}
			lcdGotoXY( 0, 9);
			lcdPrintS("                            ");
			reset_display();
			reset_calculations();
			reset_fsm();
			aktivate_interrupts();
		}
	}
}

// EOF
