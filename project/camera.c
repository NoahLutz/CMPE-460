/*
 * File:        camera.c
 * Purpose:     Camera related processing
 *
 * Notes:		
 *
 */

#include "camera.h"
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

uint16_t adcCopy[128];
uint16_t smoothedData[128];
uint16_t smoothedDataCopy[128];
uint16_t derivData[128];

uint8_t prevMid = 63;

// Private function declarations
void smoothRawCameraData(const uint16_t * const adcData, uint16_t * const dest, uint8_t length);
void derivitiveFilter(const uint16_t * const adcData, uint16_t * const dest, uint8_t length);
uint16_t maxValue(const uint16_t * const data, uint8_t length);


// Public Function Definitions

/*
 * Name: processCameraData
 * 
 * Description: processes camera data and returns the center point of the white
 *				portion of the camera data
 *
 * Params:	*adcData - raw data from the camera ADC
 *			length - length of ADC data
 * 
 * Returns: center point
 */
uint8_t processCameraData(uint16_t *adcData, uint8_t length)
{
	uint16_t maxDerivValue;
	int8_t rightSpike = -1;
	int8_t leftSpike = -1;

	memcpy(adcCopy, adcData, length);
	smoothRawCameraData(adcCopy, smoothedData, length);

	memcpy(smoothedDataCopy, smoothedData, length);
	derivitiveFilter(smoothedDataCopy, derivData, length);

	maxDerivValue = maxValue( (const uint16_t*)&derivData, length);

	// Find the inner two spikes
	for (uint8_t i = prevMid; i < 127; i++) {
		if (derivData[i] >= maxDerivValue/2) {
			rightSpike = i;
		}
	}

	for (uint8_t i = prevMid - 1; i <= 0; i--) {
		if (derivData[i] >= maxDerivValue/2) {
			leftSpike = i;
		}
	}

	//return mid-point
	prevMid = ((rightSpike - leftSpike)/2);

	return prevMid;
}

/*
 * Name: getSmoothedData
 * 
 * Description: Copies smoothed ADC data into provided array
 *
 * Params:	*dest - ptr to destination array
 *			length - length of dest array
 * 
 * Returns: N/A
 */
void getSmoothedData(uint16_t *dest, size_t length)
{
	memcpy(dest, smoothedData, length);
}

/*
 * Name: getDerivData
 * 
 * Description: Copies derivative data into provided array
 *
 * Params:	*dest - ptr to destination array
 *			length - length of dest array
 * 
 * Returns: N/A
 */
void getDerivData(uint16_t *dest, size_t length)
{
	memcpy(dest, derivData, length);
}


// Private Function Definitions

/*
 * Name: smoothRawCameraData
 * 
 * Description: Runs a 5-point averaging filter on data
 *
 * Params:	*adcData - point to data to average
 *			*dest - destination array
 *			length - length of data array
 * 
 * Returns: N/A
 */
void smoothRawCameraData(const uint16_t * const adcData, uint16_t * const dest, uint8_t length)
{
	for (uint8_t i = 2; i < length-3; i++) {
		dest[i] = (adcData[i-2] + adcData[i-1] + adcData[i] + adcData[i+1] + adcData[i+2])/5;
	}
}

/*
 * Name: derivitaveFilter
 * 
 * Description: Runs a derivative filter over array of values
 *
 * Params:	*adcData - point to data 
 *			*dest - destination array
 *			length - length of data array
 * 
 * Returns: N/A
 */
void derivitiveFilter(const uint16_t * const adcData, uint16_t * const dest, uint8_t length)
{
	for (uint8_t i = 1; i < length-2; i++) {
		dest[i] = abs(adcData[i+1] - adcData[i-1])/3;
	}
}

/*
 * Name: maxValue
 * 
 * Description: Finds the maximum value in an array of values
 *
 * Params:	*data- pointer to data 
 *			length - length of data array
 * 
 * Returns: maximum value
 */
uint16_t maxValue(const uint16_t * const data, uint8_t length)
{
	uint16_t maxVal = data[0];
	for (uint8_t i = 1; i < length; i++) {
		if (data[i] > maxVal) {
			maxVal = data[i];
		}
	}
	return maxVal;
}

