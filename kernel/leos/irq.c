/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file irq.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <drivers/soc/bcm2837/bcm2837.h>
#include <drivers/timer/timer.h>
#include "log.h"
#include "task.h"
#include "irq.h"

static const char *m_types[] = {
	"EL1t_SYNC",
	"EL1t_IRQ",
	"EL1t_FIQ",
	"EL1t_ERROR",
	"EL1h_SYNC",
	"EL1h_IRQ",
	"EL1h_FIQ",
	"EL1h_ERROR",
	"EL0_64_SYNC",
	"EL0_64_IRQ",
	"EL0_64_FIQ",
	"EL0_64_ERROR",
	"EL0_32_SYNC",
	"EL0_32_IRQ",
	"EL0_32_FIQ",
	"EL0_32_ERROR"
};


static void
IRQ_onTimerInterrupt(void)
{
	Timer_incFromISR();
	Task_scheduleFromISR();
}

void
IRQ_init()
{
	AArch64_setReg32(ENABLE_IRQS_1, SYSTEM_TIMER_IRQ_1);
}

void
IRQ_onInterrupt(void)
{
	unsigned int irq = AArch64_getReg32(IRQ_PENDING_1);

	switch(irq) {
#if CONFIG_ARM_TIMER == 1
	case LOCAL_TIMER_IRQ:
#endif
	case SYSTEM_TIMER_IRQ_1:
		return IRQ_onTimerInterrupt();

	default:
		Log_putS("Unhandled irq: ");
		Log_putU(irq, 16);
		Log_putS("\n");
	}
}

void
IRQ_fallback(int type, unsigned long esr, unsigned long address)
{
	Log_putS(m_types[type]);
	Log_putS(" -> ESR: ");
	Log_putU(esr, 16);
	Log_putS(", address: ");
	Log_putU(address, 16);
	Log_putS("\r\n");
}
