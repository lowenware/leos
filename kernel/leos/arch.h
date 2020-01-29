/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file arch.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef ARCH_H_F63C116D_51C9_4E25_9B1F_126833937268
#define ARCH_H_F63C116D_51C9_4E25_9B1F_126833937268

#include <aarch64/aarch64.h>

#define Arch_init(...) AArch64_init(__VA_ARGS__)

#endif /* !ARCH_H */
