/* 
Title: main.c
Purpose: Lab 1
Name: Noah Lutz
Date: 8/30/19
*/
#include "MK64F12.h"                    // Device header
#include <stdint.h>

#define LED_RED_PIN			22U
#define LED_GREEN_PIN		26U
#define LED_BLUE_PIN		21U
#define SW2_PIN					6U

uint8_t index;

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

void Button_Init(void){
	// Enable clock for Port C PTC6 button
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	// Configure the Mux for the button
	PORTC_PCR6 = PORT_PCR_MUX(1);
	 
	// Set the push button as an input
	GPIOC_PDDR = ~(1 << SW2_PIN);
}

void delay (uint32_t delay) {
	int i;
	for(i = 0; i < delay; i++);
}

void yellow_loop(void) {
	for(;;){
		//Turn on an LED configuration when button is held
		if((GPIOC_PDIR & (1 << SW2_PIN)) == 0){
			GPIOB_PCOR = (1 << LED_RED_PIN);
			GPIOE_PCOR = (1 << LED_GREEN_PIN);
			delay (2000000);
		}
		// Turn off LEDs on release of button
		else{
			GPIOB_PSOR = (1UL << 21) | (1UL << 22);
			GPIOE_PSOR = 1UL << 26;
		}
	}
}

void led_cycle(void) {
	if ((GPIOC_PDIR & (1 << SW2_PIN)) == 0){
		index++;
	}
	
	switch (index) {
		case 1:
			GPIOB_PCOR = (1 << LED_RED_PIN);
			delay (2000000);
			GPIOB_PSOR = (1 << LED_RED_PIN);
			GPIOE_PCOR = (1 << LED_GREEN_PIN);
			delay (2000000);
			index = 0;
			break;
	}
}

int main(void){
	index = 0;
	
	// Initialize buttons and LEDs
	LED_Init();
	Button_Init();

	//yellow_loop();
	
	led_cycle();
	
}
