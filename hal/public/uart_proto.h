/*
 * uart_proto.h
 *
 *  Created on: Jul 2, 2025
 *      Author: niral
 */

#ifndef PUBLIC_UART_PROTO_H_
#define PUBLIC_UART_PROTO_H_

#include<stdint.h>

volatile  UART_Reg_def_t* UART_GetPort();
void      USART_Init(UART_config_t UART_config);
uint32_t   uart_receive();
void USART2_Write(char ch);

#endif /* PUBLIC_UART_PROTO_H_ */
