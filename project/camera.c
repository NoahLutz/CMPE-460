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
#include <stdio.h>
#include "uart.h"

#define MIN_DIFF	10

uint8_t startOffset = 0;


uint16_t smoothedData[128];
uint16_t thresholdData[128];
uint16_t derivData[128];

uint16_t adcCopy[128];
uint16_t smoothedDataCopy[128];
uint16_t derivDataCopy[128];

uint8_t prevMid = 63;

// Private function declarations
void smoothRawCameraData(const uint16_t * const adcData, uint16_t * const dest, uint8_t length);
void derivitiveFilter(const uint16_t * const adcData, uint16_t * const dest, uint8_t length);
void thresholdFilter(const uint16_t * const data, uint16_t * const dest, uint8_t length);
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

	// Copy data into temporary buffer so it's not accidentially clobbered...
	memcpy(adcCopy, adcData, length * sizeof(uint16_t));
	
	smoothRawCameraData(adcCopy, smoothedData, length);
	
	memcpy(smoothedDataCopy, smoothedData, length * sizeof(uint16_t));
	
	
	thresholdFilter(smoothedDataCopy, thresholdData, length);
	
	//derivitiveFilter(smoothedDataCopy, derivData, length);
	//memcpy(derivDataCopy, derivData, length*sizeof(uint16_t));
	
	//thresholdFilter(derivDataCopy, thresholdDeriv, length);
	
	//maxDerivValue = maxValue(derivData, length);
	
	for (uint8_t i = 64; i < 127; i++) {
		if(thresholdData[i] == 0){
			rightSpike = i;
			break;
		}
	}
	
	for (uint8_t i = 64 - 1; i >= 0; i--) {
		if (thresholdData[i] == 0) {
			leftSpike = i;
			break;
		}
	}

	//return mid-point
	prevMid = leftSpike + ((rightSpike - leftSpike)/2);
	
	char str[100];
	sprintf(str, "left: %i\r\n right: %i\r\n mid:%i\r\n", leftSpike, rightSpike, prevMid);
	uart_put(UART3, str);

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
void getSmoothedData(uint16_t *dest, uint8_t length)
{
	memcpy(dest, smoothedData, sizeof(uint16_t) * length);
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
void getDerivData(uint16_t *dest, uint8_t length)
{
	memcpy(dest, derivData, sizeof(uint16_t) * length);
}

/*
 * Name: getThresholdDeriv
 * 
 * Description: Copies derivative data into provided array
 *
 * Params:	*dest - ptr to destination array
 *			length - length of dest array
 * 
 * Returns: N/A
 */
void getThresholdData(uint16_t *dest, uint8_t length)
{
	memcpy(dest, thresholdData, sizeof(uint16_t) * length);
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
 * Name: threshold flter
 * 
 * Description: Runs a threshold filter over array of values
 * 							threshold is half of maximum value found in array
 *
 * Params:	*adcData - point to data 
 *			*dest - destination array
 *			length - length of data array
 * 
 * Returns: N/A
 */
void thresholdFilter(const uint16_t * const data, uint16_t * const dest, uint8_t length)
{
	float threshold = maxValue(data, length)/1.6f;

	for (uint8_t i = 0; i < length-1; i++) {
		if (data[i] <= threshold) {
			dest[i] = 0;
		} else {
			dest[i] = 1;
		}
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

