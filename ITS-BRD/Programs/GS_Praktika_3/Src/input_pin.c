#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "lcd.h"

int readGPIOPin(GPIO_TypeDef *GPIOx, int pin, int *pin_value) {
    //chekc if pin exist
    *pin_value = (0x01 << pin) != (GPIOx->IDR & (0x01 << pin));
    return SUCCESS;
}