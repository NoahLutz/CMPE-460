/*
 * Main Method for testing the PWM Code for the K64F
 * PWM signal can be connected to output pins are PC3 and PC4
 * 
 * Author:  
 * Created:  
 * Modified:  
 */

#include "MK64F12.h"
#include "uart.h"
#include "pwm.h"

void initialize();
void en_interrupts();
void delay();

int main(void)
{
	// Initialize UART and PWM
	initialize();

	// Print welcome over serial
	uart_put("Running... \n\r");
	
	//Step 3
	//Generate 20% duty cycle at 10kHz
	
	
	PORTB_PCR2 |= PORT_PCR_MUX(1);
	PORTB_PCR3 |= PORT_PCR_MUX(1);
	
	GPIOB_PDDR |= (1 << 2) | (1 << 3);
	GPIOB_PSOR |= (1 << 2) | (1 << 3);
	
	
	
	//for(;;) ;  //then loop forever
	
	//Step 9
	// 0 to 100% duty cycle in forward direction
	for(;;) {
		uint8_t i;
		/*for (i=0; i<100; i++){
			SetMotor1DutyCycle(i, 10000, 0);
			SetMotor2DutyCycle(i, 10000, 0);
			delay(2);
		}
		
		// 100% down to 0% duty cycle in the forward direction
		for (i=100; i>=0; i--){
			SetMotor1DutyCycle(i, 10000, 0);
			SetMotor2DutyCycle(i, 10000, 0);
			delay(2);
		}*/
		
		/*// 0 to 100% duty cycle in reverse direction
		for (i=0; i<100; i++){
			SetMotor1DutyCycle(i, 10000, 1);
			SetMotor2DutyCycle(i, 10000, 1);
			delay(2);
		}
		
		// 100% down to 0% duty cycle in the reverse direction
		for (i=100; i>=0; i--){
			SetMotor1DutyCycle(i, 10000, 1);
			SetMotor2DutyCycle(i, 10000, 1);
			delay(2);
		}*/
		
		for(i=1; i<8; i++) {
			SetServoDutyCycle(1350);
			delay(1000);
		}
	}
		
	//for(;;);
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
	// Initialize UART
	uart_init();	
	
	// Initialize the FlexTimer
	InitMotorPWM();
	InitServoPWM();
}
