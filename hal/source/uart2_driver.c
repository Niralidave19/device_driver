/*
 * uart2_driver.c
 *
 *  Created on: Jul 1, 2025
 *      Author: niral
 */
#include"uart_types.h"
#include"uart_macros.h"
#include"stm32f446xx.h"

static uint8_t bytes[10];
void UART_clock(){
	UART2_clock_enable();
}
/* UART_GetPort() -
 * Returns a pointer, pointing to the address of the USART2 peripheral
 */
volatile UART_Reg_def_t* UART_GetPort(){
	return (volatile UART_Reg_def_t*)USART2_BASE_ADDRESS;
}

void USART_Init(UART_config_t UART_config)
{
	/*Get the peripheral address of USART */
	volatile UART_Reg_def_t* USART = UART_GetPort();

	/* Set the baud rate: No. of bits/sec
	 * PCLK : Clock driving the UART peripheral : basically the APB1 Bus clock
	 * Each bus clock is derived from system clock */
	//USART->usart_brr = (UART_config.pclk + (UART_config.baud / 2)) / UART_config.baud;
	//USART->usart_brr = RCC->rcc_cfgr
	USART->usart_brr = 0x683;
	/* General init configuration required for any UART peripheral
	 * Enable UART peripheral, Transmitter enable, receiver enable,
	 * set word length, parity
	 */
	/*USART->usart_cr1 =  (1 << 13) |  // UE: USART Enable
            			(1 << 3)  |  // TE: Transmitter enable
						(1 << 2)  |  // RE: Receiver enable
						(1 << 12) |  // word length set to 1 - 9 bits transmitted
						(1 << 10) |  //parity control enable
						(1 << 9);    //even parity*/
	USART->usart_cr1 =  (1 << 13) |  // UE: USART Enable
	            	    (1 << 3)  |  // TE: Transmitter enable
						(1 << 2)  ;  // RE: Receiver enable

	/*If USART Needs to be configured as synchronous
	 * Send the CLKEN bit to 1 in CR2
	 * If USART needs to be asynchronous, don't configure clock/set the bit to be 0 */
	 //USART->usart_cr2 = 0;
	 if(UART_config.enable_clk_cntrl){
		 USART->usart_cr2 |= (1 << 11);  // CLKEN - Enable SCLK Pin
		 USART->usart_cr2 &= ~(1 << 10); // CPOL = 0
		 USART->usart_cr2 &= ~(1 << 9);  // CPHA = 0
	 }

	 /*If USART needs flow control, we enable else disable
	  *If communicating with a strict device, with timings and buffers
	  * flow control is required. */
	 //USART->usart_cr3 = 0;
	 if(UART_config.enable_flow_cntrl){
		 USART->usart_cr3  |= (1 << 8);  // CTSE
		 USART->usart_cr3  |= (1 << 9);   // RTSE
	 }
}
void uart_command(uint8_t *rx_buff)
{
	if((rx_buff[0]!=0x7E)||(rx_buff[9]!=0x7F)){
		return;
	}
	uint8_t cmd_id   = rx_buff[1];
	uint8_t length   = rx_buff[2];
	uint8_t* payload = &rx_buff[3];
	switch(cmd_id){
	/*Get data stored at a particular address */
	case 0x01:
		uint32_t addr = payload[0] | payload[1]<<8 | payload[2]<<16 | payload[3]<<24;
		uint32_t value = *((uint32_t*)addr);
		uint8_t* tx_buff = (uint8_t)value;
		USART2_Write(tx_buff,1);
	}
}
uint8_t* uart_receive(){
	/*Get the peripheral address of USART */
	volatile UART_Reg_def_t* USART = UART_GetPort();

	uint32_t address;
	/* Polling is used for reading the data
	 * In this method, we tell the processor to keep checking the RXNE bit (5th bit of SR reg)
	 * if the bit is set we read the data from the DR register
	 */
	/* Assuming 10 Bytes of data are received in one single frame */
	for(int i = 0;i<10;i++)
	{
		while(!((USART->usart_sr) & (1<<5)));
		bytes[i] = (uint8_t)USART->usart_dr & 0xFF;
	}
	address = bytes[0] | bytes[1]<<8 | bytes[2]<<16 | bytes[3]<<24;
	uart_command(bytes);
	return bytes;
	/*
	 *
	while(!((USART->usart_sr) & (1<<5)))
		{
			uint8_t data = USART->usart_dr;
			printf("Received: 0x%02X\n", data);
		}*/

	/*we read the data once received and typecast it to uint8_t
	 *because we return only 8 bits of data */
	/*return (uint8_t)(USART->usart_dr & 0xFF);*/
}

void USART2_Write(uint8_t* ch,uint8_t size) {
	/*Get the peripheral address of USART */
	volatile UART_Reg_def_t* USART = UART_GetPort();
  // Wait until TXE == 1
	for(int i = 0;i<size;i++)
	{
	    while (!(USART->usart_sr & (1 << 7)));
		USART->usart_dr = ch[i];
	}
}



