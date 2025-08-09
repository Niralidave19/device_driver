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

unsigned char check_crc(unsigned int data, unsigned char framechkseq) {
    /*
     * Check if the CRC is valid for the given data.
        * :param data: The input data 32 bit long.
        * :param framechkseq: The frame check sequence, which is a 1 byte long value and should be >= 0x80.
     * :return: True if the CRC is valid, False otherwise.
     */
    unsigned char cnt = 31, bitpos;
    unsigned int rem, num;
    if (data < framechkseq) return 0;
    /* Find first non zero bit */
    while((data & (1 << cnt)) == 0) cnt--;
    /* initialize bit position */
    bitpos = cnt - 7;
    num = (data & (0xFFU << bitpos)) >> bitpos;
    rem = framechkseq;
    while(num >= (1 << 7)){
        rem = num ^ framechkseq;
        while(bitpos > 0) {
            bitpos --;
            rem = (rem << 1) | ((data & (1 << bitpos)) >> bitpos);
            if (rem  >= (1 << 7)) break;
        }
        num = rem & 0xFF;
    }
    return (rem == 0);
}

void check_receive(){
	uint8_t bytes[12];
	uint8_t count = 0;
	uint32_t size;
	unsigned char crc;
	uint32_t temp = 0xFFFFFF;
	/* receive the request frame ID */
	uint8_t rx_buff = app_req_frame();
	/* if request frame ID == 0x3 Flash software */
	if(rx_buff == 0x3){
		/*send an ACK*/
		uart_write(0x1);
		/* Client sends total size of flash file */
		for(int i=0;i<2;i++){
			bytes[i] = uart_receive();
		}
		/*erase sector*/
		size = bytes[0]<<8 | bytes[1];
		while(size/4 != 0){
			/*get 3 bytes of data and 1 byte CRC */
			for(int i=0;i<4;i++){
				bytes[i] = uart_receive();
			}
			/*convert four bytes into an integer */
			for(int i=0;i<4;i++)
			{
				uint32_t num = (bytes[i]<<24) | (bytes[i+1]<<16) | (bytes[i+2]<<8) | (bytes[i+3]);
				/*check for CRC*/
				crc = check_crc(num,0b10101010);
				if(crc == 1){
					num = (num & (temp << 7)) >> 7;
				}
				else{
					uart_write(0x4);
				}
			}
			size--;
		}
	}
	else{
		/*send NACK*/
		uart_write(0x4);
	}
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
