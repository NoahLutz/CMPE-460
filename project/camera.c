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

#define RECAL_COUNTER_INIT	50

typedef enum {
	THRESHOLD_NO_CAL = 0,
	THRESHOLD_GOOD_CAL = 1,
	THRESHOLD_BAD_CAL = 2,
	THRESHOLD_NUM_CAL = 3
} ThresholdCalState_t;

typedef struct {
	ThresholdCalState_t state;
	uint16_t recalCounter;
	uint32_t derivThreshold;
	uint32_t whiteDarkAreaThreshold;
} ThresholdCal_t;

ThresholdCal_t threshCal;

char str1[100];
uint16_t smoothedData[ARRAY_SIZE];
uint16_t thresholdData[ARRAY_SIZE];
uint16_t derivData[ARRAY_SIZE];

uint16_t adcCopy[ARRAY_SIZE];
uint16_t smoothedDataCopy[ARRAY_SIZE];
uint16_t derivDataCopy[ARRAY_SIZE];

uint8_t prevMid = 63;

// Private function declarations
void calibrateThresholds(void);
void smoothRawCameraData(uint16_t * const dest, const uint16_t * const adcData, uint8_t length);
void derivitiveFilter(uint16_t * const dest, const uint16_t * const adcData, uint8_t length);
void thresholdFilter(uint16_t * const dest, const uint16_t * const data, uint8_t length, uint32_t threshold);

uint16_t maxValue(const uint16_t * const data, uint8_t length);


// Public Function Definitions

/*
 * Name: 		initCamera
 * 
 * Description: Initializes the camera module
 *
 * Params:		None
 * 
 * Returns: 	None
 */
void initCamera(void)
{
	// Initialize threshCal values
	threshCal.state = THRESHOLD_NO_CAL;
	thresCal.recalCounter = RECAL_COUNTER_INIT;
	threshCal.derivThreshold = 0;
	threshCal.whiteDarkAreaThreshold = 0;

	// zero out all data arrays
	memset(smoothedData, 0U, sizeof(uint16_t) * ARRAY_SIZE);
	memset(smoothedDataCopy, 0U, sizeof(uint16_t) * ARRAY_SIZE);
	memset(thresholdData, 0U, sizeof(uint16_t) * ARRAY_SIZE);
	memset(thresholdDataCopy, 0U, sizeof(uint16_t) * ARRAY_SIZE);
	memset(derivData, 0U, sizeof(uint16_t) * ARRAY_SIZE);
	memset(derivDataCopy, 0U, sizeof(uint16_t) * ARRAY_SIZE);
}

/*
 * Name: 		processCameraData
 * 
 * Description: processes raw ADC data and produces filtered data
 *              used by other functions
 *
 * Params:		*adcData - raw data from the camera ADC
 *				length - length of ADC data
 * 
 * Returns: 	None
 */
void processCameraData(uint16_t *adcData, uint8_t length)
{
	//TODO: may want to zero out first 10 and last 10 values...

	// Copy data into temporary buffer so it's not accidentially clobbered...
	memcpy(adcCopy, adcData, length * sizeof(uint16_t));
	
	// smooth out raw ADC data
	smoothRawCameraData(smoothedData, adcData, length);
   
	// copy smoothed data   
	memcpy(smoothedDataCopy, smoothedData, length * sizeof(uint16_t));
	
	// run derivitave filter over smoothed data
	derivitiveFilter(derivData, smoothedDataCopy, length);


	// Update calibration state
	if (threshCal.state == THRESHOLD_NO_CAL || threshCal.state == THRESHOLD_BAD_CAL) {
		calibrateThresholds();
		thresCal.recalCounter = RECAL_COUNTER_INIT;
	} else {
		// decrement counter for recalibration
		thresCal.recalCounter--;

		// recalibrate next once counter reaches zero
		if (threshCal.recalCounter == 0) {
			threshCal.state = THRESHOLD_BAD_CAL;
		}
	}

	// Only run threshold filter if good calibration
	if (treshCal.state == THRESHOLD_GOOD_CAL) {
		// copy smoothed data   
		memcpy(smoothedDataCopy, smoothedData, length * sizeof(uint16_t));

		// run smoothed data through threshold filter
		thresholdFilter(thresholdData, smoothedDataCopy, length, threshCal.whiteDarkThreshold);
	} else {
		// If calibration is bad, zero out threshold data
		memset(thresholdData, 0U, sizeof(uint6_t) * ARRAY_SIZE);
	}
}

/*
 * Name: 		calibrateThresholds
 * 
 * Description: calibrates thresholds based on ADC data
 *
 * Params:		*adcData - raw data from the camera ADC
 *				length - length of ADC data
 * 
 * Returns: 	None
 */
