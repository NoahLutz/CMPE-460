/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* Spring 2016
*
* Filename: main_timer_template.c
*/

#include "MK64F12.h"
#include "main.h"
#include "uart.h"
#include "isr.h"
#include <stdio.h>

/*From clock setup 0 in system_MK64f12.c*/
#define DEFAULT_SYSTEM_CLOCK 20485760u /* Default System clock value */

void initPDB(void);
void initGPIO(void);
void initFTM(void);
void initInterrupts(void);

int main(void){
	//initializations
	initPDB();
	initGPIO();
	initFTM();
	uart_init();
	initInterrupts();

	for(;;){
		//To infinity and beyond
	}
}


void initPDB(void){
	//Enable clock for PDB module
	SIM_SCGC6 |= SIM_SCGC6_PDB_MASK;

	// Set continuous mode, prescaler of 128, multiplication factor of 20,
	// software triggering, and PDB enabled
	PDB0->SC |= (PDB_SC_PRESCALER_MASK | PDB_SC_TRGSEL_MASK | PDB_SC_CONT_MASK);
	PDB0->SC |= 2U << PDB_SC_MULT_SHIFT;
	PDB0->SC |= PDB_SC_PDBEN_MASK;
	

	//Set the mod field to get a 1 second period.
	//There is a division by 2 to make the LED blinking period 1 second.
	//This translates to two mod counts in one second (one for on, one for off)
	PDB0->MOD = (DEFAULT_SYSTEM_CLOCK/(128 * 20))/2;

	//Configure the Interrupt Delay register.
	PDB0_IDLY = 10;

	//Enable the interrupt mask.
	PDB0->SC |= PDB_SC_PDBIE_MASK;
	

	//Enable LDOK to have PDB0_SC register changes loaded.
	PDB0->SC |= PDB_SC_LDOK_MASK;

	PDB0->SC &= ~PDB_SC_PDBEN_MASK;

	return;
}

void initFTM(void){
	//Enable clock for FTM module (use FTM0)
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;

	//turn off FTM Mode to  write protection;
	FTM0->MODE |= FTM_MODE_WPDIS_MASK;

	//divide the input clock down by 128,
	FTM0->SC |= FTM_SC_PS_MASK;

	//reset the counter to zero
	FTM0->CNTIN = 0;
	FTM0->CNT = 0;

	//Set the overflow rate
	//(Sysclock/128)- clock after prescaler
	//(Sysclock/128)/1000- slow down by a factor of 1000 to go from
	//Mhz to Khz, then 1/KHz = msec
	//Every 1msec, the FTM counter will set the overflow flag (TOF) and
	FTM0->MOD = (DEFAULT_SYSTEM_CLOCK/(1<<7))/1000;

	//Select the System Clock
	FTM0->SC |= (1 << FTM_SC_CLKS_SHIFT);

	//Enable the interrupt mask. Timer overflow Interrupt enable
	FTM0->SC |= FTM_SC_TOIE_MASK;

	return;
}

void initGPIO(void){
	//initialize push buttons and LEDs
	
	//initialize clocks for each different port used.
	SIM_SCGC5 |= (SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTE_MASK | SIM_SCGC5_PORTC_MASK);

	//Configure Port Control Register for Inputs with pull enable and pull up resistor
	PORTC_PCR6 = PORT_PCR_MUX(1);
	PORTA_PCR4 = PORT_PCR_MUX(1);
	
	PORTC_PCR6 |= (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
	PORTA_PCR4 |= (PORT_PCR_PE_MASK | PORT_PCR_PS_MASK);
	
	// Configure mux for Outputs
	PORTB_PCR22 = PORT_PCR_MUX(1);
	PORTB_PCR21 = PORT_PCR_MUX(1);
	PORTE_PCR26 = PORT_PCR_MUX(1);

	// Switch the GPIO pins to output mode (Red and Blue LEDs)
	GPIOB_PDDR = LED_RED_PIN | LED_BLUE_PIN;
	GPIOE_PDDR = LED_GREEN_PIN;

	// Turn off the LEDs
	GPIOB_PSOR = LED_RED_PIN | LED_BLUE_PIN;
	GPIOE_PSOR = LED_GREEN_PIN;
	
	// Set the push buttons as an input
	GPIOC_PDDR &= ~(SW2_PIN);
	GPIOA_PDDR &= ~(SW3_PIN);

	// interrupt configuration for SW3(Rising Edge) and SW2 (Either)
	PORTA_PCR4 |= PORT_PCR_IRQC(9);
	PORTC_PCR6 |= PORT_PCR_IRQC(11);

	return;
}


void initInterrupts(void){
	/*Can find these in MK64F12.h*/
	// Enable NVIC for portA,portC, PDB0,FTM0
	NVIC_EnableIRQ(PORTA_IRQn);
	NVIC_EnableIRQ(PORTC_IRQn);
	NVIC_EnableIRQ(PDB0_IRQn);
	NVIC_EnableIRQ(FTM0_IRQn);

	return;
}
