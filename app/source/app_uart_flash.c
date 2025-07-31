/*******************************************************************************************
 * File name: app_uart_flash.c
 * Description: The Client sends a flash file through UART, and this application moves the control to the sector
 * of flash memory where it has been flashed
 *******************************************************************************************/

#include <stdint.h>
#include "uart_proto.h"
#include "app_uart_flash_proto.h"

/* Receive request to flash data from client
 * Send ACK to client
 * Client sends no. of bytes of data
 * Clear memory segment and send ACK
 * Client sends 16 Bytes of data - and waits
 * Server checks if the data isn't corrupted and writes this data
 * Server sends ACK
 * Clients sends data ... process continues till no. of bytes reached
 */
