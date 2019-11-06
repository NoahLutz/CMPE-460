
#ifndef CAMERA_H
#define CAMERA_H

#include <stdint.h>
#include <stdlib.h>

uint8_t processCameraData(uint16_t *adcData, uint8_t length);

void smoothRawCameraData(const uint16_t * const adcData, uint16_t * const dest, size_t length);
void derivitaveFilter(const uint16_t * const adcData, uint16_t * const dest, size_t length);

#endif
