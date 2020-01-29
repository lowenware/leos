
#include "aarch64_reg.h"

.section ".text.boot"
.globl _start

_start:
	mrs x0, mpidr_el1       /* Check CPU ID */
	mov x1, 0xC1000000
	bic x0, x0, x1
	cbz x0, set_el
idle:
	b idle

set_el:
	/* set SCTRL_EL1 */
	ldr x0, =SCTLR_VALUE_MMU_DISABLED
	msr sctlr_el1, x0
	/* set HCR_EL2 */
	ldr x0, =HCR_VALUE
	msr hcr_el2, x0
	/* set SCR_EL3 */
	ldr x0, =SCR_VALUE
	msr scr_el3, x0
	/* set SPSR_EL3 */
	ldr x0, =SPSR_VALUE
	msr spsr_el3, x0
	/* set elr_el3 */
	adr x0, set_stack
	msr elr_el3, x0
	eret

set_stack:
	ldr x30, =ld_stackPtr  /* defined in aarch64.ld */
	mov sp,  x30
	bl skip
skip:
	bl  Leos_run
hang: b hang


