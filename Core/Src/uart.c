/*
 * uart.c
 *
 *  Created on: May 31, 2024
 *      Author: 19119
 */
#include "uart.h"
#include "stm32f4xx.h"
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define APB1_FREQ 42000000
#define BAUD_RATE 9600

void initUART(){
    RCC->APB1ENR |= (1<<17); //enable USART 2
    RCC->AHB1ENR |= (1<<0); //enable port A

    GPIOA->MODER |= (2<<4)|(2<<6); //alternate function for pin 2 and pin 3 PA
    GPIOA->OSPEEDR |= (3<<4)|(3<<6); //highspeed mode
    GPIOA->AFR[0] |= (7<<8)|(7<<12); //enable usart alternate function for pin 2 pin 3;

    USART2->CR1 = 0x00; //clear all - Clear M, PCE, and PS bits

    USART2->BRR = (7<<0) | (273<<4);
    //USART2->BRR = SystemCoreClock / BAUD_RATE;//
//    uint32_t baudrate = 9600;
//    uint32_t pclk1 = 42000000; // Assuming APB1 clock is 42 MHz
//    uint32_t usartdiv = (pclk1 + (baudrate / 2U)) / baudrate; // Round to nearest integer
//    USART2->BRR = usartdiv;

    USART2->CR1 |= (1<<2)|(1<<3); //enable tx and rx of usart 2
    USART2->CR1 |= (1<<13); //enable bit UE == enable usart 2
}

void sendChar(char ch){
    // Wait until transmit data register is empty
    while (!(USART2->SR & USART_SR_TXE));
    // Send character
    USART2->DR = ch;
}

void sendString(const char* str){
    while (*str) {
        sendChar(*str++);
    }
}
void sendInteger(int num){
	char buffer[50];
	sprintf(buffer, "%d", num);
	sendString(buffer);
}
