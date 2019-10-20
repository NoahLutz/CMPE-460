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
#define BS		 0x08

#define LED_RED_PIN			22U
#define LED_GREEN_PIN		26U
#define LED_BLUE_PIN		21U

void part1(void);
void part2(void);
void LED_Init(void);
void led_cycle(uint8_t index);

int main()
{
	LED_Init();
	uart_init(UART0);
	uart_init(UART3);
	uart_put(UART0, "start\r\n");
	uart_put(UART3, "AT+IBE0?");
	
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_put(UART0, "\r\n");
	
	uart_put(UART3, "AT+IBE1?");
	
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_put(UART0, "\r\n");

	uart_put(UART3, "AT+IBE2?");
	
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_put(UART0, "\r\n");
	
	uart_put(UART3, "AT+IBE3?");
	
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_putchar(UART0, uart_getchar(UART3));
	uart_put(UART0, "\r\n");
  
	uart_put(UART0, "\r\ndone\r\n");
	//part1();
	//part2();
}



/**************************************************
* 
* part1()
*
* Description: 	Runs Part 1 of Lab 4
*
* Parameters:		None
*
* Returns: 			None
*
***************************************************/
void part1(void) {
   uint8_t buffer[10];
   uint8_t index;
   
   for(;;) {
      if (index == 0) {
         uart_put(UART3, "\r\n> ");
      }
      buffer[index] = uart_getchar(UART3);
			uart_putchar(UART3, buffer[index]);
			index++;
			if (buffer[index-1] == CR) {
				index = 0;
				if (buffer[0] == '0') {
					led_cycle(0);
				} else if (buffer[0] == '1') {
					led_cycle(1);
				} else if (buffer[0] == '2') {
					led_cycle(2);
				} else if (buffer[0] == '3') {
					led_cycle(3);
				}
			}
			
   }
}

/**************************************************
* 
* part2()
*
* Description: 	Runs Part 1 of Lab 4
*
* Parameters:		None
*
* Returns: 			None
*
***************************************************/
void part2(void) {
	uint8_t buffer[20];
	uint8_t index = 0;
	memset(buffer, 0, 20);
	for(;;) {
		uart_put(UART3, "\r\n>");
		while(index < 20) {
			buffer[index] = uart_getchar(UART3);
			uart_putchar(UART3, buffer[index]);
			index++;
			
			if(buffer[index-1] == CR){
				break;
			}
		}
		//uart_put(UART3, (char*)buffer);
		buffer[index] = 0;
		uart_put(UART0, (char*)buffer);
		index = 0;
		memset(buffer, 0, 20);
		
		uart_put(UART0, "\r\n>");
		while(index < 20) {
			buffer[index] = uart_getchar(UART0);
			uart_putchar(UART0, buffer[index]);
			index++;
			
			if (buffer[index-1] == CR) {
				uart_putchar(UART0, '\n');
				break;
			}
		}
		buffer[index] = 0;
		uart_put(UART3, (char*)buffer);
		index = 0;
		
	}
}


void delay (uint32_t delay) {
	int i;
	for(i = 0; i < delay; i++);
}

void LED_Init(void){
	// Enable clocks on Ports B and E for LED timing
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	SIM_SCGC5 |= SIM_SCGC5_PORTE_MASK;
	
	// Configure the Signal Multiplexer for GPIO
  PORTB_PCR22 = PORT_PCR_MUX(1);
	PORTB_PCR21 = PORT_PCR_MUX(1);
	PORTE_PCR26 = PORT_PCR_MUX(1);
	
	// Switch the GPIO pins to output mode
	GPIOB_PDDR = (1UL << LED_RED_PIN) | (1UL << LED_BLUE_PIN);
	GPIOE_PDDR = (1UL << LED_GREEN_PIN);

	// Turn off the LEDs
  GPIOB_PSOR = (1UL << LED_RED_PIN) | (1UL << LED_BLUE_PIN);
	GPIOE_PSOR = (1UL << LED_GREEN_PIN);
}

void led_cycle(uint8_t index) {
	switch (index) {
		case 0:
			GPIOB_PSOR = (1 << LED_BLUE_PIN);
			GPIOB_PSOR = (1 << LED_RED_PIN);
			GPIOE_PSOR = (1 << LED_GREEN_PIN);
			break;
		case 1:
			GPIOB_PCOR = (1 << LED_RED_PIN);
			break;
		case 2:
			GPIOB_PCOR = (1 << LED_BLUE_PIN);
			break;
		case 3:
			GPIOE_PCOR = (1 << LED_GREEN_PIN);
			break;
	}
}
