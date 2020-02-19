/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file aarch64_reg.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef AARCH64_REG_H_C74FE7BF_C8A6_4718_867A_C125CBF326BD
#define AARCH64_REG_H_C74FE7BF_C8A6_4718_867A_C125CBF326BD

#define AARCH64_LOCAL_INT_ROUTING *((uint32_t *) 0x40000024)

#define AARCH64_LOCAL_TIMER_STATCTL *((uint32_t *) 0x40000034)

#define AARCH64_LOCAL_TIMER_RECLR *((uint32_t *) 0x40000038)

/* Timers interrupt control registers 
 * */
#define AARCH64_CORE0_TIMER_IRQCTL *((uint32_t *) 0x40000040)
#define AARCH64_CORE1_TIMER_IRQCTL *((uint32_t *) 0x40000044)
#define AARCH64_CORE2_TIMER_IRQCTL *((uint32_t *) 0x40000048)
#define AARCH64_CORE3_TIMER_IRQCTL *((uint32_t *) 0x4000004C)

/* Timer interrupr routing 
 * */
#define AARCH64_TIMER0_IRQ 0x01
#define AARCH64_TIMER1_IRQ 0x02
#define AARCH64_TIMER2_IRQ 0x04
#define AARCH64_TIMER3_IRQ 0x08
#define AARCH64_TIMER0_FIQ 0x10
#define AARCH64_TIMER1_FIQ 0x20
#define AARCH64_TIMER2_FIQ 0x40
#define AARCH64_TIMER3_FIQ 0x80

/* Mailbox control registers 
 * */
#define AARCH64_CORE0_MBOX_IRQCTL *((uint32_t *) 0x40000050)
#define AARCH64_CORE1_MBOX_IRQCTL *((uint32_t *) 0x40000054)
#define AARCH64_CORE2_MBOX_IRQCTL *((uint32_t *) 0x40000058)
#define AARCH64_CORE3_MBOX_IRQCTL *((uint32_t *) 0x4000005C)

/* Mailbox interrupr routing 
 * */
#define AARCH64_MBOX0_IRQ 0x01
#define AARCH64_MBOX1_IRQ 0x02
#define AARCH64_MBOX2_IRQ 0x04
#define AARCH64_MBOX3_IRQ 0x08
#define AARCH64_MBOX0_FIQ 0x10
#define AARCH64_MBOX1_FIQ 0x20
#define AARCH64_MBOX2_FIQ 0x40
#define AARCH64_MBOX3_FIQ 0x80

/* Source registers for IRQ / FIQ
 * */
#define AARCH64_CORE0_IRQSRC *((uint32_t *) 0x40000060)
#define AARCH64_CORE1_IRQSRC *((uint32_t *) 0x40000064)
#define AARCH64_CORE2_IRQSRC *((uint32_t *) 0x40000068)
#define AARCH64_CORE3_IRQSRC *((uint32_t *) 0x4000006C)
#define AARCH64_CORE0_FIQSRC *((uint32_t *) 0x40000070)
#define AARCH64_CORE1_FIQSRC *((uint32_t *) 0x40000074)
#define AARCH64_CORE2_FIQSRC *((uint32_t *) 0x40000078)
#define AARCH64_CORE3_FIQSRC *((uint32_t *) 0x4000007C)

/* Interrupt source bits
 * */
#define AARCH64_TIMER0_INTSRC 0x0001
#define AARCH64_TIMER1_INTSRC 0x0002
#define AARCH64_TIMER2_INTSRC 0x0004
#define AARCH64_TIMER3_INTSRC 0x0008
#define AARCH64_MBOX0_INTSRC  0x0010
#define AARCH64_MBOX1_INTSRC  0x0020
#define AARCH64_MBOX2_INTSRC  0x0040
#define AARCH64_MBOX3_INTSRC  0x0080
#define AARCH64_GPU_INTSRC    0x0100
#define AARCH64_PMU_INTSRC    0x0200

/* Mailbox write-set registers (write only)
 * */
#define AARCH64_CORE0_MBOX0_SETREG *((uint32_t *) 0x40000080)
#define AARCH64_CORE0_MBOX1_SETREG *((uint32_t *) 0x40000084)
#define AARCH64_CORE0_MBOX2_SETREG *((uint32_t *) 0x40000088)
#define AARCH64_CORE0_MBOX3_SETREG *((uint32_t *) 0x4000008C)
#define AARCH64_CORE1_MBOX0_SETREG *((uint32_t *) 0x40000090)
#define AARCH64_CORE1_MBOX1_SETREG *((uint32_t *) 0x40000094)
#define AARCH64_CORE1_MBOX2_SETREG *((uint32_t *) 0x40000098)
#define AARCH64_CORE1_MBOX3_SETREG *((uint32_t *) 0x4000009C)
#define AARCH64_CORE2_MBOX0_SETREG *((uint32_t *) 0x400000A0)
#define AARCH64_CORE2_MBOX1_SETREG *((uint32_t *) 0x400000A4)
#define AARCH64_CORE2_MBOX2_SETREG *((uint32_t *) 0x400000A8)
#define AARCH64_CORE2_MBOX3_SETREG *((uint32_t *) 0x400000AC)
#define AARCH64_CORE3_MBOX0_SETREG *((uint32_t *) 0x400000B0)
#define AARCH64_CORE3_MBOX1_SETREG *((uint32_t *) 0x400000B4)
#define AARCH64_CORE3_MBOX2_SETREG *((uint32_t *) 0x400000B8)
#define AARCH64_CORE3_MBOX3_SETREG *((uint32_t *) 0x400000BC)

