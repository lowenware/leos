/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file UARTMini.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <aarch64/aarch64.h>
#include <drivers/soc/bcm2837/bcm2837.h>

#include "uart_mini.h"


int
UARTMini_init(void)
{
	unsigned int sel;

	/* Enable UART Mini and its registers*/
	AArch64_setReg32(AUX_ENABLES, 1);
	/* Disable TX and RX interrupts */
	AArch64_setReg32(AUX_MU_IER_REG, 0);
	/* Disable auto flow control, TX and RX */
	AArch64_setReg32(AUX_MU_CNTL_REG, 0);
	/* Set 8bit mode */
	AArch64_setReg32(AUX_MU_LCR_REG, 3);
	/* Set RTS line HIGH */
	AArch64_setReg32(AUX_MU_MCR_REG, 0);
	/* Set baud rate 115200 */
	AArch64_setReg32(AUX_MU_IER_REG, 0);
	AArch64_setReg32(AUX_MU_IIR_REG, 0xC6);
	AArch64_setReg32(AUX_MU_BAUD_REG, 270);

	sel = AArch64_getReg32(GPFSEL1);
	/* clean and set ALT5 for GPIO14 */
	sel &= ~(7 << 12);
	sel |= (2 << 12);
	/* clean and set ALT5 for GPIO15 */
	sel &= ~(7 << 15);
	sel |= (2 << 15);
	AArch64_setReg32(GPFSEL1, sel);

	AArch64_setReg32(GPPUD, 0);
	AArch64_idle(150);
	AArch64_setReg32(GPPUDCLK0, (1 << 14) | (1 << 15));
	AArch64_idle(150);
	AArch64_setReg32(GPPUDCLK0, 0);

	/* Enable TX and RX */
	AArch64_setReg32(AUX_MU_CNTL_REG, 3);

	return 0;
}

int
UARTMini_put(char c)
{
	while (1) {
		if (AArch64_getReg32(AUX_MU_LSR_REG) & 0x20)
			break;
	}
	AArch64_setReg32(AUX_MU_IO_REG, c);

	return 0;
}

int
UARTMini_get(char *pc)
{
	while (1) {
		if (AArch64_getReg32(AUX_MU_LSR_REG) & 0x01)
			break;
	}
	*pc = AArch64_getReg32(AUX_MU_IO_REG) & 0xFF;
	return 0;
}
