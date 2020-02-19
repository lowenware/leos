#include "aarch64_irq.h"
#include "aarch64_context.h"

.globl AArch64_init
AArch64_init:
	/* set vector table */
	adr x0, AArch64_vectors
	msr vbar_el1, x0
	mov x0, 0
	ret

.globl AArch64_getEL
AArch64_getEL:
	mrs x0, CurrentEL
	lsr x0, x0, 0x02
	ret

.globl AArch64_getReg32
AArch64_getReg32:
	ldr w0, [x0]
	ret

.globl AArch64_setReg32
AArch64_setReg32:
	str w1, [x0]
	ret

.globl AArch64_idle
AArch64_idle:
	subs x0, x0, 1
	bne AArch64_idle
	ret

/*
.globl AArch64_initIRQVector
AArch64_initIRQVector:
	ret
*/

.globl AArch64_enableIRQ
AArch64_enableIRQ:
	msr daifclr, 2
	ret

.globl AArch64_disableIRQ
AArch64_disableIRQ:
	msr daifset, 2
	ret

.globl AArch64_memzero
AArch64_memzero:
	str xzr, [x0], 8
	subs x1, x1, 8
	b.gt AArch64_memzero
	ret

/* TODO: Optimize */
.globl AArch64_memcpy
AArch64_memcpy:
	add x3, x1, x2
AArch64_memcpy_loop:
	cmp x3, x1
	beq AArch64_memcpy_return
	ldr x4, [x1], 8
	str x4, [x0], 8
	b AArch64_memcpy_loop
AArch64_memcpy_return:
	ret

/* Exceptions Vector Table
 * */
	.macro PUSH_CONTEXT
	sub sp, sp, AARCH64_CONTEXT_SIZE
	stp x0, x1, [sp, 16 * 0]
	stp x2, x3, [sp, 16 * 1]
	stp x4, x5, [sp, 16 * 2]
	stp x6, x7, [sp, 16 * 3]
	stp x8, x9, [sp, 16 * 4]
	stp x10, x11, [sp, 16 * 5]
	stp x12, x13, [sp, 16 * 6]
	stp x14, x15, [sp, 16 * 7]
	stp x16, x17, [sp, 16 * 8]
	stp x18, x19, [sp, 16 * 9]
	stp x20, x21, [sp, 16 * 10]
	stp x22, x23, [sp, 16 * 11]
	stp x24, x25, [sp, 16 * 12]
	stp x26, x27, [sp, 16 * 13]
	stp x28, x29, [sp, 16 * 14]

	mrs x22, elr_el1
	mrs x23, spsr_el1

	stp x30, x22, [sp, 16 * 15]
	str x23, [sp, 16 * 16]
	.endm

	.macro POP_CONTEXT
	ldr x23, [sp, 16 * 16]
	ldp x30, x22, [sp, 16 * 15]

	msr elr_el1, x22
	msr spsr_el1, x23

	ldp x28, x29, [sp, 16 * 14]
	ldp x26, x27, [sp, 16 * 13]
	ldp x24, x25, [sp, 16 * 12]
	ldp x22, x23, [sp, 16 * 11]
	ldp x20, x21, [sp, 16 * 10]
	ldp x18, x19, [sp, 16 * 9]
	ldp x16, x17, [sp, 16 * 8]
	ldp x14, x15, [sp, 16 * 7]
	ldp x12, x13, [sp, 16 * 6]
	ldp x10, x11, [sp, 16 * 5]
	ldp x8, x9, [sp, 16 * 4]
	ldp x6, x7, [sp, 16 * 3]
	ldp x4, x5, [sp, 16 * 2]
	ldp x2, x3, [sp, 16 * 1]
	ldp x0, x1, [sp, 16 * 0]
	add sp, sp, AARCH64_CONTEXT_SIZE
	.endm

	.macro VECTOR_ENTRY GOTO_LABEL
	.align 7
	b \GOTO_LABEL
	.endm

	.macro EXCEPTION_FALLBACK EID
	PUSH_CONTEXT
	mov x0, \EID
	mrs x1, esr_el1
	mrs x2, elr_el1
	bl IRQ_fallback
	b die
	.endm

die:
	b die

.globl AArch64_startTask 
AArch64_startTask:
	bl Task_unlockScheduler
	mov x0, x20
	blr x21
	
hang:
	/* todo: implement task exit here */
	WFE
	b hang

