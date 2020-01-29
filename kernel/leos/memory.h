/******************************************************************************
 *
 *                Copyright (c) 2017-2020 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file memory.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef MEMORY_H_C583E24E_55B0_49EF_99C9_5A36B04468AC
#define MEMORY_H_C583E24E_55B0_49EF_99C9_5A36B04468AC


void
Memory_init(void);

void *
Memory_getPage(void);

void
Memory_freePage(void *p_addr);


#endif /* !MEMORY_H */
