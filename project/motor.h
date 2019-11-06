/*
 * File:        motor.h
 * Purpose:     Motor routines
 *
 * Notes:		
 *
 */
#ifndef MOTOR_H
#define MOTOR_H

void EnableMotor1(void);
void EnableMotor2(void);
void DisableMotor1(void);
void DisableMotor2(void);

void SetMotor1DutyCycle(uint16_t dutyCycle, uint8_t dir);
void setMotor2DutyCycle(uint16_t dutyCycle, uint8_t dir);

#endif MOTOR_H

