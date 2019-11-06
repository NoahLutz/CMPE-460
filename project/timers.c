/*
 * File:        timers.c
 * Purpose:     timer intitalizations and register access
 *
 * Notes:		
 *
 */


#include "MK64F12.h"
#include "timers.h"
#include "gpio.h"
#include "adc.h"
#include "main.h"

/*From clock setup 0 in system_MK64f12.c*/
// Integration time (seconds)
// Determines how high the camera values are
// Don't exceed 100ms or the caps will saturate
// Must be above 1.25 ms based on camera clk 
//	(camera clk is the mod value set in FTM2)
#define INTEGRATION_TIME .0075f

#define FTM2_MOD_10US     2 * 205U   // 205 = 10[us] / (1 / 20[MHz])

#define PIT_LDVAL_1290US	69500U * 4	// 64500 = 1.29[ms] / (1 / 50[MHz]) 

#define PWM_FREQUENCY			10000
#define SERVO_FREQUENCY			50
#define FTM0_MOD_VALUE			(CLOCK/PWM_FREQUENCY)
#define FTM3_MOD_VALUE			(CLOCK/16/SERVO_FREQUENCY)


int clkval = 1;
int pixcnt = -2;


/*
 * Initialize FTM0
 * Used for the two DC motors
 */
void InitFTM0(void)
{
	// 12.2.13 Enable the Clock to the FTM0 Module
	SIM_SCGC6 |= SIM_SCGC6_FTM0_MASK;
	
	// Enable clock on PORT A so it can output
	SIM_SCGC5 |= SIM_SCGC5_PORTA_MASK | SIM_SCGC5_PORTB_MASK | SIM_SCGC5_PORTC_MASK;
	
	// 11.4.1 Route the output of FTM channel 0 to the pins
	// Use drive strength enable flag to high drive strength
	//These port/pins may need to be updated for the K64 <Yes, they do. Here are two that work.>
	
   PORTC_PCR1  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK; //Ch0
   PORTC_PCR2  = PORT_PCR_MUX(4)  | PORT_PCR_DSE_MASK;//Ch1
	PORTC_PCR3 = PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK; // ch2
	PORTC_PCR4 = PORT_PCR_MUX(4) | PORT_PCR_DSE_MASK; // ch3
	
	// 39.3.10 Disable Write Protection
	FTM0_MODE |= FTM_MODE_WPDIS_MASK;
	
	// 39.3.4 FTM Counter Value
	// Initialize the CNT to 0 before writing to MOD
	FTM0_CNT = 0;
	
	// 39.3.8 Set the Counter Initial Value to 0
	FTM0_CNTIN = 0;
	
	// 39.3.5 Set the Modulo resister
	FTM0_MOD = FTM0_MOD_VALUE;
	//FTM0->MOD = (DEFAULT_SYSTEM_CLOCK/(1<<7))/1000;

	// 39.3.6 Set the Status and Control of both channels
	// Used to configure mode, edge and level selection
	// See Table 39-67,  Edge-aligned PWM, High-true pulses (clear out on match)
	FTM0_C0SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C0SC &= ~FTM_CnSC_ELSA_MASK;
	
	// See Table 39-67,  Edge-aligned PWM, Low-true pulses (clear out on match)
	FTM0_C1SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C1SC &= ~FTM_CnSC_ELSA_MASK;
	
	// See Table 39-67,  Edge-aligned PWM, Low-true pulses (clear out on match)
	FTM0_C2SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C2SC &= ~FTM_CnSC_ELSA_MASK;
	
	// See Table 39-67,  Edge-aligned PWM, Low-true pulses (clear out on match)
	FTM0_C3SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM0_C3SC &= ~FTM_CnSC_ELSA_MASK;
	
	// 39.3.3 FTM Setup
	// Set prescale value to 1 
	// Chose system clock source
	// Timer Overflow Interrupt Enable
	FTM0_SC = FTM_SC_PS(0) | FTM_SC_CLKS(1); 
	//| FTM_SC_TOIE_MASK;

}


/*
 * Initialize FTM3
 * Used for servo control
 */
