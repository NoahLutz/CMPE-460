/*
 * File:        queue.c
 * Purpose:     Circular Ring buffer queue
 *
 * Notes:		
 *
 */

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "queue.h"

/**************************************************
* 
* Name:			initQueue()
*
* Description:	Initializes a queue
*
* Parameters:	queuePtr - pointer to allocated queue info struct
*				*buffer - pointer to allocated buffer block
*				size - size of the buffer
*
* Returns: 		None
*
***************************************************/
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
* Description:	Adds an item to the queue
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
			*queuePtr->tailPtr = data;
			
         if (queuePtr->tailPtr == queuePtr->buffer + queuePtr->size) {
				queuePtr->tailPtr = queuePtr->buffer;
			} else {
				queuePtr->tailPtr++;
			}
			retVal = true;
		}
	}

	return retVal;
}


/**************************************************
* 
* Name:			queuePop()
*
* Description:	Pops an item off of the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*				*data - pointer to store the data
*
* Returns:		true - sucessfully popped item
*				false - failed to pop item
*
***************************************************/
bool queuePop(QueueInfo_t *queuePtr, uint8_t *data)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if queue has items to pop
		if (queuePtr->numItems > 0) {
			*data = *(queuePtr->headPtr);
			if (queuePtr->headPtr == queuePtr->buffer + queuePtr->size) {
				queuePtr->headPtr = queuePtr->buffer;
			} else {
				queuePtr->headPtr++;
			}
			queuePtr->numItems--;
			retVal = true;
		}
	}
	return retVal;
}


/**************************************************
* 
* Name:		  	queuePeek()
*
* Description:	Peeks an item at the top of the queue
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
			*data = *(queuePtr->headPtr);
			retVal = true;
		}
	}
	return retVal;
}


/**************************************************
* 
* Name:			queueDrop()
*
* Description:	Drops the item at the head of the queue
*
* Parameters:	queuePtr - pointer to queue info struct
*
* Returns: 		true - sucessfully dropped item
*				   false - failed to drop item
*
***************************************************/
bool queueDrop(QueueInfo_t *queuePtr)
{
	bool retVal = false;
	if (queuePtr != NULL) {
		// Check if queue has items to drop
		if (queuePtr->numItems > 0) 
			if (queuePtr->headPtr == queuePtr->buffer) {
				queuePtr->headPtr = queuePtr->buffer;
			} else {
				queuePtr->headPtr++;
			}
		retVal = true;
	}
	return retVal;
}


