/*
 * File:        main.c
 * Purpose:     Main 
 *
 * Notes:		
 *
 */

#include "MK64F12.h"
#include "main.h"
#include "uart.h"
#include "timers.h"
#include "adc.h"
#include "camera.h"
#include "gpio.h"
#include <stdio.h>
#include <string.h>

int debugcamdata = 1;
int capcnt = 0;
uint16_t line[128];
char str[100];

void initialize();
void delay();

int main(void)
{
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	uart_put("Running... \n\r");
	
	PORTB_PCR2 |= PORT_PCR_MUX(1);
	PORTB_PCR3 |= PORT_PCR_MUX(1);
	
	GPIOB_PDDR |= (1 << 2) | (1 << 3);
	//GPIOB_PSOR |= (1 << 2) | (1 << 3);
	GPIOB_PCOR |= (1 << 2) | (1 << 3);

	// Set Motors at constatnt speed for now
	SetMotor1DutyCycle(30,  10000, 0);
	SetMotor2DutyCycle(30, 10000, 0);
	
	
		
	for(;;) {
		if (debugcamdata) {
			// Every 2 seconds
			if (capcnt >= (500)) {
				
				uint16_t data[128];
				uint16_t smoothedData[128];
				uint16_t derivData[128];
				
				memset(smoothedData, 0, sizeof(smoothedData));
				memset(derivData, 0, sizeof(derivData));
				
				smoothRawCameraData(line, smoothedData, sizeof(line));
				derivitaveFilter(smoothedData, derivData, sizeof(smoothedData));
				
				memcpy(data, line, sizeof(data));
				
				GPIOB_PCOR |= (1 << 22);
				// send the array over uart
				sprintf(str,"%i\n\r",-1); // start value
				uart_put(str);
				for (int i = 0; i < 127; i++) {
					sprintf(str,"%i\n", data[i]);
					uart_put(str);
				}
				sprintf(str,"%i\n\r",-2); // end value
				uart_put(str);
				capcnt = 0;
				GPIOB_PSOR |= (1 << 22);
			}
		}
		
		// Process new camera data
		
		// adjust servo
		
	}
		
	return 0;
}


/**
 * Waits for a delay (in milliseconds)
 * 
 * del - The delay in milliseconds
 */
void delay(int del){
	int i;
	for (i=0; i<del*50000; i++){
		// Do nothing
	}
}

void initialize()
{
	// Init GPIO
	init_GPIO();
	
	// Initialize UART
	uart_init();
	
	// Init the ADC
	init_ADC0();
	
	// Initialize the timers
	InitFTM0();
	InitFTM3();
	InitFTM2();
	InitPIT();
}
