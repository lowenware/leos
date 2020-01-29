/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file main.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <leos/irq.h>
#include <leos/leos.h>
#include <leos/log.h>
#include <leos/memory.h>
#include <leos/task.h>
#include <drivers/timer/timer.h>

void
Leos_demoTask1(void *arg);

void
Leos_demoTask2(void *arg);


void
Leos_run(void)
{
	Log_init();

	Log_putS("Starting LEOS (EL");
	Log_putI(AArch64_getEL(), 10);
	Log_putS(")\r\n");

	AArch64_init();

	IRQ_init();
	Timer_init();
	Memory_init();

	Task_initSheduler();

	IRQ_enable();

	if (Task_create(Leos_demoTask1, "T1") == -1)
		Log_putS("Task 1 was not created\r\n");
		
	if (Task_create(Leos_demoTask2, "T2") == -1)
		Log_putS("Task 2 was not created\r\n");


	for (;;) {
		Log_putS("I");
		Task_yield();
	}
}

void
Leos_demoTask2(void *arg)
{
	for (;;) {
		Log_putS("B");
		Task_yield();
	}
}
void
Leos_demoTask1(void *arg)
{
	for (;;) {
		Log_putS("A");
		Task_yield();
	}
}
