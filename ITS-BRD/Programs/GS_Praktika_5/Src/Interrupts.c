#include "Interrrupts.h"
#include "FSM.h"
#include <stdio.h>
#include "stm32f4xx_hal.h"
#include "DisplayOut.h"
#include "output.h"

void init_interrupts() {
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;
	SYSCFG->EXTICR[0] &= ~(0x0f << (4*0));
	SYSCFG->EXTICR[0] |= 0x06 << (4*0);
	SYSCFG->EXTICR[0] &= ~(0x0f << (4*1));
	SYSCFG->EXTICR[0] |= 0x06 << (4*1);
	
	EXTI->RTSR |= (1); //select rising trigger for INT2
	EXTI->FTSR |= (1); //select falling trigger for INT2
	EXTI->FTSR |= (1 << 1);
	EXTI->RTSR |= (1 << 1);
	
	EXTI->IMR |= (1);//interrupt aktivieren
	EXTI->IMR |= (1<<1);//interrupt aktivieren
	
	NVIC_SetPriority(EXTI0_IRQn, 4);
	NVIC_SetPriority(EXTI1_IRQn, 4);
	
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI1_IRQn);
}

void kill_interrupts() {
	EXTI->IMR &= ~(1);//interrupt deaktivieren
	EXTI->IMR &= ~(1<<1);//interrupt deaktivieren
}

void aktivate_interrupts() {
	EXTI->IMR |= (1);//interrupt aktivieren
	EXTI->IMR |= (1<<1);//interrupt aktivieren
}

void EXTI0_IRQHandler(void) {
	setGPIOPin(GPIOE, 1, true);	
	set_fsm_state();
	EXTI->PR = (1);
	setGPIOPin(GPIOE, 1, false);
}

void EXTI1_IRQHandler(void) {
	setGPIOPin(GPIOE, 1, true);	
	set_fsm_state();
	EXTI->PR = (1<<1);
	setGPIOPin(GPIOE, 1, false);	
}