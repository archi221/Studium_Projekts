#ifndef _OUTPUT_H
#define	_OUTPUT_H

#include <stdio.h>
#include "stm32f4xx_hal.h"
#include <stdbool.h>

#define PHASE_A 0
#define PHASE_B 1
#define PHASE_C 2
#define PHASE_D 3


int setMODER(GPIO_TypeDef* GPIOx, int pin, bool io);

int setGPIOPin(GPIO_TypeDef* GPIOx, int pin, bool on);

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin, int *pin_value);

int get_phase(int *phase_value);

int get_error();

int read_all();

int set_all(int pulse_count, bool direction);

int get_error_input();

#endif 