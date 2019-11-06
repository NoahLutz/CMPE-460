/*
 * File:        gpio.c
 * Purpose:     Provide GPIO routines
 *
 * Notes:		
 *
 */

#include <stdlib.h>
#include "gpio.h"
#include "MK64F12.h"
 
/**********************************************************
* 					Private Function Declarations
**********************************************************/

 
/**********************************************************
*						Private Variable Declarations
**********************************************************/
GPIOPin_t clk = {PTB, 9};
GPIOPin_t si = {PTB, 23};
GPIOPin_t redLed = {PTB, 22};
GPIOPin_t motor1Enable = {PTB, 2};
GPIOPin_t motor2Enable = {PTB, 3};
 
/* Set up pins for GPIO
*     PTB9 		- camera clk
*		PTB23		- camera SI
*		PTB22		- red LED
*/
void init_GPIO(void){
	// Enable LED and GPIO so we can see results
	
	// Turn on PORTB clock
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	
	// set ptb9,22,23 as GPIO
	PORTB_PCR9 |= PORT_PCR_MUX(1);
	PORTB_PCR22 |= PORT_PCR_MUX(1);
	PORTB_PCR23 |= PORT_PCR_MUX(1);

	PORTB_PCR2 |= PORT_PCR_MUX(1);
	PORTB_PCR3 |= PORT_PCR_MUX(1);
	
	// set data direction for GPIO pins
	clk.port->PDDR |= (1U << clk.pin);
	si.port->PDDR |= (1U << si.pin);
	redLed.port->PDDR |= (1U << redLed.pin);
	motor1Enable.port->PDDR |= (1 << motor1Enable.pin);
	motor2Enable.port->PDDR |= (1 << motor2Enable.pin);

   gpio_high(&redLed);
	
	return;
}

void gpio_toggle(GPIOPin_t *ptr) {
   if (ptr != NULL) {
      ptr->port->PTOR |= (1U << ptr->pin);
   }
}

void gpio_high(GPIOPin_t *ptr) {
   if (ptr != NULL) {
      ptr->port->PSOR |= (1U << ptr->pin);
   }
}

void gpio_low(GPIOPin_t *ptr) {
   if (ptr != NULL) {
      ptr->port->PCOR |= (1U << ptr->pin);
   }
}




