

#include "servo.h"
#include "timers.h"
#include "string.h"
#include "stdio.h"
#include "uart.h"


/*
#define SERVO_DEGREE_MULT	1
#define SERVO_MOD_ADJUST	460
#define SERVO_MOD_MAX		2650
#define SERVO_MOD_MIN		1350
#define SERVO_MOD_MID		(SERVO_MOD_MAX - ((SERVO_MOD_MAX-SERVO_MOD_MIN)>>1))
*/

#define SERVO_FREQUENCY			50
#define FTM3_MOD_VALUE			(CLK/16/SERVO_FREQUENCY)



#define SERVO_CENTER		1232 //1750
#define SERVO_MIN				((SERVO_CENTER-250)) // left turn
#define SERVO_MAX				((SERVO_CENTER+250)) // right turn
#define SERVO_INCREMENT	35

float kp = 1.12;
float ki = 0.0; // 0.15
float kd = 0.00; // 0.25

float adjustment_n1;

int32_t err;
int32_t err_n1;
int32_t err_n2;

float calculatAdjustmentPID(uint8_t targetCenter, uint8_t currentCenter);

char str2[100];

/*
 * adjustServoAngle()
 *
 * Change the Servo angle based on given centerpoint data
 */
void adjustServoAngle(uint8_t targetCenter, uint8_t currentCenter)
{
	float adj = calculatAdjustmentPID(targetCenter, currentCenter);
	
	uint16_t mod = SERVO_CENTER + (adj * SERVO_INCREMENT);
	
	if (mod > SERVO_MAX) {
		mod = SERVO_MAX;
	} else if (mod < SERVO_MIN) {
		mod = SERVO_MIN;
	}
	
	sprintf(str2, "mod:%i\r\ncenter:%i\r\n", mod, currentCenter);
	uart_put(UART3, str2);
	setFTM3Chan4Mod(mod);
	setFTM3Mod(FTM3_MOD_VALUE);
}
	
float calculatAdjustmentPID(uint8_t targetCenter, uint8_t currentCenter)
{
	float adjustment = 0;
	err = targetCenter - currentCenter;
	adjustment = adjustment_n1
							+ kp * (err - err_n1)
							+ ki * 0.5f * (err + err_n1)
							+ kd * (err + 2*err_n1 + err_n2);
	if (adjustment >= 64) {
		adjustment = 63;
	}else if (adjustment <= -64) {
		adjustment = -63;
	}
	adjustment_n1 = adjustment;
	err_n2 = err_n1;
	err_n1 = err;
	return adjustment;
}
