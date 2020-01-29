/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file util.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef AARCH64_H_F3AA8888_CEB3_4C16_9835_C3F23B040BB5
#define AARCH64_H_F3AA8888_CEB3_4C16_9835_C3F23B040BB5

#include <leos/types.h>
#include "aarch64_reg.h"
#include "aarch64_irq.h"

extern unsigned int
AArch64_init(void);

extern unsigned int
AArch64_getEL(void);

extern unsigned int
AArch64_getReg32(unsigned long reg);

extern void
AArch64_setReg32(unsigned long reg, unsigned int value);

extern void
AArch64_idle(unsigned long cycles);

extern void
AArch64_enableIRQ(void);

extern void
AArch64_disableIRQ(void);

extern void
AArch64_memzero(void *addr, unsigned long size);

extern void
AArch64_startTask(void *arg, void *callback);

extern uint32_t
AArch64_getPState(void);

extern void
AArch64_switchContext(void *currentTask, void *nextTask);

#endif /* !AARCH64_H */
