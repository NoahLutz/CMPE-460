#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void SetMotor1DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir);
void SetMotor2DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir);
void SetServoDutyCycle(int8_t degrees);
void InitMotorPWM(void);
void InitServoPWM(void);


#endif /* PWM_H_ */
