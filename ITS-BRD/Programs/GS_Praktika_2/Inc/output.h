#ifndef _OUTPUT_H
#define	_OUTPUT_H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "error_handeling.h"

#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3


int setMODER(GPIO_TypeDef* GPIOx, int pin, bool io);

int setGPIOPin(GPIO_TypeDef* GPIOx, int pin, bool on);

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin, int *pin_value);

#endif 