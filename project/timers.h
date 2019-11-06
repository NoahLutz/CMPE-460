

#ifndef TIMERS_H
#define TIMERS_H

#include <stdint.h>

#define DEFAULT_SYSTEM_CLOCK 20485760u /* Default System clock value */
#define CLOCK					20485760u



void InitFTM0(void);
void InitFTM2(void);
void InitFTM3(void);
void InitPIT(void);

void setFTM0Chan0Mod(uint16_t mod);
void setFTM0Chan1Mod(uint16_t mod);
void setFTM0Chan2Mod(uint16_t mod);
void setFTM0Chan3Mod(uint16_t mod);
void setFMT3Chan4Mod(uint16_t mod);
void setFTM2Mod(uint16_t mod);
void setFTM3Mod(uint16_t mod);

/*void SetMotor1DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir);
void SetMotor2DutyCycle(uint16_t dutyCycle, uint16_t freq, uint8_t dir);
void SetServoDutyCycle(int8_t degrees);
*/

#endif
