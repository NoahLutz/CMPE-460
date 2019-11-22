

#include "servo.h"
#include "timers.h"
#include "string.h"
#include "stdio.h"
#include "uart.h"
#include <float.h>
#include <math.h>


/*
#define SERVO_DEGREE_MULT	1
#define SERVO_MOD_ADJUST	460
#define SERVO_MOD_MAX		2650
#define SERVO_MOD_MIN		1350
#define SERVO_MOD_MID		(SERVO_MOD_MAX - ((SERVO_MOD_MAX-SERVO_MOD_MIN)>>1))
*/

#define SERVO_FREQUENCY			50
#define FTM3_MOD_VALUE			(CLK/16/SERVO_FREQUENCY)



#define SERVO_CENTER		1373 //1750
#define SERVO_MIN				((SERVO_CENTER-450)) // left turn
#define SERVO_MAX				((SERVO_CENTER+550)) // right turn
#define SERVO_INCREMENT	20

float kp = 0.61; //1.12;
float ki = 0.050; // 0.15
float kd = 0.8; // 0.7

float adjustment_n1 = 0;

float err = 0;
float err_n1 = 0;
float err_n2 = 0;

float calculatAdjustmentPID(uint8_t targetCenter, uint8_t currentCenter);

char str2[100];

void initServo(void) {
	FTM3_C4V = SERVO_CENTER;
}
/*
 * adjustServoAngle()
 *
 * Change the Servo angle based on given centerpoint data
 */
void adjustServoAngle(uint8_t targetCenter, uint8_t currentCenter)
{
	float adj = 0.0;
	uint32_t mod = 0;
	
	adj = calculatAdjustmentPID(targetCenter, currentCenter);

	mod = SERVO_CENTER + ((int32_t)(adj * SERVO_INCREMENT));
	if (mod > SERVO_MAX) {
		mod = SERVO_MAX;
	} else if (mod < SERVO_MIN) {
		mod = SERVO_MIN;
	}
	
	sprintf(str2, "mod:%i\r\ncenter:%i\r\n", mod, currentCenter);
	//sprintf(str2, "Kp:%f\r\n", kp);
	if (ki > 0.0f) {
		sprintf(str2, "ki bigger than zero");
	} else if (kd > 0.0f) {
		sprintf(str2, "kd bigger than zero");
	}
	uart_put(UART3, str2);
	setFTM3Chan4Mod(mod);
	setFTM3Mod(FTM3_MOD_VALUE);
}
	
float calculatAdjustmentPID(uint8_t targetCenter, uint8_t currentCenter)
{
	float adjustment = 0;
	err =(float) (targetCenter - currentCenter);
	adjustment = adjustment_n1
							+ kp * (err - err_n1)
							+ ki * 0.5f * (err + err_n1)
							+ kd * (err  - 2*err_n1 + err_n2);
	
	if (adjustment >= (SERVO_CENTER/4)) {
		adjustment = SERVO_CENTER/4;
	}else if (adjustment <= -(SERVO_CENTER/4)) {
		adjustment = -SERVO_CENTER/4;
	}
	adjustment_n1 = adjustment;
	err_n2 = err_n1;
	err_n1 = err;
	return adjustment;
}
