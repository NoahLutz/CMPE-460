/*
 * File:        motor.c
 * Purpose:     Motor related control
 *
 * Notes:		
 *
 */

#include "motor.h"
#include "gpio.h"

#define MOTOR_FREQ   10000U // 10kHz

void EnableMotor1(void)
{
   gpio_high(&motor1Enable);
}

void EnableMotor2(void)
{
   gpio_high(&motor2Enable);
}


void DisableMotor1(void)
{
   gpio_low(&motor1Enable);
}

void DisableMotor2(void)
{
   gpio_low(&motor2Enable);
}

/*
 * Change the Motor Duty Cycle
 * @param DutyCycle (0 to 100)
 * @param dir: 0 for fwd 1 for rev
 */
void SetMotor1DutyCycle(uint16_t dutyCycle, uint8_t dir)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/MOTOR_FREQ) * dutyCycle) / 100);
  
	// Set outputs 
	if(dir==1) {
      setFTM0Chan0Mod(mod);
      setFTM0Chan1Mod(0);
	}
	else {
      setFTM0Chan1Mod(mod);
      setFTM0Chan0Mod(0);
	}

	// Update the clock to the new frequency
   setFMT0Mod(CLOCK/MOTOR_FREQ);
}

/*
 * Change the Motor Duty Cycle
 * @param DutyCycle (0 to 100)
 * @param dir: 0 for fwd 1 for rev
 */
void SetMotor2DutyCycle(uint16_t dutyCycle, uint8_t dir)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (((CLOCK/MOTOR_FREQ) * dutyCycle) / 100);
  
	// Set outputs 
	if(dir==1) {
      setFMT0Chan2Mod(mod);
      setFMT0Chan3Mod(0);
	}
	else {
      setFTM0Chan3Mod(mod);
      setFTM0Chan2Mod(0);
	}

	// Update the clock to the new frequency
	setFTM0Mod(CLOCK/MOTOR_FREQ);
}

