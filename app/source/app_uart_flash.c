/*******************************************************************************************
 * File name: app_uart_flash.c
 * Description: The Client sends a flash file through UART, and this application moves the control to the sector
 * of flash memory where it has been flashed
 *******************************************************************************************/

#include <stdint.h>
#include "uart_proto.h"
#include "app_uart_proto.h"
/* Receive request to flash data from client
 * Send ACK to client
 * Client sends no. of bytes of data
 * Clear memory segment and send ACK
 * Client sends 16 Bytes of data - and waits
 * Server checks if the data isn't corrupted and writes this data
 * Server sends ACK
 * Clients sends data ... process continues till no. of bytes reached
 */

void app_uart_flash_update(){
	/* receive the request frame ID */
	uint8_t rx_buff = app_req_frame();
	uint32_t size;
	/* if request frame ID == 0x3
	 * Flash software */
	if(rx_buff == 0x3){
		/*send an ACK*/
		app_send_ACK();
	}
	/* Client sends total size of flash file */

	/*sector erase*/

	/* Server sends ACK indicating flash sector is erased - send data */
	app_send_ACK();
}
