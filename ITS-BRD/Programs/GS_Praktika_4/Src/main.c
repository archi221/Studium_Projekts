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
#include "lcd.h"
#include "LCD_GUI.h"
#include "errorhandler.h"
#include "IO_wrapper.h"

#define A3

sensor sensoren[5];
int anzahl_sensoren = 0;

/**
  * @brief  Main program
  * @param  None
  * @retval None
  */

int main(void) {
    initITSboard(); // Initialisierung des ITS Boards
    init_display(); // Initialisierung des Displays
    initZeitmessung();
    init_mode(OPEN_DRAIN);

#ifdef A1
    LOOP_ON_ERR(EOK == write_reset(), "init_mode: kein sklave");
    write_byte(0x33);
    read_bytes(sensoren[0].pdrom, 8);
    anzahl_sensoren++;
    ERR_HANDLER(!check_CRC(sensoren[0].pdrom, 8), "CRC falsch");
    sensoren[0].temperatur = 0;
    print_sensoren(sensoren, anzahl_sensoren);
#endif
#ifdef A2
    sensoren[0].pdrom[0] = 0x28;
    sensoren[0].pdrom[1] = 0x73;
    sensoren[0].pdrom[2] = 0xb4;
    sensoren[0].pdrom[3] = 0x87;
    sensoren[0].pdrom[4] = 0x0d;
    sensoren[0].pdrom[5] = 0x00;
    sensoren[0].pdrom[6] = 0x00;
    sensoren[0].pdrom[7] = 0xc0;
    anzahl_sensoren++;
    while (true) {
        LOOP_ON_ERR(EOK == write_reset(), "init_mode: kein sklave");
        write_byte(0x55);
        write_bytes(sensoren[0].pdrom, 8);
        write_byte(0x44);
        init_mode(PUSH_PULL);
        sleep(750 * 1000);
        init_mode(OPEN_DRAIN);
        LOOP_ON_ERR(EOK == write_reset(), "init_mode: kein sklave");
        write_byte(0x55);
        write_bytes(sensoren[0].pdrom, 8);
        write_byte(0xBE);
        read_temperature(&sensoren[0].temperatur);
        print_sensoren(sensoren, anzahl_sensoren);
    }
#else
    printf("\nFIND ALL\n");
    int cnt = 0;
    int rslt = OWFirst();
    while (rslt) {
// print device found
        for (int i = 7; i >= 0; i--) {
            printf("%02X", ROM_NO[i]);
        }
        cnt++;
        rslt = OWNext();
    }
#endif
}

// EOF
