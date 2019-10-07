/*
* Rochester Institute of Technology
* Department of Computer Engineering
* CMPE 460  Interfacing Digital Electronics
* Spring 2016
*
* Filename: main.c
*/
 
#include "uart.h"
#include "MK64F12.h"
#include "stdio.h"

#define PHOTO	0U
#define LM36	1U

#define SENSOR				LM36

uint16_t ADC1VAL;

 
void PDB_INIT(void) {
    //Enable PDB Clock
    SIM_SCGC6 |= SIM_SCGC6_PDB_MASK;
    //PDB0_CNT = 0x0000;
    PDB0_MOD = 50000; // 50,000,000 / 50,000 = 1000

    PDB0_SC = PDB_SC_PDBEN_MASK | PDB_SC_CONT_MASK | PDB_SC_TRGSEL(0xf)
                                    | PDB_SC_LDOK_MASK;
    PDB0_CH1C1 = PDB_C1_EN(0x01) | PDB_C1_TOS(0x01);
}
 
void ADC1_INIT(void) {
	unsigned int calib;

	// Turn on ADC1
	SIM_SCGC3 |= SIM_SCGC3_ADC1_MASK;
	
	// Set PTB10 as ADC input
	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
	PORTB_PCR10 |= PORT_PCR_MUX(0);

	// Configure CFG Registers
	// Configure ADC to divide 50 MHz down to 6.25 MHz AD Clock, 16-bit single ended
	ADC1->CFG1 |= (ADC_CFG1_ADIV_MASK | ADC_CFG1_MODE_MASK);

	// Do ADC Calibration for Singled Ended ADC. Do not touch.
	ADC1_SC3 = ADC_SC3_CAL_MASK;
	while ( (ADC1_SC3 & ADC_SC3_CAL_MASK) != 0 );
	calib = ADC1_CLP0;
	calib += ADC1_CLP1;
	calib += ADC1_CLP2;
	calib += ADC1_CLP3;
	calib += ADC1_CLP4;
	calib += ADC1_CLPS;
	calib = calib >> 1;
	calib |= 0x8000;
	ADC1_PG = calib;

	// Configure SC registers.
	// Select hardware trigger.
	ADC1_SC2 |= ADC_SC2_ADTRG_MASK;


	// Configure SC1A register.
	// Select ADC Channel and enable interrupts. Use ADC1 channel AN14  in single ended mode.
	ADC1_SC1A = (14U << ADC_SC1_ADCH_SHIFT);
	ADC1_SC1A |= (ADC_SC1_AIEN_MASK);


	// Enable NVIC interrupt
	NVIC_EnableIRQ(ADC1_IRQn);
}
 
// ADC1 Conversion Complete ISR
void ADC1_IRQHandler(void) {
    // Read the result (upper 12-bits). This also clears the Conversion complete flag.
    ADC1VAL = ADC1_RA;

    //Set DAC output value (12bit)
    //(Insert your code here.)
}

void DAC0_INIT(void) 
{
    //enable DAC clock
    SIM_SCGC2 |= SIM_SCGC2_DAC0_MASK;
    DAC0_C0 = DAC_C0_DACEN_MASK | DAC_C0_DACRFS_MASK;
    DAC0_C1 = 0;
}
 
int main(void) {
	int i;
	char str[100];
	double tempC;
	double tempF;
	
 
	// Initialize UART
	uart_init();
						 
	DAC0_INIT();
	ADC1_INIT();
	PDB_INIT();

	// Start the PDB (ADC Conversions)
	PDB0_SC |= PDB_SC_SWTRIG_MASK;

	for(;;) {
		#if SENSOR == PHOTO
		sprintf(str,"\n Decimal: %d Hexadecimal: %x \n\r",ADC1VAL,ADC1VAL);
		#elif SENSOR == LM36
		
		tempC = (double) (ADC1VAL + 5000) / 1000;
		tempF = (tempC * ((double)9/(double)5)) + 32;
		
		sprintf(str,"\n Temp: %f C, %f F\n\r",tempC, tempF);
		//sprintf(str,"\n Decimal: %d Hexadecimal: %x \n\r",ADC1VAL,ADC1VAL);
		#endif
		uart_put(str);
		
		for( i=0; i < 5000000; ++i ){
										 
			}
		}

	return 0;
}
 