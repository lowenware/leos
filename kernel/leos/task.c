/******************************************************************************
 *
 *                Copyright (c) 2017-2020 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file task.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <stdlib.h>
#include <aarch64/aarch64.h>
#include <drivers/soc/bcm2837/bcm2837.h>
#include <drivers/timer/timer.h>
#include "memory.h"
#include "log.h"
#include "task.h"

#define TASK_STATE_RUNNING 0
#define TASK_STATE_HALFCYCLE (1 << 8)

#ifndef CONFIG_IDLE_TASK_STACK_SIZE
#define CONFIG_IDLE_TASK_STACK_SIZE 0x4000
#endif

struct Task {
	void *sp;
	void *stackStart;
	uint32_t pid;
	uint32_t stackSize;
	uint32_t lock;
	uint32_t counter;
	uint32_t cycles;
	int32_t priority;
	uint32_t state;
	uint32_t options;
	char name[CONFIG_TASK_MAX_NAME_LEN + 1];
	struct Task *next;
};

struct __attribute__((packed)) TaskContext {
	uint64_t x[31];
	uint64_t elr_el1;
	uint64_t spsr_el1;
};

static struct Task *m_currentTask, *m_lastTask, m_idleTask;


static uint32_t m_pid = 1;

static struct Task *
scheduleNext(void)
{
	struct Task *i, *next = NULL;
	int32_t priority = -1;

	if (m_currentTask->counter)
		m_currentTask->counter--;

	for (;;) {
		/* check urgent tasks */
		for (i = &m_idleTask; i != NULL; i = i->next) {
			if (i->state != TASK_STATE_RUNNING)
				continue;

			if (i->priority > priority && i->counter) {
				priority = i->priority;
				next = i;
			}
		}

		if (next) {
			break;
		}

		for (i = &m_idleTask; i != NULL; i = i->next) {
			i->counter = i->cycles;
		}
	}

	return next;
}

void
Task_initSheduler(void)
{
	struct Task *idleTask = &m_idleTask;

	m_pid = 1;
	m_idleTask.sp = NULL;
	m_idleTask.stackStart = NULL;
	m_idleTask.stackSize = CONFIG_IDLE_TASK_STACK_SIZE;
	m_idleTask.pid = 1;
	m_idleTask.lock = 1;
	m_idleTask.counter = 1;
	m_idleTask.cycles = 1;
	m_idleTask.priority = 0;
	m_idleTask.state = TASK_STATE_RUNNING;
	m_idleTask.name[0] = 'I';
	m_idleTask.name[1] = 'D';
	m_idleTask.name[2] = 'L';
	m_idleTask.name[3] = 'E';
	m_idleTask.name[4] = 0;
	m_idleTask.next = NULL;
	m_idleTask.options = 0;

	m_currentTask = idleTask;
	m_lastTask = idleTask;
	Task_unlockScheduler();
}

PID
Task_create(TaskCallback callback, void *arg, uint32_t options)
{
	struct TaskContext *ctx;
	struct Task *task = Memory_getPage();
	uint8_t el;

	if (!task)
		return -1;

	Log_putS("Task @0x");
	Log_putU((uint64_t) task, 16);
	Log_putS(" - ");
	Log_putU(((uint64_t) task) + MEMORY_PAGE_SIZE - 1, 16);
	Log_putS("\r\n");
	
	el = (options & TASK_OPT_USERSPACE) ? AARCH64_PSR_MODE_EL0t
		: AARCH64_PSR_MODE_EL1h;

	task->sp = (void *)task + MEMORY_PAGE_SIZE - 272;
	task->stackStart = task->sp;
	task->stackSize = MEMORY_PAGE_SIZE - sizeof(*task);
	task->lock = 1;
	task->counter = 1;
	task->cycles = 1;
	task->pid = ++m_pid;
	task->priority = 0;
	task->state = TASK_STATE_RUNNING;
	task->name[0] = 'N';
	task->name[1] = 'O';
	task->name[2] = 'N';
	task->name[3] = 'E';
	task->name[4] = 0;
	task->next = 0;
	task->options = options;
	
	ctx = (struct TaskContext *) task->sp;
	ctx->x[20] = (uint64_t) arg;
	ctx->x[21] = (uint64_t) callback;
	ctx->x[30] = (uint64_t) AArch64_startTask;
	ctx->elr_el1 = (uint64_t) AArch64_startTask;
	ctx->spsr_el1 = AArch64_getPSR(el);

	Log_putS("ELR_EL1=");
	Log_putU(ctx->elr_el1, 16);
	Log_putS("; SPSR_EL1=");
	Log_putU(ctx->spsr_el1, 16);
	Log_putS(";\r\n");

	Task_lockScheduler();
	m_lastTask->next = task;
	m_lastTask = task;
	Task_unlockScheduler();

	return task->pid;
}

void
Task_yield(void)
{
#if 1
	uint64_t ticks = Timer_getTicks();

	Task_lockScheduler();
	Log_putS("^");
	m_currentTask->counter = 0;
	Task_unlockScheduler();
	__asm__("WFE");

	while (ticks == Timer_getTicks());
#else
	/* Task yield should be solved differently */
	struct Task *next, *prev;

	Task_lockScheduler();
	Log_putS("^");
	prev = m_currentTask;
	prev->counter = 0;

	next = scheduleNext();

	if (next != prev) {
		next->state |= TASK_STATE_HALFCYCLE;
		m_currentTask = next;
		Task_unlockScheduler();
		AArch64_switchContext(prev, next);
		/* `next` tasks never exits here, but in AArch64_startTask,
		 * that is why there is an own Task_unlockScheduler() call
		 * */
	} else {
		// __asm__("WFE");
	}

	Task_unlockScheduler();
#endif
}

void
Task_lockScheduler(void)
{
	m_currentTask->lock++;
}

void
Task_unlockScheduler(void)
{
	if (m_currentTask->lock)
		m_currentTask->lock--;
}

void
Task_scheduleFromISR(void)
{
	if (!m_currentTask->lock) {
		struct Task *next;

		if (m_currentTask->state & TASK_STATE_HALFCYCLE) {
			m_currentTask->state &= ~TASK_STATE_HALFCYCLE;
			return;
		}

		Log_putS("!");

		Task_lockScheduler();


		next = scheduleNext();
		if (next != m_currentTask) {
			m_currentTask = next;
		}
		/* unlock call could be moved to aarch64.S interrupt handler in case of
		 * issue
		 * */
		Task_unlockScheduler();
	}
}

void *
Task_getStackPointer(void)
{
	/*
	Log_putS("gSP:");
	Log_putU((uint64_t)m_currentTask->sp, 16);
	Log_putS("\r\n");
	*/
	return m_currentTask->sp;
}

void
Task_setStackPointer(void *sp)
{
	/*
	Log_putS("sSP:");
	Log_putU((uint64_t)sp, 16);
	Log_putS("\r\n");
	*/
	m_currentTask->sp = sp;
}

int
Task_getEL(void)
{
	return (m_currentTask->options & TASK_OPT_USERSPACE) ? 0 : 1;
}

