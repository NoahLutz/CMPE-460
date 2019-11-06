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
#include "servo.h"
#include "motor.h"
#include <stdio.h>
#include <string.h>

#define IDEAL_CENTER 63

int debugcamdata = 1;
int capcnt = 0;
uint16_t line[128];
char str[100];

uint8_t centerPoint = 0;

void initialize(void);
void delay(int del);

int main(void)
{
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	uart_put("Running... \n\r");
	
	
	// Set Motors at constatnt speed for now
	SetMotor1DutyCycle(30, 0);
	SetMotor2DutyCycle(30, 0);
	
	
  //EnableMotor1();
  //EnableMotor2();
		
	for(;;) {
		// Process new camera data
		centerPoint = processCameraData(line, 128);
		
		// adjust servo
		adjustServoAngle(100, IDEAL_CENTER);
		
		// send debug data if necessary
		if (debugcamdata) {
			// Every 2 seconds
			if (capcnt >= (100)) {
				
				uint16_t data[128];
				uint16_t smoothedData[128];
				uint16_t derivData[128];
				
				memset(smoothedData, 0, sizeof(smoothedData));
				memset(derivData, 0, sizeof(derivData));
				
				getSmoothedData(smoothedData, sizeof(smoothedData));
				getDerivData(derivData, sizeof(smoothedData));
				
				
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
