/*
 * File:        camera.h
 * Purpose:     Camera related processing
 *
 * Notes:		
 *
 */

#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include <stdlib.h>

#define ARRAY_SIZE   128U

void processCameraData(uint16_t *adcData, uint8_t length);
uint8_t findCenterPoint(void);
uint32_t calculateArea(void);

void getSmoothedData(uint16_t *dest, uint8_t length);
void getDerivData(uint16_t *dest, uint8_t length);
void getThresholdData(uint16_t *dest, uint8_t length);


#endif
