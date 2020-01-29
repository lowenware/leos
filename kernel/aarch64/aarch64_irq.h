/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file aarch64_irq.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef AARCH64_IRQ_H_286AEC6E_325F_469E_B140_53DDDD63876C
#define AARCH64_IRQ_H_286AEC6E_325F_469E_B140_53DDDD63876C

#define EL1t_SYNC    0
#define EL1t_IRQ     1
#define EL1t_FIQ     2
#define EL1t_ERROR   3
#define EL1h_SYNC    4
#define EL1h_IRQ     5
#define EL1h_FIQ     6
#define EL1h_ERROR   7
#define EL0_64_SYNC  8
#define EL0_64_IRQ   9
#define EL0_64_FIQ   10
#define EL0_64_ERROR 11
#define EL0_32_SYNC  12
#define EL0_32_IRQ   13
#define EL0_32_FIQ   14
#define EL0_32_ERROR 15


#endif /* !AARCH64_IRQ_H */
