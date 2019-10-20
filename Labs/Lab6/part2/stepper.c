/*
 * stepper.c
 * 
 * Author:  
 * Created:  
 * Modified:  
 */

#include "MK64F12.h"
#include "stepper.h"

void init_stepper(void) {
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;
	
	// Set PTD0-3 to GPIO
	PORTD_PCR0 |= PORT_PCR_MUX(1);
	PORTD_PCR1 |= PORT_PCR_MUX(1);
	PORTD_PCR2 |= PORT_PCR_MUX(1);
	PORTD_PCR3 |= PORT_PCR_MUX(1);
	
	GPIOD_PDDR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
	
	GPIOD_PCOR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
}