void calibrateThresholds(void)
{
	uint16_t derivMaxRight = derivData[64];
	uint16_t derivMaxLeft = derivData[63];
	uint16_t derivMax = 0;
	uint16_t smoothedMax = smoothedData[10];
	
	// analyze derivitive peaks
	// NOTE: first and last 10 values are not included
	for(uint8_t i = 65; i < 117; i++) {
		if (derivData[i] > derivMaxRight) {
			derivMaxRight = derivData[i];
		}
	}
	for (uint8_t i = 62; i >= 10; i--) {
		if (derivData[i] > derivMaxLeft) {
			derivMaxLeft = derivData[i];
		}
	}
	if (derivMaxRight > derivMaxLeft) {
		derivMax = derivMaxRight;
	} else {
		derivMax = derivMaxLeft;
	}

	//TODO: may need to adjust what division value is
	threshCal.derivThreshold = derivMax/2;

	// calculate areas based on smoothed data max values
	// NOTE: first and last 10 values are ignored
	for(uint8_t i = 11; i < 117; i++) {
		if(smoothedData[i] > smoothedMax) {
			smoothedMax = smoothedData[i];
		}
	}
	
	//TODO: may need to adjust what division value is
	threshCal.whiteDarkAreaThreshold = (smoothedMax/2) * 108; // 1/2 smoothedMax * [num data elements]

	// Check that we have good threshold values
	if (threshCal.derivThreshold != 0 && threshCal.whiteDarkAreaThreshold != 0) {
		threshCal.state = THRESHOLD_GOOD_CAL;
	} else {
		threshCal.state = THRESHOLD_BAD_CAL;
	}
}

/*
 * Name: 		findCenterPoint
 * 
 * Description: processes camera data and returns the center point of the white
 *				portion of the camera data
 *
 * Params:		None
 * 
 * Returns: 	center point
 */
uint8_t findCenterPoint(void)
{
	uint8_t rightSpike = 127;
	uint8_t leftSpike = 0;

	//TODO: might want to use prevMid as starting point rather than starting at 64
	for (uint8_t i = 64; i < 117; i++) {
		if(thresholdData[i] == 0){
			rightSpike = i;
			break;
		}
	}
	
	for (uint8_t i = 64 - 1; i >= 10; i--) {
		if (thresholdData[i] == 0) {
			leftSpike = i;
			break;
		}
	}

	//return mid-point
	prevMid = leftSpike + ((rightSpike - leftSpike)/2);

	return prevMid;
}


/*
 * Name: calculateArea
 * 
 * Description: Calculates area underneath signal
 *
 * Params:	N/A
 * 
 * Returns: Area under signal
 */
uint32_t calculateArea(void)
{
   uint32_t area = 0;
   for (uint8_t i = 10; i < 117; i++) {
      area+=smoothedData[i];
   }
   return area;
}


/*
 * Name: 		analyzeCameraData
 * 
 * Description: Checks if camera has detected all white or all dark (no edges)
 *
 * Params:		N/A
 * 
 * Returns: 	-1 - no valid data could be determined
 *				0 - has edges
 *          	1 - has one edge
 *          	2 - all white camera data
 *          	3 - all dark camera data
 */
int8_t analyzeCameraData(void)
{
   int8_t retVal = -1;
   uint16_t maxDerivValue = 0;
   uint8_t derivPeaks = 0;
   uint32_t area = 0;
   
	maxDerivValue = maxValue(derivData, ARRAY_SIZE);
	
	if (threshCal.state == THRESHOLD_GOOD_CAL) {
		if (maxDerivValue >= threshCal.derivThreshold) {
		   for (uint8_t i = 0; i < ARRAY_SIZE; i++){
			   if (derivData[i] >= threshCal.derivThreshold) {
				   derivPeaks++;
			   }
		   }
		   if (derivPeaks >= 2) {
			  retVal = 0;
		   } else if (derivPeaks == 1) {
			   retVal = 1;
		   } else {
			   uart_put(UART3, "Should never get here, no peaks found?\r\n");
		   }
	   }
		else {
		  area = calculateArea();

		  if (area >= threshCal.whiteDarkAreaThreshold) {
			retVal = 2;
		  } else {
			uart_put(UART3, "below dark area threshold\r\n");
			retVal = 3;
		  }
	   }
	}

   return retVal;
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
void smoothRawCameraData(uint16_t * const dest, const uint16_t * const adcData, uint8_t length)
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
void derivitiveFilter(uint16_t * const dest, const uint16_t * const adcData, uint8_t length)
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
void thresholdFilter(uint16_t * const dest, const uint16_t * const data, uint8_t length, uint32_t threshold)
{
	//float threshold = maxValue(data, length)/1.6f;

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


