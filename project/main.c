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

int debugcamdata = 1;
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
	
  //EnableMotor1();
  //EnableMotor2();
		
	for(;;) {
		
		updatePIDVars();
		
		if (processCameraFlag == true) {
			processCameraFlag = false;
			
			// Process new camera data
			processCameraData(line, ARRAY_SIZE);
			area = calculateArea();
			
			uint8_t edgeVal = hasEdges();
			if (edgeVal == 2 || edgeVal == 3) {
				sprintf(str, "Disabling Motors\r\n");
				uart_put(UART3, "DISABLING MOTORS\r\n");
				
				
				SetMotor1DutyCycle(35, 1);
				SetMotor2DutyCycle(35, 1);
				delay(20);
				DisableMotor1();
				DisableMotor2();
				SetMotor1DutyCycle(35, 0);
				SetMotor2DutyCycle(35, 0);
				centerPoint = IDEAL_CENTER;
			} else if (edgeVal == 1) {
				sprintf(str, "all white\r\n");

				centerPoint = IDEAL_CENTER;
			} else if (edgeVal == 0) {
				EnableMotor1();
				EnableMotor2();
				sprintf(str, "has edges\r\n");

				centerPoint = findCenterPoint();
			}
			
			//centerPoint = IDEAL_CENTER;
			
			//uint16_t derivMaxVal = 
			//uart_put(UART3, str);
			sprintf(str, "area: %i\r\n", area);
			//uart_put(UART3, str);
			
				

      //centerPoint = findCenterPoint();

      //area = calculateArea();
			
			//sprintf(str, "areaData: %i\r\n", area);
			//uart_put(str);

			//sprintf(str, "Center Point: %i\r\nArea: %i\r\n", centerPoint, area);
			//uart_put(str);
			
			// adjust servo
			adjustServoAngle(IDEAL_CENTER, centerPoint);
			
			delay(10);
			
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
					
					
					memcpy(data, thresholdData, ARRAY_SIZE * sizeof(uint16_t));
					
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
}