.globl AArch64_getPSR
AArch64_getPSR:
	mrs x23, NZCV
	mrs x3, DAIF
	orr x23, x23, x3
	/* mrs x3, CurrentEL */
	/* lsr x3, x3, 0x02 */
	/* orr x3, x3, 0x04 */
	orr x3, x23, x3
	orr x0, x0, x3
	ret


.align 11
.globl AArch64_vectors
AArch64_vectors:
	/* EL1t */
	VECTOR_ENTRY el1t_sync
	VECTOR_ENTRY el1t_irq
	VECTOR_ENTRY el1t_fiq
	VECTOR_ENTRY el1t_error
	/* EL1h */
	VECTOR_ENTRY el1h_sync
	VECTOR_ENTRY el1h_irq
	VECTOR_ENTRY el1h_fiq
	VECTOR_ENTRY el1h_error
	/* EL0 - 64bit */
	VECTOR_ENTRY el0_64_sync
	VECTOR_ENTRY el0_64_irq
	VECTOR_ENTRY el0_64_fiq
	VECTOR_ENTRY el0_64_error
	/* EL0 - 32bit */
	VECTOR_ENTRY el0_32_sync
	VECTOR_ENTRY el0_32_irq
	VECTOR_ENTRY el0_32_fiq
	VECTOR_ENTRY el0_32_error

el1t_sync:
	EXCEPTION_FALLBACK EL1t_SYNC

el1t_irq:
	EXCEPTION_FALLBACK EL1t_IRQ

el1t_fiq:
	EXCEPTION_FALLBACK EL1t_FIQ

el1t_error:
	EXCEPTION_FALLBACK EL1t_ERROR

el1h_sync:
	EXCEPTION_FALLBACK EL1h_SYNC

.globl AArch64_getSPSel
AArch64_getSPSel:
	mrs x0, SPSel
	ret

.globl AArch64_getSP_EL0
AArch64_getSP_EL0:
	mrs x0, sp_el0
	ret

.globl AArch64_getSP_EL1
AArch64_getSP_EL1:
	mrs x0, sp_el1
	ret

el1h_irq:
	PUSH_CONTEXT
	mov x0, sp
	bl Task_setStackPointer
	bl IRQ_onInterrupt
	bl Task_getStackPointer 
	mov x19, x0
	bl Task_getEL
	cbz x0, el1_irq_return_el0
/* return to EL1 */
	mov sp, x19
	b el1_irq_return
el1_irq_return_el0:
/* return to EL0 */
	sub sp, sp, AARCH64_CONTEXT_SIZE
	mov x0, sp
	mov x1, x19
	mov x2, AARCH64_CONTEXT_SIZE
	bl AArch64_memcpy
	add x0, x19, AARCH64_CONTEXT_SIZE
	msr sp_el0, x0
/* return from ISR */
el1_irq_return:
	POP_CONTEXT
	eret

el1h_fiq:
	EXCEPTION_FALLBACK EL1h_FIQ

el1h_error:
	EXCEPTION_FALLBACK EL1h_ERROR

el0_64_sync:
	EXCEPTION_FALLBACK EL0_64_SYNC

el0_64_irq:
	PUSH_CONTEXT
	/* save task context */
	mrs x0, sp_el0
	mov x1, sp
	mov x2, AARCH64_CONTEXT_SIZE
	sub x0, x0, x2
	mov x20, x0
	bl AArch64_memcpy
	mov x0, x20
	bl Task_setStackPointer
	bl IRQ_onInterrupt
	bl Task_getEL
	cbz x0, el0_irq_return_el0
/* return to EL1 task */
	bl Task_getStackPointer
	mov sp, x0
	b el0_irq_return
/* return to EL0 task */
el0_irq_return_el0:
	bl Task_getStackPointer
	mov x2, AARCH64_CONTEXT_SIZE
	add x20, x0, x2
	mov x1, x0
	mov x0, sp
	bl AArch64_memcpy
	msr sp_el0, x20
/* return from ISR */
el0_irq_return:
	POP_CONTEXT
	eret

el0_64_fiq:
	EXCEPTION_FALLBACK EL0_64_FIQ

el0_64_error:
	EXCEPTION_FALLBACK EL0_64_ERROR

el0_32_sync:
	EXCEPTION_FALLBACK EL0_32_SYNC

el0_32_irq:
	EXCEPTION_FALLBACK EL0_32_IRQ

el0_32_fiq:
	EXCEPTION_FALLBACK EL0_32_FIQ

el0_32_error:
	EXCEPTION_FALLBACK EL0_32_ERROR


