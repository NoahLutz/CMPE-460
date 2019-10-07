/*
 * isr.c
 */

#include "isr.h"
#include "MK64F12.h"
#include <stdio.h>
#include <stdbool.h>
#include "uart.h"
#include "main.h"

//variables global to the IRQ handlers which dictates if timer is enabled &  timer counter
uint32_t ftmCounter = 0;
bool counterActive = false;
char buf[80];

void PDB0_IRQHandler(void){ //For PDB timer
	// Clear the interrupt flag
	PDB0->SC &= ~PDB_SC_PDBIF_MASK;
	
	// Toggle the LED
	GPIOB_PTOR |= LED_RED_PIN; 
	

	return;
}
	
void FTM0_IRQHandler(void){ //For FTM timer
	FTM0->SC &= ~FTM_SC_TOF_MASK;
	
	if (counterActive == true) {
		ftmCounter++;
	}
	
	return;
}
	
void PORTA_IRQHandler(void){ //For switch 3
	PORTA_PCR4 |= PORT_PCR_ISF_MASK;
	
	if ((PDB0_SC & PDB_SC_PDBEN_MASK) == 0) {
		PDB0_SC |= PDB_SC_PDBEN_MASK;
	} else {
		PDB0_SC &= ~PDB_SC_PDBEN_MASK;
		GPIOB_PSOR |= LED_RED_PIN;
	}
	PDB0_SC |= PDB_SC_SWTRIG_MASK;
	
	return;
}

void PORTC_IRQHandler(void){ //For switch 2
	PORTC_PCR6 |= PORT_PCR_ISF_MASK;
	
	if ((GPIOC_PDIR & SW2_PIN) == 0) {
		ftmCounter = 0;
		counterActive = true;
		FTM0_CNT = 0;
		GPIOB_PCOR |= LED_BLUE_PIN;
	} else {
		GPIOB_PSOR |= LED_BLUE_PIN;
		counterActive = false;
		
		// Print to UART0
		sprintf(buf, "%u", ftmCounter);
		uart_put("SW 2 button held down for ");
		uart_put(buf);
		uart_put(" milliseconds!\r\n");
	}
	
	
	return;
}
