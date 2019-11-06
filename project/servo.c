

#include "servo.h"
#include "timers.h"


/*
#define SERVO_DEGREE_MULT	1
#define SERVO_MOD_ADJUST	460
#define SERVO_MOD_MAX		2650
#define SERVO_MOD_MIN		1350
#define SERVO_MOD_MID		(SERVO_MOD_MAX - ((SERVO_MOD_MAX-SERVO_MOD_MIN)>>1))
*/

#define SERVO_FREQUENCY			50
#define FTM3_MOD_VALUE			(CLOCK/16/SERVO_FREQUENCY)


#define SERVO_CENTER		1850
#define SERVO_MIN				1500
#define SERVO_MAX				2200
#define SERVO_INCREMENT	35

/*
 * adjustServoAngle()
 *
 * Change the Servo angle based on given centerpoint data
 */
void adjustServoAngle(uint8_t centerPoint, uint8_t idealCenter)
{
	uint16_t mod;
	uint8_t diff;
	if (centerPoint > idealCenter) {
		diff = centerPoint - idealCenter;
		mod = SERVO_CENTER + (diff * SERVO_INCREMENT);
	} else if (centerPoint < idealCenter) {
		diff = idealCenter - centerPoint;
		mod = SERVO_CENTER - (diff * SERVO_INCREMENT);
	}
	if (centerPoint == idealCenter) {
		mod = SERVO_CENTER;
	}
	
	if (mod > SERVO_MAX) {
		mod = SERVO_MAX;
	} else if (mod < SERVO_MIN) {
		mod = SERVO_MIN;
	}
	
	setFTM3Chan4Mod(mod);
	setFTM3Mod(FTM3_MOD_VALUE);
}
