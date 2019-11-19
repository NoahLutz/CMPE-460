/*
 * File:        queue.h
 * Purpose:     generic queue header
 *
 * Notes:		
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
	uint16_t size;
	uint16_t numItems;
	uint8_t *headPtr;
	uint8_t *tailPtr;
	uint8_t *buffer;
} QueueInfo_t;

void initQueue(QueueInfo_t *queuePtr, uint8_t *buffer, uint16_t size);
bool queueAdd(QueueInfo_t *queuePtr, uint8_t data);
bool queuePop(QueueInfo_t *queuePtr, uint8_t *data);
bool queuePeek(QueueInfo_t *queuePtr, uint8_t *data);
bool queueDrop(QueueInfo_t *queuePtr);

#endif
