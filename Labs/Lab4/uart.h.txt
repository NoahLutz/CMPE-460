/*
 * File:        uart.h
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */
#include <stdint.h>
#include "MK64F12.h"

void uart_put(UART_Type *uart, char *ptr_str);
void uart_init(UART_Type *uart);
uint8_t uart_getchar(UART_Type *uart);
void uart_putchar(UART_Type *uart, char ch);
