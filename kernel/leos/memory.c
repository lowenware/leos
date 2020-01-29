/******************************************************************************
 *
 *                Copyright (c) 2017-2020 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
			unsigned
 * @file memory.c
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#include <stdlib.h>
#include <aarch64/aarch64.h>
#include <drivers/soc/bcm2837/bcm2837.h>
#include "memory.h"
#include "log.h"

static unsigned long m_map[MEMORY_PAGE_COUNT / sizeof(unsigned long) / 8];
static int m_ix;

void
Memory_init(void)
{
	m_ix = 0;
	AArch64_memzero(m_map, sizeof(m_map));
}

void *
Memory_getPage(void)
{
	int i, j;
	unsigned long map;

	for (i = m_ix; i < sizeof(m_map) / sizeof(m_map[0]); i++) {
		map = m_map[i];
		for (j = 0; j < 8 * sizeof(map); j++) {
			if (!(map & (1 << j))) {
				m_map[i] |= (1 << j);
				return (void *) (MEMORY_LOW + (i * sizeof(map) * 8 + j) * MEMORY_PAGE_SIZE);
			}
		}
		m_ix = i;
	}

	Log_putS("ENOMEM\r\n");
	return NULL;
}

void
Memory_freePage(void *p_addr)
{
	int i, j, c;

	c = ((unsigned long) p_addr) / MEMORY_PAGE_SIZE;
	i = c / sizeof(m_map[0]);
	j = c % sizeof(m_map[0]);
	m_map[i] &= ~(1 << j);
}
