/*
 * File:        gpio.c
 * Purpose:     Provide GPIO routines
 *
 * Notes:		
 *
 */
 
 #include "gpio.h"
 #include "MK64F12.h"
 
 /**********************************************************
 * 									Private Function Declarations
 **********************************************************/

 
  /**********************************************************
 * 									Private Variable Declarations
 **********************************************************/
 const GPIOPin_t clk = {PTB, 9};
 const GPIOPin_t si = {PTB, 23};
 const GPIOPin_t redLed = {PTB, 22};
 
 /* Set up pins for GPIO
* 	PTB9 		- camera clk
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
	
	// set data direction for GPIO pins
	clk.port->PDDR |= (1U << clk.pin);
	si.port->PDDR |= (1U << si.pin);
	redLed.port->PDDR |= (1U << redLed.pin);
	
	return;
}




