#include "output.h"
#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "init.h"
#include "delay.h"
#include "LCD_GUI.h"
#include "lcd.h"
#include "error_handeling.h"

int phase;
int error_t = 0;

int phase_matrix[2][2] = {{PHASE_A, PHASE_D},
													{PHASE_B, PHASE_C}};

int setMODER(GPIO_TypeDef* GPIOx, int pin, bool io) {// true if input
	if ((pin <=0) || (pin >16)) {
		return OUT_OF_BOUNDS;
	}
	
	uint32_t moder_mask = (0x03U << (2*pin));
	uint32_t output_mask = (0x01U << (2*pin));
	
	if (io) { // Set to input
		GPIOx->MODER = GPIOx->MODER & ~moder_mask;
	} else {//Set to output
		GPIOx->MODER = (GPIOx->MODER & ~moder_mask) | output_mask;
	}
	return SUCCESS;
}

int setGPIOPin(GPIO_TypeDef* GPIOx, int pin, bool on) {
	//check if pin exist
	if ((pin < 0) || (pin > 16)) {
		return OUT_OF_BOUNDS;
	}
	int offset = (on) ? 0 : 16; //offset to acces reset bits
	
	GPIOx->BSRR = (0x01 << (pin + offset));
	return SUCCESS;
}

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin, int *pin_value) {
	//chekc if pin exist
	if ((pin < 0) || (pin > 16)) {
		return OUT_OF_BOUNDS;
	}
	*pin_value = (0x01 << pin) != (GPIOx->IDR & (0x01 << pin));
	return SUCCESS;
}

int read_all() {
	int channel_a, channel_b;
	if (readGPIOPin(GPIOF, 0, &channel_a)){
		return OUT_OF_BOUNDS;
	}
	if (readGPIOPin(GPIOF, 1, &channel_b)) {
		return OUT_OF_BOUNDS;
	}
	phase = phase_matrix [channel_a][channel_b];
//	lcdGotoXY( 0, 3);
	lcdPrintInt(phase);
	return SUCCESS;
}

int get_phase(int *phase_value) {
	if (phase == NULL) {
		return NO_ROTATION_YET;
	}
	*phase_value = phase;
	return SUCCESS;
}

int get_error_input() {
	int error_button;
		if (readGPIOPin(GPIOF, 7, &error_button)) {
		return OUT_OF_BOUNDS;
	}
	if (error_button){
		return SUCCESS;
	}
	return NOT_PRESSED;
}

int set_all(int pulse_count, bool direction) {
	if (direction) {
		setGPIOPin(GPIOE, 6, false);
		setGPIOPin(GPIOE, 7, true);
	}else {
		setGPIOPin(GPIOE, 7, false);
		setGPIOPin(GPIOE, 6, true);
	}
	//0 - 16 setting bits 16 - 32 resetting bits vom BSRR
	uint32_t pulse_count_32_bit = (pulse_count & 0xFFU);
	GPIOD->BSRR = pulse_count_32_bit;
	GPIOD->BSRR = (((~pulse_count_32_bit) | 0x0U) << 16);
	return SUCCESS;
}