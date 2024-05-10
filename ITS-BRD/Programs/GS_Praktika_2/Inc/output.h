#ifndef _OUTPUT_H
#define	_OUTPUT_H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "lcd.h"

#define OUT_OF_BOUNDS 21
#define SUCCESS 0

int setMODER(GPIO_TypeDef* GPIOx, int pin, bool io);

int setGPIOPin(GPIO_TypeDef* GPIOx, int pin, bool on);

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin);

#endif 