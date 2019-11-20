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
#include <stdbool.h>

#define IDEAL_CENTER 64

int debugcamdata = 0;
int capcnt = 0;
uint16_t line[ARRAY_SIZE];
char str[100];

bool processCameraFlag = false;

uint8_t centerPoint = 0;
uint32_t area = 0;

void initialize(void);
void delay(int del);

int main(void)
{
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	uart_put(UART3,"Running... \n\r");
	
	
	// Set Motors at constatnt speed for now
	SetMotor1DutyCycle(35, 0);
	SetMotor2DutyCycle(35, 0);
	
	delay(100);
	
   EnableMotor1();
   EnableMotor2();
		
	for(;;) {
		
		updatePIDVars();
		
		if (processCameraFlag == true) {
			processCameraFlag = false;
			
			// Process new camera data
			processCameraData(line, ARRAY_SIZE);
			
			uint8_t edgeVal = analyzeCameraData();

			if (edgeVal == 3) {
				// no edges, all dark camera data
				sprintf(str, "Disabling Motors\r\n");
				uart_put(UART3, "DISABLING MOTORS\r\n");
				DisableMotor1();
				DisableMotor2();
				centerPoint = IDEAL_CENTER;
			} else if (edgeVal == 2) {
				// no edges, all white camera data
				centerPoint = IDEAL_CENTER;
			} else if (edgeVal == 1) {
				// only one edge
				sprintf(str, "has only one edge\r\n");
				//uart_put(UART3, str);
				//TODO: use different function for finding centerpoint if one edge is missing
				centerPoint = findCenterPoint();
			} else if (edgeVal == 0) {
				// two good edges
				sprintf(str, "has both edges\r\n");
				//uart_put(UART3, str);
				centerPoint = findCenterPoint();
			} else if (edgeVal == -1) {
				// only here if we get bad/no calibration
				sprintf(str, "[ERROR] unable to process camera data\r\n[ERROR] bad/no calibration\r\n");
				uart_put(UART3, str);
			}
			
			// adjust servo
			adjustServoAngle(centerPoint, IDEAL_CENTER);
			
			// send debug data if necessary
			if (debugcamdata) {
				// Every 2 seconds
				if (capcnt >= (1)) {
					
					uint16_t data[ARRAY_SIZE];
					uint16_t smoothedData[ARRAY_SIZE];
					uint16_t derivData[ARRAY_SIZE];
					uint16_t thresholdData[ARRAY_SIZE];
					
					memset(smoothedData, 0, sizeof(smoothedData));
					memset(derivData, 0, sizeof(derivData));
					memset(thresholdData, 0, sizeof(thresholdData));
					
					getSmoothedData(smoothedData, ARRAY_SIZE);
					getDerivData(derivData, ARRAY_SIZE);
					getThresholdData(thresholdData, ARRAY_SIZE);
					
					
					memcpy(data, derivData, ARRAY_SIZE * sizeof(uint16_t));
					
					GPIOB_PCOR |= (1 << 22);
					// send the array over uart
					sprintf(str,"%i\n\r",-1); // start value
					uart_put(UART0,str);
					for (int i = 0; i < 127; i++) {
						sprintf(str,"%i\n", data[i]);
						uart_put(UART0, str);
					}
					sprintf(str,"%i\n\r",-2); // end value
					uart_put(UART0,str);
					capcnt = 0;
					GPIOB_PSOR |= (1 << 22);
				}
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
	uart_init(UART0);
   uart_init(UART3);
	
	// Init the ADC
	init_ADC0();
	
	// Initialize the timers
	InitFTM0();
	InitFTM3();
	InitFTM2();
	InitPIT();

	//Init higher level modules
	initCamera();
}
