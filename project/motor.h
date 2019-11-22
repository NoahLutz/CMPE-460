/*
 * File:        motor.h
 * Purpose:     Motor routines
 *
 * Notes:		
 *
 */
#ifndef MOTOR_H
#define MOTOR_H

#include <stdint.h>
#include <stdbool.h>

typedef enum {
	MOTOR_SPEED_OFF,
	MOTOR_SPEED_LOW,
	MOTOR_SPEED_MED,
	MOTOR_SPEED_HIGH
} MotorSpeed_t;

typedef enum {
	MOTOR_DIR_FWD = 0,
	MOTOR_DIR_REV = 1
} MotorDirection_t;

typedef struct {
	MotorSpeed_t speed;
	MotorDirection_t direction;
	volatile uint16_t *modFwd;
	volatile uint16_t *modRev;
	bool enabled;
	GpioPin_t *enablePin
} Motor_t;

extern Motor_t motor1;
extern Motor_t motor2;

void initMotors(void);

void EnableMotor(Motor_t *motor);
void DisableMotor(Motor_t *motor);

void SetMotorSpeed(Motor_t *motor, MotorSpeed_t speed);
void SetMotorDirection(Motor_t *motor, MotorDirection_t dir);
void StopMotors(bool hardStop);

// TODO: remove all of these
void SetMotor1DutyCycle(uint16_t dutyCycle, uint8_t dir)
void SetMotor2DutyCycle(uint16_t dutyCycle, uint8_t dir)
void EnableMotor1(void);
void EnableMotor2(void);
void DisableMotor1(void);
void DisableMotor2(void);

#endif

