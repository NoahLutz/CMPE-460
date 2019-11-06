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
 

/**********************************************************
*						Public Variable Declarations
**********************************************************/
extern GPIOPin_t clk;
extern GPIOPin_t si;
extern GPIOPin_t redLed;
extern GPIOPin_t motor1Enable;
extern GPIOPin_t motor2Enable;

 
void init_GPIO(void);
void gpio_toggle(GPIOPin_t *ptr);
void gpio_high(GPIOPin_t *ptr);
void gpio_low(GPIOPin_t *ptr);
 
#endif
 
