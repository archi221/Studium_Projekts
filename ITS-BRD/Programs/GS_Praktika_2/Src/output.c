#include "output.h"

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

int readGPIOPin(GPIO_TypeDef* GPIOx, int pin) {
	//chekc if pin exist
	if ((pin <= 0) || (pin > 16)) {
		return OUT_OF_BOUNDS;
	}
	return (0x01 << pin) != (GPIOx->IDR & (0x01 << pin));
}