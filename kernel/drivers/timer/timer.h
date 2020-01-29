/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file timer.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef TIMER_H_8D327261_47D6_4832_8DC5_31BF1614A21F
#define TIMER_H_8D327261_47D6_4832_8DC5_31BF1614A21F

#include <leos/types.h>

void
Timer_init(void);

void
Timer_incFromISR(void);

uint32_t
Timer_getTicks(void);

#endif /* !TIMER_H */
