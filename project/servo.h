

#ifndef SERVO_H
#define SERVO_H

#include<stdint.h>

extern float kp;
extern float ki;
extern float kd;

void adjustServoAngle(uint8_t centerPoint, uint8_t idealCenter);


#endif
