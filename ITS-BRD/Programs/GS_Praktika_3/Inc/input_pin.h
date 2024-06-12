#ifndef __INPUT_PIN_H
#define __INPUT_PIN_H

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "lcd.h"

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin, int *pin_value);

#endif