/*
 * File:        main.h
 * Purpose:     global variable/function declarations
 *
 * Notes:		
 *
 */
 
 
#ifndef MAIN_H
#define MAIN_H

#include <stdint.h>


extern uint16_t ADC0VAL;

extern int pixcnt;
extern int clkval;
extern uint16_t line[128];

extern int debugcamdata;
extern int capcnt;
extern char str[100];

#endif
