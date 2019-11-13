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

//#define FTM2_MOD_10US     410U   // 410 = 10[us] / (1 / 20[MHz])
#define FTM2_MOD_33MS		2*42679U

//#define PIT_LDVAL_1290US	69500U * 4	// 64500 = 1.29[ms] / (1 / 50[MHz]) 



/* Initialization of FTM2 for camera */
void init_FTM2() {
	// Enable clock
	SIM_SCGC6 |= SIM_SCGC6_FTM2_MASK;

	// Disable Write Protection
	FTM2_MODE |= FTM_MODE_WPDIS_MASK;
	
	// Initialize the CNT to 0 before writing to MOD
	FTM2_CNT = 0;
	
	// Set the Counter Initial Value to 0
	FTM2_CNTIN = 0;

	// Set the period (~10us)
	FTM2_MOD = FTM2_MOD_33MS;
	
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
	
	// 16x prescaler, system clock
	FTM2_SC |= 7U << FTM_SC_PS_SHIFT;
	FTM2_SC |= 1U << FTM_SC_CLKS_SHIFT;
	
	// Don't enable interrupts yet (disable)
	FTM2_SC |= FTM_SC_TOIE_MASK;
	NVIC_EnableIRQ(FTM2_IRQn);
}


/* 
* FTM2 handles the camera driving logic
*	This ISR gets called once every integration period
*		by the periodic interrupt timer 0 (PIT0)
*	When it is triggered it gives the SI pulse,
*		toggles clk for 128 cycles, and stores the line
*		data from the ADC into the line variable
*/
void FTM2_IRQHandler(void)
{
	//For FTM timer
	gpio_toggle(&clk);
	return;
}



