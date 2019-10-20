/*
 * File:        uart.h
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */
#include <stdint.h>

#ifndef UART_H
#define UART_H

void uart_put(char *ptr_str);
void uart_init(void);
uint8_t uart_getchar(void);
void uart_putchar(char ch);

#endif
