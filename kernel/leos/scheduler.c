/******************************************************************************
 *
 *                Copyright (c) 2017-2020 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file scheduler.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include "scheduler.h"


static struct KTask *m_first = NULL, *m_last, *m_current = NULL;
static KPid m_pid = 0;

static void
_disable_preempt(void)
{
	m_current->preempt++;
}

static void
_enable_preempt(void)
{
	m_current->preempt--;
}

static void
_switch(void)
{
	struct KTask *i, *next;
	long p = 0;

	_disable_preempt();

	for (;;) {
		/* check urgent tasks */
		for (i = m_first; i != NULL; i = i->next) {
			if (!i->state && i->counter > p) {
				p = i->counter;
				next = i;
			}
			i = i->next;
		}

		if (p) {
			break;
		}

		i = m_first;
		for (i = m_first; i != NULL; i = i->next) {
			i->counter = i->priority;
		}
	}

	aarch64_switch(m_current, next);
	_enable_preempt();
}

void
scheduler_init(void)
{

}

KPid
scheduler_add(struct KTask *task)
{
	KPid result = ++m_pid;
	task->pid = result;
	task->prev = m_last;
	m_last->next = task;
	return result;
}

void
scheduler_switch(void)
{

}

void
scheduler_switch_from_isr(void)
{

}
