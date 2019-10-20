/*
 * Main Method for testing the PWM Code for the K64F
 * PWM signal can be connected to output pins are PC3 and PC4
 * 
 * Author:  
 * Created:  
 * Modified:  
 */

#include "MK64F12.h"
#include "uart.h"
#include "stepper.h"

#define DELAY 50000

void initialize(void);

int main(void) {
	uint8_t phase = 4;
	initialize();
	
	//GPIOD_PSOR |= 1<<0;
	
	for(;;) {
		GPIOD_PCOR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
		phase--;
		GPIOD_PSOR |= (1 << phase);
		
		
		
		if (phase == 0) {
			phase = 4;
		}
		
		for(int i = 0; i<DELAY; i++);
		
		
		/*GPIOD_PCOR |= (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3);
		GPIOD_PSOR |= 1;
		for(int i = 0; i<DELAY; i++);
		GPIOD_PCOR |= 1;
		GPIOD_PSOR |= 1 << 1;
		for(int i = 0; i<DELAY; i++);
		GPIOD_PCOR |= 1 << 1;
		GPIOD_PSOR |= 1 << 2;
		for(int i = 0; i<DELAY; i++);
		GPIOD_PCOR |= 1 << 2;
		GPIOD_PSOR |= 1 << 3;
		for(int i = 0; i<DELAY; i++);
		*/
	}
	
	return 0;
}


void initialize(void) {
	init_stepper();
}
