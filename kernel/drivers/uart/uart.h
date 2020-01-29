/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file uart.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef UART_H_8AFC47F9_2953_42C1_A5C1_1AE5A1F52CD0
#define UART_H_8AFC47F9_2953_42C1_A5C1_1AE5A1F52CD0

#include "uart_mini.h"
#include "uart_qemu.h"

#define UART_MINI 0
#define UART_QEMU 1

#ifndef UART_DEFAULT
#define UART_DEFAULT UART_MINI
#endif

#if UART_DEFAULT == UART_MINI

#define UART_init(...) UARTMini_init(__VA_ARGS__)
#define UART_get(...) UARTMini_get(__VA_ARGS__)
#define UART_put(...) UARTMini_put(__VA_ARGS__)

#elif UART_DEFAULT == UART_QEMU

#define UART_init(...)
#define UART_get(...)
#define UART_put(...) UARTQEMU_put(__VA_ARGS__)

#else

#warning "Unsupported UART"

#endif

#endif /* !UART_H */
