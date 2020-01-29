/******************************************************************************
 *
 *                Copyright (c) 2017-2019 by Löwenware Ltd
 *             Please, refer LICENSE file for legal information
 *
 ******************************************************************************/

/**
 * @file UARTMini.h
 * @author Ilja Kartašov <ik@lowenware.com>
 * @brief 
 *
 * @see https://lowenware.com/
 */

#ifndef UART_MINI_H_B0DFA3CF_5B4F_4EB0_B393_391C0069A04F
#define UART_MINI_H_B0DFA3CF_5B4F_4EB0_B393_391C0069A04F

int
UARTMini_init(void);

int
UARTMini_put(char c);

int
UARTMini_get(char *pc);

#endif /* !UART_MINI_H */
