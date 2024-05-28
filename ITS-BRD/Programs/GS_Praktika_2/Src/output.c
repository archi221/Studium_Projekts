#include "output.h"

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
	if ((pin <= 0) || (pin > 16)) {
		return OUT_OF_BOUNDS;
	}
	int offset = (on) ? 0 : 16; //offset to acces reset bits
	
	GPIOx->BSRR = (0x01 << (pin + offset));
	return SUCCESS;
}

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin, int *pin_value) {
	//chekc if pin exist
	if ((pin <= 0) || (pin > 16)) {
		return OUT_OF_BOUNDS;
	}
	*pin_value = (0x01 << pin) != (GPIOx->IDR & (0x01 << pin));
	return SUCCESS;
}

int read_all() {
	int channel_a, channel_b, error_t;
	if (readGPIOPin(GPIOF, 0, &channel_a)){
		return OUT_OF_BOUNDS;
	}
	if (readGPIOPin(GPIOF, 1, &channel_b)) {
		return OUT_OF_BOUNDS;
	}
	if (readGPIOPin(GPIOF, 6, &error_t)) {
		return OUT_OF_BOUNDS;
	}
	phase = phase_matrix [channel_a][channel_b];
	return SUCCESS;
}

int get_phase(int *phase_value) {
	if (phase == NULL) {
		return NO_ROTATION_YET;
	}
	*phase_value = phase;
	return SUCCESS;
}

int get_error() {
	return error_t;
}

int set_all_outputs(int pulse_count, bool direction) {
	if (direction) {
		setGPIOPin(GPIOE, 6, false);
		setGPIOPin(GPIOE, 7, true);
	}else {
		setGPIOPin(GPIOE, 7, false);
		setGPIOPin(GPIOE, 6, true);
	}
	//0 - 16 setting bits 16 - 32 resetting bits vom BSRR
	uint32_t pulse_count_32_bit = (pulse_count & 0xFFU);
	pulse_count_32_bit = pulse_count_32_bit | (((!pulse_count_32_bit) & 0xFFU) << 16);
	GPIOD->BSRR = pulse_count_32_bit;
	return SUCCESS;
}