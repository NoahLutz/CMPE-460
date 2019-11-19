/*
 * File:        queue.c
 * Purpose:     Circular Ring buffer queue
 *
 * Notes:		
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include "queue.h"

void initQueue(QueueInfo_t *queuePtr, uint8_t *buffer, uint16_t size)
{
	if (queuePtr != NULL && buffer != NULL) {
		queuePtr->size = size;
		queuePtr->buffer = buffer;
		queuePtr->headPtr = buffer;
		queuePtr->tailPtr = buffer;
		queuePtr->numItems = 0;
	}
}

/**************************************************
* 
* Name:			queueAdd()
*
* Description: 	Adds an item to the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*				data - data to add to queue
*
* Returns: 		true - successfully added item
*				false - failed to add item
*
***************************************************/
bool queueAdd(QueueInfo_t *queuePtr, uint8_t data)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if there is space in queue
		if (queuePtr->numItems < queuePtr->size) {
			// Add items to queue
			queuePtr->numItems++;

			if (queuePtr->tailPtr == queuePtr->buffer + size) {
				queuePtr->tailPtr = buffer;
			} else {
				queuePtr->tailPtr++;
			}
			queuePtr->buffer[queuePtr->tailPtr] = data;
			retVal = true;
		}
	}

	return retVal;
}


/**************************************************
* 
* Name:			queuePop()
*
* Description: 	Pops an item off of the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*				*data - pointer to store the data
*
* Returns: 		true - sucessfully popped item
*				false - failed to pop item
*
***************************************************/
bool queuePop(QueueInfo_t *queuePtr, uint8_t *data)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if queue has items to pop
		if (queuePtr->numItems > 0) {
			*data = *(queueInfo->headPtr);
			if (queueInfo->headPtr == queuePtr->buffer + size) {
				queueInfo->headPtr = buffer;
			} else {
				queueInfo->headPtr++;
			}
			queuInfo->numItems--;
			retVal = true;
		}
	}
	return retVal;
}


/**************************************************
* 
* Name:			queuePeek()
*
* Description: 	Peeks an item at the top of the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*				*data - pointer to store the data
*
* Returns: 		true - sucessfully popped item
*				false - failed to pop item
*
***************************************************/
bool queuePeek(QueueInfo_t *queuePtr, uint8_t *data)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if queue has items to peek
		if (queuePtr->numItems > 0) {
			*data = *(queueInfo->headPtr);
			retVal = true;
		}
	}
	return retVal;
}


/**************************************************
* 
* Name:			queueDrop()
*
* Description: 	Drops the item at the head of the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*
* Returns: 		true - sucessfully dropped item
*				false - failed to drop item
*
***************************************************/
bool queueDrop(QueueInfo_t *queuePtr)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if queue has items to drop
		if (queuePtr->numItems > 0) 
			if (queueInfo->headPtr == queueInfo->buffer) {
				queueInfo->head = queueInfo->buffer;
			} else {
				queueInfo->headPtr++;
			}
		retVal = true;
	}
	return retVal;
}


