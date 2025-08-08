/*******************************************************************************************
 * File name: app_uart_flash.c
 * Description: The Client sends a flash file through UART, and this application moves the control to the sector
 * of flash memory where it has been flashed
 *******************************************************************************************/

#include <stdint.h>
#include "uart_proto.h"
#include "app_uart_proto.h"
#include"flash_types.h"
#include"stm32f446xx.h"
/* Receive request to flash data from client
 * Send ACK to client
 * Client sends no. of bytes of data and no. of records
 * Clear memory segment and send ACK
 * Client sends 16 Bytes of data - and waits
 * Server checks if the data isn't corrupted and writes this data
 * Server sends ACK
 * Clients sends data ... process continues till no. of bytes reached
 */

void check_receive(){
	uint8_t bytes[4];
	uint8_t count = 0;
	uint8_t length_of_data;
	uint8_t record_type;
	uint32_t address_offset;
	uint32_t size,record_size;
	/* receive the request frame ID */
	uint8_t rx_buff = app_req_frame();
	/* if request frame ID == 0x3
		 * Flash software */
	if(rx_buff == 0x3){
		/*send an ACK*/
		uart_write(0x1);
		/* Client sends total size of flash file and number of records */
		for(int i=0;i<4;i++){
			bytes[i] = uart_receive();
		}
		/*first two bytes is size*/
		size = bytes[0]<<8 | bytes[1];
		/*second two bytes is number of records*/
		record_size = bytes[2]<<8 | bytes[3];
		while((record_size)!=0){
				for(int i = 0;i<4;i++){
						bytes[i] = uart_receive();
				}
				length_of_data = bytes[0];
				address_offset = bytes[1] << 8 | bytes[2];
				record_type    = bytes[3];
				uint8_t data[length_of_data];
				for(int i=0;i<length_of_data;i++)
				{
					data[i] = uart_receive();
				}
				record_size--;
			}
	}
	else{
		/*send NACK*/
		uart_write(0x4);
	}




	/*
	for(int i=0; i<length_of_data ; i++)
	{
		*((uint8_t *)(START_ADDR + address_offset + i)) = (uint8_t)data[4+i];
	}*/
}

void app_uart_flash_update(){

    uint8_t data[32];
	/*sector erase*/
    /* Unlock flash */
    /* wait till FLash CR is unlocked */
    while(FLASH->CR & FLASH_CR_LOCK);
    /* Code reaching here indicates FLASH CR is unlocked */

    /* Wait till operation over */
    while(FLASH->SR & FLASH_SR_BSY);
    /* If interrupts are enabled check for EOP */

    /* Write a byte to flash */
    /* Set PSIZE (00 for byte writing) */
    /* CLear 8th and 9th bit */
    FLASH->CR &= ~(0x3 << FLASH_CR_PSIZE);
    /* Set bits to correct value (0 in case of byte writing) */
    FLASH->CR |= 0 << FLASH_CR_PSIZE;

    /* sector erase */
    /* wait for flash operation to end */
    while(FLASH->SR & FLASH_SR_BSY);
    /* SER bit set */
    FLASH->CR |= FLASH_CR_SER;
    /* Clear SNB */
    FLASH->CR &= ~(0xF << FLASH_CR_SNB);
    /* Select sector 7 in SNB */
    FLASH->CR |= (0x7 << FLASH_CR_SNB);
    /* Start Sector clear */
    FLASH->CR |= FLASH_CR_START;
    /* Wait for end of operation */
    while(FLASH->SR & FLASH_SR_BSY);
    /* Clear SER */
    FLASH->CR &= ~(FLASH_CR_SER);
    /* Clear SNB */
    FLASH->CR &= ~(0xF << FLASH_CR_SNB);
    /* START gets cleared automatically */
    /* Set programming bit */
    FLASH->CR |= FLASH_CR_PG;



	/* Server sends ACK indicating flash sector is erased - send data */
	app_send_ACK();
}
