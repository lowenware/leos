/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file print.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef LOG_H_AE38CD54_2822_47A5_AFB1_E785739FA01D
#define LOG_H_AE38CD54_2822_47A5_AFB1_E785739FA01D

#include <leos/types.h>

void
Log_init(void);

int
Log_putS(const char *string);

int
Log_putI(int64_t value, uint8_t base);

int
Log_putU(uint64_t value, uint8_t base);

#endif /* !LOG_H */
