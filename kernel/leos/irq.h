/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file irq.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef IRQ_H_037ADD8D_3AAA_4541_A876_843DFF3A59E8
#define IRQ_H_037ADD8D_3AAA_4541_A876_843DFF3A59E8

#include <aarch64/aarch64.h>

void
IRQ_init(void);

void
IRQ_onInterrupt(void);

void
IRQ_fallback(int type, unsigned long esr, unsigned long address);

#define IRQ_enable(...) AArch64_enableIRQ(__VA_ARGS__)

#define IRQ_disable(...) AArch64_disableIRQ(__VA_ARGS__)

#endif /* !IRQ_H */
