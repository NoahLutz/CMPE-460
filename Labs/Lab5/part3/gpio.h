/*
 * File:        gpio.h
 * Purpose:     Provide GPIO routines
 *
 * Notes:		
 *
 */
 
 #include <stdint.h>
 #include "MK64F12.h"
 
 #ifndef GPIO_H
 #define GPIO_H
 
	
 typedef struct {
	 GPIO_Type* port;
	 uint8_t pin;
 } GPIOPin_t;
 

 
 void init_GPIO(void);
 
 #endif
 