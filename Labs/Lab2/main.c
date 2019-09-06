/*
** Title:	main.c
** Description:
** Authors: Noah Lutz
** Date: 9/6/19
**
** Some of the contents are obtained by the courtesy of the material provided by Freescale Semiconductor, Inc.
** Copyright (c) 2014, Freescale Semiconductor, Inc.
** All rights reserved.
*/

#include<stdio.h>
#include<string.h>
#include "MK64F12.h"
#include "uart.h"

#define BAUD_RATE 9600      //default baud rate 
#define SYS_CLOCK 20485760 //default system clock (see DEFAULT_SYSTEM_CLOCK  in system_MK64F12.c)
#define CHAR_COUNT 10      //change this to modify the max. permissible length of a sentence

#define CR     0x0D
#define LF     0x0A

void put(char *ptr_str);
void part1(void);
void part2(void);

int main()
{
	
	uart_init();
	
	//part1();
   part2();
}

/**************************************************
* 
* part1()
*
* Description: 	Runs Part 1 of Lab 2
*
* Parameters:		None
*
* Returns: 			None
*
***************************************************/
void part1(void) {
   put("\r\nIDE Lab2 Demonstration by Noah Lutz");
}

/**************************************************
* 
* part2()
*
* Description: 	Runs Part 2 of Lab 2
*
* Parameters:		None
*
* Returns: 			None
*
***************************************************/
void part2(void) {
   uint8_t buffer;
   uint8_t index;
   
   for(;;) {
      if (index == 0) {
         put("> ");
      }
      buffer = uart_getchar();
      if (buffer != CR) {
         uart_putchar(buffer);
         index++;
      }
      else {
         uart_putchar(LF);
         uart_putchar(CR);
         if (index > CHAR_COUNT) {
            break;
         }
         else {
            index = 0;
         }
      }
   }
}

/**************************************************
* 
* put()
*
* Description: 	Prints a string via UART
*
* Parameters:		*ptr_str - char pointer
*
* Returns: 			None
*
***************************************************/
void put(char *ptr_str)
{
	while(*ptr_str) {
		uart_putchar(*ptr_str++);
   }
}
