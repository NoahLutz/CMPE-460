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

uint8_t processCameraData(uint16_t *adcData, uint8_t length);

void getSmoothedData(uint16_t *dest, uint8_t length);
void getDerivData(uint16_t *dest, uint8_t length);
void getThresholdData(uint16_t *dest, uint8_t length);


#endif
