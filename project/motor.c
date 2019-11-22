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

#define FTM0_MOD_VALUE			(CLOCK/PWM_FREQUENCY)

Motor_t motor1;
Motor_t motor2;



void initMotors(void)
{
	motor1.speed = MOTOR_SPEED_LOW;
	motor1.direction = MOTOR_DIR_FWD;
	motor1.modFwd = &FTM0_C0V;
	motor1.modRev = &FTM0_C1V;
	motor1.enabled = false;
	motor1.enablePin = &motor1Enable;

	motor2.speed = MOTOR_SPEED_LOW;
	motor2.direction = MOTOR_DIR_FWD;
	motor2.modFwd = &FMT0_C2V;
	motor2.modRev = &FTM0_C3V;
	motor2.enabled = false;
	motor2.enablePin = &motor2Enable;

	gpio_low(motor1.enablePin);
	gpio_low(motor2.enablePin);

	//Set FTM0 overall mod value
	setFTM0Mod(CLOCK/MOTOR_FREQ);
}

void EnableMotor(Motor_t *motor) {
	motor->enabled = true;
	gpio_high(motor->enablePin);
}

void DisableMotor(Motor_t *motor) {
	motor->enabled = false;
	gpio_low(motor->enablePin);
}

void SetMotorSpeed(Motor_t *motor, MotorSpeed_t speed) {
	uint16_t mod;
   	uint16_t dutyCyle;

	switch(speed) {
		case MOTOR_SPEED_LOW:
			dutyCycle = 35;
			break;
		case MOTOR_SPEED_MED:
			dutyCycle = 50;
			break;
		case MOTOR_SPEED_HIGH:
			dutyCycle = 70;
			break;
		default:
			dutyCycle = 0;
	}

	// Calculate the new cutoff value
	mod = (uint16_t) (((CLOCK/MOTOR_FREQ) * dutyCycle) / 100);


	if(motor->dir == MOTOR_DIR_FWD) {
		motor->modRev = 0;
		motor->modFwd = mod;
	} else {
		motor->modFwd = 0;
		motor->modRev = mod;
	}
}

void SetMotorDirection(Motor_t *motor, MotorDirection_t dir)
{
	uint16_t temp;
	if (motor->direction != dir) {
		motor->direction = dir;
		temp = motor->modRev;
		motor->modRev = motor->modFwd;
		motor->modFwd = temp;
	}
}

void StopMotors(bool hardStop)
{
	MotorSpeed_t prevSpeed1 = motor1.speed;
	MotorSpeed_t prevSpeed2 = motor2.speed;

	if (hardStop == true) {
		if (motor1.direction == MOTOR_DIR_FWD && motor2.direction == MOTOR_DIR_FWD) {
			SetMotorDirection(&motor1, MOTOR_DIR_REV);
			SetMotorDirection(&motor2, MOTOR_DIR_REV);
			SetMotorSpeed(&motor1, MOTOR_SPEED_MED);
			SetMotorSpeed(&motor2, MOTOR_SPEED_MED);
			delay(20);
			DisableMotor(&motor1);
			DisableMotor(&motor2);
			SetMotorSpeed(&motor1, prevSpeed1);
			SetMotorSpeed(&motor2, prevSpeed2);
			SetMotorDirection(&motor1, MOTOR_DIR_FWD);
			SetMotorDirection(&motor2, MOTOR_DIR_FWD);
		} else if (motor1.direction == MOTOR_DIR_REV && motor2.direction == MOTOR_DIR_REV){
			SetMotorDirection(&motor1, MOTOR_DIR_FWD);
			SetMotorDirection(&motor2, MOTOR_DIR_FWD);
			SetMotorSpeed(&motor1, MOTOR_SPEED_MED);
			SetMotorSpeed(&motor2, MOTOR_SPEED_MED);
			delay(20);
			DisableMotor(&motor1);
			DisableMotor(&motor2);
			SetMotorSpeed(&motor1, prevSpeed1);
			SetMotorSpeed(&motor2, prevSpeed2);
			SetMotorDirection(&motor1, MOTOR_DIR_REV);
			SetMotorDirection(&motor2, MOTOR_DIR_REV);
		}
	} else {
		DisableMotor(&motor1);
		DisableMotor(&motor2);
	}
}


//TODO: to be removed below this

void EnableMotor1(void){
	gpio_high(&motor1Enable);
}

void EnableMotor2(void){
	gpio_high(&motor2Enable);
}

void DisableMotor1(void) {
	gpio_low(&motor1Enable);
}

void DisableMotor2(void) {
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

