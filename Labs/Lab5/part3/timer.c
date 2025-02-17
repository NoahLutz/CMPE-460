/*
 * File:        timer.c
 * Purpose:     Provide timer routines
 *
 * Notes:		
 *
 */

#include "timer.h"
#include "gpio.h"
#include "main.h"

// Default System clock value
// period = 1/20485760  = 4.8814395e-8
#define DEFAULT_SYSTEM_CLOCK 20485760u

// Integration time (seconds)
// Determines how high the camera values are
// Don't exceed 100ms or the caps will saturate
// Must be above 1.25 ms based on camera clk 
//	(camera clk is the mod value set in FTM2)
#define INTEGRATION_TIME .0075f

#define FTM2_MOD_10US     2 * 205U   // 205 = 10[us] / (1 / 20[MHz])

#define PIT_LDVAL_1290US	69500U * 4	// 64500 = 1.29[ms] / (1 / 50[MHz]) 



/* Initialization of FTM2 for camera */
void init_FTM2() {
	// Enable clock
	SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;

	// Disable Write Protection
	FTM2_MODE |= FTM_MODE_WPDIS_MASK;

	// Set output to '1' on init
	gpio_high(&clk);
	
	// Initialize the CNT to 0 before writing to MOD
	FTM2_CNT = 0;
	
	// Set the Counter Initial Value to 0
	FTM2_CNTIN = 0;

	// Set the period (~10us)
	FTM2_MOD = FTM2_MOD_10US;
	
	// 50% duty
	//FTM2_C0SC |= 
	
	// Set edge-aligned mode
	FTM2_C0SC |= FTM_CnSC_MSB_MASK;
	
	// Enable High-true pulses
	// ELSB = 1, ELSA = 0
	FTM2_C0SC |= FTM_CnSC_ELSA_MASK;
	FTM2_C0SC &= ~FTM_CnSC_ELSB_MASK;
	
	// Enable hardware trigger from FTM2
	FTM2_EXTTRIG |= FTM_EXTTRIG_CH0TRIG_MASK;
	
	// Don't enable interrupts yet (disable)
	FTM2_SC &= ~FTM_SC_TOIE_MASK;
	
	// No prescalar, system clock
	FTM2_SC &= ~FTM_SC_PS_MASK;
	
	// Set up interrupt
	NVIC_EnableIRQ(FTM2_IRQn);
	
	FTM2_SC |= 1U << FTM_SC_CLKS_SHIFT;
	
	return;
}

/* Initialization of PIT timer to control 
* 		integration period
*/
void init_PIT(void){
	// Setup periodic interrupt timer (PIT)
	
	// Enable clock for timers
	SIM_SCGC6 |= SIM_SCGC6_PIT_MASK;
	PIT_MCR &= ~PIT_MCR_MDIS_MASK;
	
	// Enable timers to continue in debug mode
	PIT_MCR |= PIT_MCR_FRZ_MASK; // In case you need to debug
	
	// PIT clock frequency is the system clock
	// Load the value that the timer will count down from
	PIT_LDVAL0 = PIT_LDVAL_1290US;
	
	// Enable timer interrupts
	PIT_TCTRL0 |= PIT_TCTRL_TIE_MASK;
	
	// Enable the timer
	PIT_TCTRL0 |= PIT_TCTRL_TEN_MASK;

	// Clear interrupt flag
	PIT_TFLG0 &= ~PIT_TFLG_TIF_MASK;

	// Enable PIT interrupt in the interrupt controller
	NVIC_EnableIRQ(PIT0_IRQn);
	return;
}



/* 
* FTM2 handles the camera driving logic
*	This ISR gets called once every integration period
*		by the periodic interrupt timer 0 (PIT0)
*	When it is triggered it gives the SI pulse,
*		toggles clk for 128 cycles, and stores the line
*		data from the ADC into the line variable
*/
void FTM2_IRQHandler(void){ //For FTM timer
	// Clear interrupt
  FTM2_SC &= ~FTM_SC_TOF_MASK;
	
	// Toggle clk
	//gpio_toggle(&clk);
	if (clkval == 1) {
		gpio_low(&clk);
		clkval = 0;
	} else {
		gpio_high(&clk);
		clkval = 1;
	}
	
	// Line capture logic
	if ((pixcnt >= 2) && (pixcnt < 256)) {
		if (!clkval) {	// check for falling edge
			// ADC read (note that integer division is 
			//  occurring here for indexing the array)
			line[pixcnt/2] = ADC0VAL;
		}
		pixcnt += 1;
	} else if (pixcnt < 2) {
		if (pixcnt == -1) {
			gpio_high(&si); // SI = 1
		} else if (pixcnt == 0) {
			//for(int i = 0; i<10; i++);
			gpio_low(&si); // SI = 0
			// ADC read
			line[0] = ADC0VAL;
		} 
		pixcnt += 1;
	} else {
		GPIOB_PCOR |= (1 << 9); // CLK = 0
		clkval = 0; // make sure clock variable = 0
		pixcnt = -2; // reset counter
		// Disable FTM2 interrupts (until PIT0 overflows
		//   again and triggers another line capture)
		FTM2_SC &= ~FTM_SC_TOIE_MASK;
	
	}
	return;
}

/* PIT0 determines the integration period
*		When it overflows, it triggers the clock logic from
*		FTM2. Note the requirement to set the MOD register
* 	to reset the FTM counter because the FTM counter is 
*		always counting, I am just enabling/disabling FTM2 
*		interrupts to control when the line capture occurs
*/
void PIT0_IRQHandler(void){
	if (debugcamdata) {
		// Increment capture counter so that we can only 
		//	send line data once every ~2 seconds
		capcnt += 1;
	}
	// Clear interrupt
	PIT_TFLG0 |= PIT_TFLG_TIF_MASK;
	
	// Setting mod resets the FTM counter
	FTM2_MOD = FTM2_MOD_10US;
	
	// Enable FTM2 interrupts (camera)
	//FTM2_SC |= 1U << FTM_SC_CLKS_SHIFT;
	FTM2_SC |= FTM_SC_TOIE_MASK;
	//gpio_toggle(&si);
	
	return;
}


