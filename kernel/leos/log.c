/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file log.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <drivers/uart/uart.h>
#include "log.h"

void
Log_init(void)
{
	UART_init();
}

int
Log_putS(const char *string)
{
	char c;
	const char *p = string;
	while((c = *p) != 0) {
		if (UART_put(c))
			return -1;
		p++;
	}
	return (int)(p - string);
}

int
Log_putI(int64_t value, uint8_t base)
{
	int result;

	if (value < 0) {
		if (UART_put('-'))
			return -1;
		value = -value;
		result = 1;
	} else {
		result = 0;
	}
	result += Log_putU(value, base);
	return (result) ? result : -1;
}

int
Log_putU(uint64_t value, uint8_t base)
{
	int i = 0, result;
	char buffer[64];

	if (!value) {
		return (UART_put('0')) ? -1 : 1;
	}

	do {
		uint64_t r;
		if (!(i < (sizeof(buffer) / sizeof(buffer[0]))))
			return -1;

		r = value % base;
		buffer[i++] = (r < 0x0A) ? '0' + r : 'A' + r - 0x0A;
    value /= base; 
	} while (value);

	result = i;

	while (i--) {
		if (UART_put(buffer[i]))
			return -1;
	}
	return result;
}
