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

#define DERIV_EDGE_THRESHOLD  5500ULL
#define COLOR_WHITE_AREA_THRESHOLD 5000000ULL
#define COLOR_DARK_AREA_THRESHOLD	 1500000ULL

uint8_t startOffset = 0;

char str1[100];
uint16_t smoothedData[ARRAY_SIZE];
uint16_t thresholdData[ARRAY_SIZE];
uint16_t derivData[ARRAY_SIZE];

uint16_t adcCopy[ARRAY_SIZE];
uint16_t smoothedDataCopy[ARRAY_SIZE];
uint16_t derivDataCopy[ARRAY_SIZE];

uint8_t prevMid = 63;

// Private function declarations
void smoothRawCameraData(uint16_t * const dest, const uint16_t * const adcData, uint8_t length);
void derivitiveFilter(uint16_t * const dest, const uint16_t * const adcData, uint8_t length);
void thresholdFilter(uint16_t * const dest, const uint16_t * const data, uint8_t length);

uint16_t maxValue(const uint16_t * const data, uint8_t length);


// Public Function Definitions


/*
 * Name: processCameraData
 * 
 * Description: processes raw ADC data and produces filtered data
 *              used by other functions
 *
 * Params:	*adcData - raw data from the camera ADC
 *			length - length of ADC data
 * 
 * Returns: N/A
 */
void processCameraData(uint16_t *adcData, uint8_t length)
{
   
	// Copy data into temporary buffer so it's not accidentially clobbered...
	memcpy(adcCopy, adcData, length * sizeof(uint16_t));
	
   // smooth out raw ADC data
	smoothRawCameraData(smoothedData, adcData, length);
   
   // copy smoothed data   
	memcpy(smoothedDataCopy, smoothedData, length * sizeof(uint16_t));
	
	// run smoothed data through threshold filter
	thresholdFilter(thresholdData, smoothedDataCopy, length);
	
   // copy smoothed data   
	memcpy(smoothedDataCopy, smoothedData, length * sizeof(uint16_t));
   
  // run derivitave filter over smoothed data
  derivitiveFilter(derivData, smoothedDataCopy, length);
	
}


/*
 * Name: findCenterPoint
 * 
 * Description: processes camera data and returns the center point of the white
 *				portion of the camera data
 *
 * Params:	N/A
 * 
 * Returns: center point
 */
uint8_t findCenterPoint(void)
{

	uint16_t maxDerivValue;
	int8_t rightSpike = -1;
	int8_t leftSpike = -1;

	
	
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

	//uart_put(UART3, str);

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
   for (uint8_t i = 0; i < ARRAY_SIZE-1; i++) {
      area+=smoothedData[i];
   }
   return area;
}


/*
 * Name: hasEdges
 * 
 * Description: Checks if camera has detected all white or all dark (no edges)
 *
 * Params:	N/A
 * 
 * Returns: 0 - has edges
 *          1 - all white camera data
 *          2 - all dark camera data
 *          3 - unable to determine
 */
uint8_t hasEdges(void)
{
   uint8_t retVal = 3;
   uint16_t maxDerivValue;
   uint32_t area;
   
   maxDerivValue = maxValue(derivData, ARRAY_SIZE);
	sprintf(str1, "derivMaxValue: %i\r\n", maxDerivValue);
	//uart_put(UART3,str1);
   if (maxDerivValue >= DERIV_EDGE_THRESHOLD) {
      retVal = 0;
   }
   else {
      area = calculateArea();

      if (area >= COLOR_WHITE_AREA_THRESHOLD) {
         retVal = 1;
      } else if (area <= COLOR_DARK_AREA_THRESHOLD) {
         retVal = 2;
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
void thresholdFilter(uint16_t * const dest, const uint16_t * const data, uint8_t length)
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


