
#include "camera.h"
#include <stdint.h>
#include <stdlib.h>

// Private function declarations



// Public Function Definitions
uint8_t processCameraData(uint16_t *adcData, uint8_t length)
{
	
}


void smoothRawCameraData(const uint16_t * const adcData, uint16_t * const dest, size_t length)
{
	for (uint8_t i = 2; i < length-3; i++) {
		dest[i] = (adcData[i-2] + adcData[i-1] + adcData[i] + adcData[i+1] + adcData[i+2])/5;
	}
}

void derivitaveFilter(const uint16_t * const adcData, uint16_t * const dest, size_t length)
{
	for (uint8_t i = 1; i < length-2; i++) {
		dest[i] = abs((adcData[i-1]*-1 + adcData[i+1]))/3;
	}
}

// Private Function Definitions