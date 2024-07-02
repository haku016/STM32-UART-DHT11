/*
 * dht11_test.c
 *
 *  Created on: Jun 3, 2024
 *      Author: 19119
 */

#include <dht11.h>
#include "stm32f4xx.h"
#include "timer.h"
#include <stdint.h>

#define DHT11_PORT GPIOD
#define DHT11_PIN  GPIO_PIN_2
#define DHT11_PIN_NUMBER 2

void delay_us(uint32_t us) {
    SysTick->LOAD = (SystemCoreClock / 1000000 - 1) * us;
    SysTick->VAL = 0;
    SysTick->CTRL = SysTick_CTRL_ENABLE_Msk;
    while (!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
    SysTick->CTRL = 0;
}

void DHT11_SetPinOutput(void) {
    DHT11_PORT->MODER |= (1U << (DHT11_PIN_NUMBER * 2));
}

void DHT11_SetPinInput(void) {
    DHT11_PORT->MODER &= ~(1U << (DHT11_PIN_NUMBER * 2));
}

void DHT11_Start(void) {
    DHT11_SetPinOutput();
    DHT11_PORT->ODR &= ~DHT11_PIN;
    delay_us(18000);
    DHT11_PORT->ODR |= DHT11_PIN;
    delay_us(20);
    DHT11_SetPinInput();
}

uint8_t DHT11_CheckResponse(void) {
    uint8_t response = 0;
    delay_us(40);
    if (!(DHT11_PORT->IDR & DHT11_PIN)) {
        delay_us(80);
        if (DHT11_PORT->IDR & DHT11_PIN) response = 1;
        delay_us(40);
    }
    return response;
}

uint8_t DHT11_ReadByte(void) {
    uint8_t data = 0;
    for (int i = 0; i < 8; i++) {
        while (!(DHT11_PORT->IDR & DHT11_PIN));
        delay_us(40);
        if (DHT11_PORT->IDR & DHT11_PIN) data |= (1 << (7 - i));
        while (DHT11_PORT->IDR & DHT11_PIN);
    }
    return data;
}

void DHT11_ReadData(uint8_t *humidity, uint8_t *temperature) {
    uint8_t hum_int, hum_dec, temp_int, temp_dec, checksum;
    DHT11_Start();
    if (DHT11_CheckResponse()) {
        hum_int = DHT11_ReadByte();
        hum_dec = DHT11_ReadByte();
        temp_int = DHT11_ReadByte();
        temp_dec = DHT11_ReadByte();
        checksum = DHT11_ReadByte();
        if ((hum_int + hum_dec + temp_int + temp_dec) == checksum) {
            *humidity = hum_int;
            *temperature = temp_int;
        }
    }
}

