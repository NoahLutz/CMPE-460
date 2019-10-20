#ifndef PWM_H_
#define PWM_H_

#include <stdint.h>

void SetDutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir);
void InitPWM(void);
void PWM_ISR();

#endif /* PWM_H_ */
