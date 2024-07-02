/*
 * uart.h
 *
 *  Created on: May 31, 2024
 *      Author: 19119
 */

#ifndef INC_UART_H_
#define INC_UART_H_

void initUART();
void sendChar(char ch);
void sendString(const char* str);
void sendInteger(int num);
#endif /* INC_UART_H_ */
