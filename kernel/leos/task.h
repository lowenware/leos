/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file task.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef TASK_H_AE13C166_79B5_4256_ABF3_74DF04E1CD18
#define TASK_H_AE13C166_79B5_4256_ABF3_74DF04E1CD18

#include <leos/types.h>

#ifndef CONFIG_TASK_MAX_NAME_LEN
#define CONFIG_TASK_MAX_NAME_LEN 16
#endif

typedef void (*TaskCallback)(void *p_ctx);

void
Task_initSheduler(void);

PID
Task_create(TaskCallback callback, void *arg);

void
Task_yield(void);

void
Task_lockScheduler(void);

void
Task_unlockScheduler(void);

void
Task_scheduleFromISR(void);

void *
Task_getStackPointer(void);

void
Task_setStackPointer(void *sp);

#endif /* !TASK_H */
