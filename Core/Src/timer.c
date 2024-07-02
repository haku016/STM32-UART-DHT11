/*
 * timer.c
 *
 *  Created on: Apr 12, 2024
 *      Author: 19119
 */
#include "timer.h"
#include "stm32f4xx.h"
#include <stdint.h>

#define APB1_FREQ 42000000

void initTimer2(){
	RCC->APB1ENR |= (1<<0); //enable timer 2
	TIM2->PSC = 42000 - 1;
	TIM2->CR1 |= (1<<0); //enable counter for timer2
	TIM2->CNT = 0;// set the current counter value is 0
}
void delay_milli(unsigned int ms){
	unsigned int arr = (ms*(APB1_FREQ/1000))/(TIM2->PSC - 1);
	TIM2->ARR = arr;
	TIM2->CNT = 0; // Reset counter to 0
	TIM2->SR &= ~(1<<0); // Clear update flag
	TIM2->CR1 |= (1<<0); // Enable timer

	while(!(TIM2->SR & (1<<0))){};
	TIM2->CR1 &= ~(1<<0);
	TIM2->SR &= ~(1<<0);
}
void initTimer3(){
	RCC->APB1ENR |= (1<<1); //enable timer 3
	TIM3->PSC = 42 - 1;
	TIM3->CR1 |= (1<<0); //enable counter for timer3
	TIM3->CNT = 0;// set the current counter value is 0
}
void delay_micro(unsigned int micro){
	unsigned int arr = (micro*(APB1_FREQ/1000000))/(TIM3->PSC - 1);
	TIM3->ARR = arr;
	TIM3->CNT = 0; // Reset counter to 0
	TIM3->SR &= ~(1<<0); // Clear update flag
	TIM3->CR1 |= (1<<0); // Enable timer

	while(!(TIM3->SR & (1<<0))){};
	TIM3->CR1 &= ~(1<<0); // Disable timer
	TIM3->SR &= ~(1<<0);
}
