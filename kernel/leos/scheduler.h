/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file scheduler.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef SCHEDULER_H_AE39DBC8_E643_4857_B319_9732123728A4
#define SCHEDULER_H_AE39DBC8_E643_4857_B319_9732123728A4

void
scheduler_init(void);

void
scheduler_run(void);

void
scheduler_switch(void);

KPid
scheduler_add(struct KTask *task);

KRetCode
scheduler_remove(struct KTask *task);

KRetCode
scheduler_remove_pid(KPid pid);


#endif /* !SCHEDULER_H */
