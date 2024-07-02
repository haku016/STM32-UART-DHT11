/*
 * clock_config.c
 *
 *  Created on: Apr 23, 2024
 *      Author: 19119
 */
#include "stm32f4xx.h"
#include <stdint.h>
#include "clock_config.h"

#define PLL_M 4
#define PLL_N 168
#define PLL_P 2

void clockConfig(){
	RCC->CR |= RCC_CR_HSEON;
	while(!(RCC->CR & RCC_CR_HSERDY));

	//config PLL
	RCC->PLLCFGR = RCC->PLLCFGR = (PLL_M << RCC_PLLCFGR_PLLM_Pos) |(PLL_N << RCC_PLLCFGR_PLLN_Pos) |
            	   (((PLL_P >> 1) - 1) << RCC_PLLCFGR_PLLP_Pos) | (RCC_PLLCFGR_PLLSRC_HSE);
	//enable PLL
	RCC->CR |= RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY));

	// Configure Flash prefetch, instruction cache, data cache
	FLASH->ACR = FLASH_ACR_ICEN | FLASH_ACR_DCEN | FLASH_ACR_PRFTEN | FLASH_ACR_LATENCY_5WS;

	//choose PLL as clock source
	RCC->CFGR &= ~RCC_CFGR_SW;
	RCC->CFGR |= RCC_CFGR_SW_PLL;
	while((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

	//config prescaler
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1;
	RCC->CFGR |= RCC_CFGR_PPRE1_DIV4;
	RCC->CFGR |= RCC_CFGR_PPRE2_DIV2;
}

