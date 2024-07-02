#include <main.h>
#include "stm32f4xx.h"
#include <stdint.h>
#include "timer.h"
#include "clock_config.h"
#include "stm32f4xx_hal_rcc.h"
#include "uart.h"
#include "dht11.h"

#define APB1_FREQ 42000000
#define BAUD_RATE 9600

int main(){
	clockConfig();
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
	initTimer2();
	initTimer3();
	initUART();
	uint8_t temperature=0, humidity=0;

	while (1){
		sendString("Measuring...");
		DHT11_ReadData(&humidity, &temperature);
		sendString("Temperature: ");
		sendInteger(temperature);
		sendString("Humidity: ");
		sendInteger(humidity);
		delay_milli(2000);
	}
    return 0;
}
