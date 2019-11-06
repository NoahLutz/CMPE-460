/*
 * File:        motor.c
 * Purpose:     Motor related control
 *
 * Notes:		
 *
 */

#include "motor.h"
#include "gpio.h"
#include "timers.h"

#define CLOCK					20485760u

#define MOTOR_FREQ   10000U // 10kHz
#define SERVO_FREQUENCY			50

#define FTM0_MOD_VALUE			(CLOCK/PWM_FREQUENCY)
#define FTM3_MOD_VALUE			(CLOCK/16/SERVO_FREQUENCY)

#define SERVO_DEGREE_MULT	1
#define SERVO_MOD_ADJUST	460
#define SERVO_MOD_MAX		2650
#define SERVO_MOD_MIN		1350
#define SERVO_MOD_MID		(SERVO_MOD_MAX - ((SERVO_MOD_MAX-SERVO_MOD_MIN)>>1))

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
   setFTM0Mod(CLOCK/MOTOR_FREQ);
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
      setFTM0Chan2Mod(mod);
      setFTM0Chan3Mod(0);
	}
	else {
      setFTM0Chan3Mod(mod);
      setFTM0Chan2Mod(0);
	}

	// Update the clock to the new frequency
	setFTM0Mod(CLOCK/MOTOR_FREQ);
}

//TODO: this needs to be tested before plugging into the servo again
/*
 * Change the Servo angle
 * @param degrees (-35 to 30) //TODO: this is going to change
 */
void SetServoDutyCycle(int8_t degrees)
{
	// Calculate the new cutoff value
	uint16_t mod = (uint16_t) (SERVO_MOD_MID + (degrees * SERVO_DEGREE_MULT)) - SERVO_MOD_ADJUST;
  
	// Set outputs 
	setFTM3Chan4Mod(mod);

	// Update the clock to the new frequency
	setFTM3Mod(FTM3_MOD_VALUE);
}
