/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file timer.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <aarch64/aarch64.h>
#include <drivers/soc/bcm2837/bcm2837.h>
#include <leos/log.h>
#include "timer.h"

#if CONFIG_ARM_TIMER == 1
const unsigned int m_interval = 500000000;
#else
const unsigned int m_interval = 200000;
#endif
unsigned int m_current = 0;

#define TIMER_ENABLE ((1 << 31) | (1 << 29) | (1 << 28))
#define TIMER_RELOAD 5000000

void
Timer_init(void)
{
#if CONFIG_ARM_TIMER == 1
	/* Route local timer to a core0 */
	AARCH64_LOCAL_INT_ROUTING &= ~0x03;
	/* Set up timer status control register */
	AARCH64_LOCAL_TIMER_STATCTL = TIMER_ENABLE | TIMER_RELOAD;
	/* clear interrupt flag and reload timer */
	AARCH64_LOCAL_TIMER_RECLR |= (1 << 31) | (1 << 30);
	/* Set timer interrupt control register */
	AARCH64_CORE0_TIMER_IRQCTL = (1 << 1); /* nCNTPNSIR1 - Non Secure*/

#else
	m_current = AArch64_getReg32(TIMER_CLO);
	m_current += m_interval;
	AArch64_setReg32(TIMER_C1, m_current);
#endif
}

void
Timer_incFromISR(void)
{
  m_current += m_interval;
#if CONFIG_ARM_TIMER == 1
	/* clear interrupt flag and reload timer */
//	AARCH64_LOCAL_TIMER_STATCTL |= TIMER_RELOAD;
	AARCH64_LOCAL_TIMER_RECLR |= (1 << 31) | (1 << 30);
#else
	AArch64_setReg32(TIMER_C1, m_current);
	AArch64_setReg32(TIMER_CS, TIMER_CS_M1);
#endif
}

uint32_t
Timer_getTicks(void)
{
	return m_current;
}
