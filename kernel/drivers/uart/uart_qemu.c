/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file uart.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include "uart_qemu.h"

#define UARTQEMU_BASE 0x09000000;

volatile unsigned int *UART0 = (unsigned int *)UARTQEMU_BASE;

int
UARTQEMU_put(unsigned char c)
{
	*UART0 = (unsigned int) c;
	return 0;
}

