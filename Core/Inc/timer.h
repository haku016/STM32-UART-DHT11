/*
 * timer.h
 *
 *  Created on: Apr 12, 2024
 *      Author: 19119
 */

#ifndef INC_TIMER_H_
#define INC_TIMER_H_

void initTimer2();
void initTimer3();
void delay_micro(unsigned int micro); //min value passing 10 for micro - pass 1 = 10 micro second
void delay_milli(unsigned int ms); //max value passing 65536

#endif /* INC_TIMER_H_ */