void InitFTM3(void)
{
	// 12.2.13 Enable the Clock to the FTM0 Module
	SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;
	
	// Enable clock on PORT A so it can output
	SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK;
	
	// 11.4.1 Route the output of FTM channel 0 to the pins
	// Use drive strength enable flag to high drive strength
	//These port/pins may need to be updated for the K64 <Yes, they do. Here are two that work.>
	
    PORTC_PCR8  = PORT_PCR_MUX(3)  | PORT_PCR_DSE_MASK; //Ch4
    
	
	// 39.3.10 Disable Write Protection
	FTM3_MODE |= FTM_MODE_WPDIS_MASK;
	
	// 39.3.4 FTM Counter Value
	// Initialize the CNT to 0 before writing to MOD
	FTM3_CNT = 0;
	
	// 39.3.8 Set the Counter Initial Value to 0
	FTM3_CNTIN = 0;
	
	// 39.3.5 Set the Modulo resister
	FTM3_MOD = FTM3_MOD_VALUE;
	//FTM0->MOD = (DEFAULT_SYSTEM_CLOCK/(1<<7))/1000;

	// 39.3.6 Set the Status and Control of both channels
	// Used to configure mode, edge and level selection
	// See Table 39-67,  Edge-aligned PWM, High-true pulses (clear out on match)
	FTM3_C4SC |= FTM_CnSC_MSB_MASK | FTM_CnSC_ELSB_MASK;
	FTM3_C4SC &= ~FTM_CnSC_ELSA_MASK;
	
	// 39.3.3 FTM Setup
	// Set prescale value to 1 
	// Chose system clock source
	// Timer Overflow Interrupt Enable
	FTM3_SC = FTM_SC_PS(4) | FTM_SC_CLKS(1); 
	//| FTM_SC_TOIE_MASK;


}

/*
 * Initialize FTM2
 * Used for linescan camera
 */
void InitFTM2() {
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

/* 
 * Initialization of PIT timer to control 
 * Used for linescan camera
 */
void InitPIT(void){
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
 * Set FTM0 Mod
 */
void setFTM0Mod(uint16_t mod)
{
   FTM0_MOD = mod;
}

/* 
 * Set FTM2 Mod
 */
void setFTM2Mod(uint16_t mod)
{
   FTM2_MOD = mod;
}

/* 
 * Set FTM3 Mod
 */
void setFTM3Mod(uint16_t mod)
{
   FTM3_MOD = mod;
}

/*
 * Set FTM0 Channel 0 mod value
 */
void setFTM0Chan0Mod(uint16_t mod)
{
   FTM0_C0V = mod;
}

/*
 * Set FTM0 Channel 1 mod value
 */
void setFTM0Chan1Mod(uint16_t mod)
{
   FTM0_C1V = mod;
}

/*
 * Set FTM0 Channel 2 mod value
 */
void setFTM0Chan2Mod(uint16_t mod)
{
   FTM0_C2V = mod;
}

/*
 * Set FTM0 Channel 3 mod value
 */
void setFTM0Chan3Mod(uint16_t mod)
{
   FTM0_C3V = mod;
}


/*
 * Change the Motor Duty Cycle and Frequency
 * @param DutyCycle (0 to 100)
 * @param Frequency (~1000 Hz to 20000 Hz)
 * @param dir: 1 for C4 active, else C3 active 
 */
void SetMotor1DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/freq) * dutyCycle) / 100);
  
	// Set outputs 
	if(dir==1) {
		FTM0_C0V = mod;
		FTM0_C1V=0;
	}
	else {
		FTM0_C1V = mod;
		FTM0_C0V=0;
	}

	// Update the clock to the new frequency
	FTM0_MOD = (CLOCK/freq);
}

/*
 * Change the Motor Duty Cycle and Frequency
 * @param DutyCycle (0 to 100)
 * @param Frequency (~1000 Hz to 20000 Hz)
 * @param dir: 1 for C4 active, else C3 active 
 */
void SetMotor2DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/freq) * dutyCycle) / 100);
  
	// Set outputs 
	if(dir==1) {
		FTM0_C2V = mod;
		FTM0_C3V=0;
	}
	else {
		FTM0_C3V = mod;
		FTM0_C2V=0;
	}

	// Update the clock to the new frequency
	FTM0_MOD = (CLOCK/freq);
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