/* Mailbox write-clear registers (Read & Write)
 * */
#define AARCH64_CORE0_MBOX0_RDCLREG *((uint32_t *) 0x400000C0)
#define AARCH64_CORE0_MBOX1_RDCLREG *((uint32_t *) 0x400000C4)
#define AARCH64_CORE0_MBOX2_RDCLREG *((uint32_t *) 0x400000C8)
#define AARCH64_CORE0_MBOX3_RDCLREG *((uint32_t *) 0x400000CC)
#define AARCH64_CORE1_MBOX0_RDCLREG *((uint32_t *) 0x400000D0)
#define AARCH64_CORE1_MBOX1_RDCLREG *((uint32_t *) 0x400000D4)
#define AARCH64_CORE1_MBOX2_RDCLREG *((uint32_t *) 0x400000D8)
#define AARCH64_CORE1_MBOX3_RDCLREG *((uint32_t *) 0x400000DC)
#define AARCH64_CORE2_MBOX0_RDCLREG *((uint32_t *) 0x400000E0)
#define AARCH64_CORE2_MBOX1_RDCLREG *((uint32_t *) 0x400000E4)
#define AARCH64_CORE2_MBOX2_RDCLREG *((uint32_t *) 0x400000E8)
#define AARCH64_CORE2_MBOX3_RDCLREG *((uint32_t *) 0x400000EC)
#define AARCH64_CORE3_MBOX0_RDCLREG *((uint32_t *) 0x400000F0)
#define AARCH64_CORE3_MBOX1_RDCLREG *((uint32_t *) 0x400000F4)
#define AARCH64_CORE3_MBOX2_RDCLREG *((uint32_t *) 0x400000F8)
#define AARCH64_CORE3_MBOX3_RDCLREG *((uint32_t *) 0x400000FC)

#define AARCH64_PSR_MODE_EL0t 0x00000000
#define AARCH64_PSR_MODE_EL1t 0x00000004
#define AARCH64_PSR_MODE_EL1h 0x00000005
#define AARCH64_PSR_MODE_EL2t 0x00000008
#define AARCH64_PSR_MODE_EL2h 0x00000009
#define AARCH64_PSR_MODE_EL3t 0x0000000c
#define AARCH64_PSR_MODE_EL3h 0x0000000d

/* Saved Program Status Register (SPSR)
 * Exception Level 3 (EL3)
 * See page 389 of AArch64-Reference-Manual
 * */
#define SPSR_MASK_ALL (7 << 6)
#define SPSR_EL1h     (5 << 0)
#define SPSR_VALUE    (SPSR_MASK_ALL | SPSR_EL1h)

/* Secure Configuration Register (SCR)
 * Exception Level 3 (EL3)
 * See page 2648 of AArch64-Reference-Manual
 * */
#define SCR_RESERVED (3 << 4)
#define SCR_RW       (1 << 10)
#define SCR_NS       (1 << 0)
#define SCR_VALUE    (SCR_RESERVED | SCR_RW | SCR_NS)

/* Hypervisor Configuration Register (HCR)
 * Exception Level 2 (EL2)
 * See page 2487 of AArch64-Reference-Manual
 * */
#define HCR_RW    (1 << 31)
#define HCR_VALUE HCR_RW

/* System Control REgister (SCTLR_EL1)
 * Exception Level 1 (EL1)
 * See page 2654 of AArch64-Reference-Manual
 * */
#define SCTLR_RESERVED          (3 << 28) | (3 << 22) | (1 << 20) | (1 << 11)
#define SCTLR_EE_LITTLE_ENDIAN  (0 << 25)
#define SCTLR_EOE_LITTLE_ENDIAN (0 << 24)
#define SCTLR_I_CACHE_DISABLED  (0 << 12)
#define SCTLR_D_CACHE_DISABLED  (0 << 2)
#define SCTLR_MMU_DISABLED      (0 << 0)
#define SCTLR_MMU_ENABLED       (1 << 0)

#define SCTLR_VALUE_MMU_DISABLED (SCTLR_RESERVED | SCTLR_EE_LITTLE_ENDIAN \
		| SCTLR_I_CACHE_DISABLED | SCTLR_D_CACHE_DISABLED | SCTLR_MMU_DISABLED)


#endif /* !AARCH64_REG_H */
