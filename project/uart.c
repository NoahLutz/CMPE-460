/*
 * File:        uart.c
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */
#include "queue.h"
#include "uart.h"
#include "MK64F12.h"
#include "servo.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>

#define BAUD_RATE 9600      //default baud rate 
#define SYS_CLOCK 20485760 //default system clock (see DEFAULT_SYSTEM_CLOCK  in system_MK64F12.c)
#define BUFFER_SIZE  100

#define CHAR_CR      0x0D
#define CHAR_LF      0x0A

char buffer[BUFFER_SIZE];
char packet[BUFFER_SIZE];
uint8_t bufferIdx = 0;

QueueInfo_t rxQueue;
uint8_t queueBuf [BUFFER_SIZE];

float strToFloat(char* str);

/**************************************************
* 
* uart_init()
*
* Description: 	Initializes the UART3 module
*
* Parameters:		None
*
* Returns: 			None
*
***************************************************/
void uart_init(UART_Type *uart)
{
   //define variables for baud rate and baud rate fine adjust
   uint16_t ubd, brfa;

   // Initialze RX Queue
   initQueue(&rxQueue, queueBuf, BUFFER_SIZE);
	 
   //Enable clock and pins for UART
   if (uart == UART0) {
      SIM_SCGC4 |= SIM_SCGC4_UART0_MASK;
      SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
      PORTB_PCR16 |= PORT_PCR_MUX(3);
      PORTB_PCR17 |= PORT_PCR_MUX(3);
   } else if (uart == UART3) {
      SIM_SCGC4 |= SIM_SCGC4_UART3_MASK;
      SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;
      PORTB_PCR10 |= PORT_PCR_MUX(3);
      PORTB_PCR11 |= PORT_PCR_MUX(3);
		
      // Enable RX interrupts for UART3
      uart->C2 |= UART_C2_RIE_MASK;
		 //uart->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK | UART_C2_TIE_MASK;
      NVIC_EnableIRQ(UART3_RX_TX_IRQn);
   }

   /*Configure the UART for establishing serial communication*/

   //Disable transmitter and receiver until proper settings are chosen for the UART module
   uart->C2 &= ~(UART_C2_TE_MASK | UART_C2_RE_MASK);

   //Select default transmission/reception settings for serial communication of UART by clearing the control register 1
   uart->C3 = 0;

   //UART Baud rate is calculated by: baud rate = UART module clock / (16 × (SBR[12:0] + BRFD))
   //13 bits of SBR are shared by the 8 bits of UART3_BDL and the lower 5 bits of UART3_BDH 
   //BRFD is dependent on BRFA, refer Table 52-234 in K64 reference manual
   //BRFA is defined by the lower 4 bits of control register, UART0_C4 

   //calculate baud rate settings: ubd = UART module clock/16* baud rate
   ubd = (uint16_t)((SYS_CLOCK)/(BAUD_RATE * 16));  

   //clear SBR bits of BDH
   uart->BDH &= ~(UART_BDH_SBR_MASK);

   //distribute this ubd in BDH and BDL
   uart->BDH |= (ubd >> 8) & UART_BDH_SBR_MASK;
   uart->BDL = ubd & UART_BDL_SBR_MASK;

   //BRFD = (1/32)*BRFA 
   //make the baud rate closer to the desired value by using BRFA
   brfa = (((SYS_CLOCK*32)/(BAUD_RATE * 16)) - (ubd * 32));

   //write the value of brfa in UART0_C4
   uart->C4 |= brfa & UART_C4_BRFA_MASK;

   //Enable transmitter and receiver of UART
   uart->C2 |= (UART_C2_TE_MASK | UART_C2_RE_MASK);
}

/**************************************************
* 
* uart_getchar()
*
* Description: 	Gets a charachter via UART0
*
* Parameters:		None
*
* Returns: 			char received via UART0
*
***************************************************/
uint8_t uart_getchar(UART_Type *uart)
{
   uint8_t retVal = 0;
   /* Wait until there is space for more data in the receiver buffer*/
   if ((uart->S1 & UART_S1_RDRF_MASK) != 0){
      retVal = uart->D;
	}

   return retVal;
}

/**************************************************
* 
* uart_putchar()
*
* Description: 	Sends a charachter via UART0
*
* Parameters:		ch - charachter to send
*
* Returns: 			None
*
***************************************************/
void uart_putchar(UART_Type *uart, char ch)
{
   /* Wait until transmission of previous bit is complete */
   while ((uart->S1 & UART_S1_TDRE_MASK) == 0);

   /* Send the character */
   uart->D = ch;
}

/**************************************************
* 
* uart_put()
*
* Description: 	Sends a string via UART0
*
* Parameters:		ptr_str - string to send
*
* Returns: 			None
*
***************************************************/
void uart_put(UART_Type *uart, char *ptr_str){
	/*use putchar to print string*/
   while (*ptr_str != NULL) {
      uart_putchar(uart, *ptr_str++);
   }
}

void UART3_RX_TX_IRQHandler(void)
{
   if ((UART3->S1 & UART_S1_RDRF_MASK) != 0) {
      if (queueAdd(&rxQueue, UART3->D) == false) {
         //uart_put(UART0, "Failed to send via BT\r\n");
      }
   }
}


/**************************************************
* 
* Name: 		updatePIDVars()
*
* Description: 	checks for update for PID variables
*
* Parameters:	None
*
* Returns: 		None
*
***************************************************/
void updatePIDVars(void)
{
	bool validPacket = false;
	float temp_kp, temp_ki, temp_kd;
	char *kp_str, *ki_str, *kd_str;
	
	char kp_str_cpy[100];
	char ki_str_cpy[100];
	char kd_str_cpy[100];

	char delim1[2] = " ";
	uint8_t c;
	
   // get char from uart if available
   if (rxQueue.numItems > 0) {
      if (queuePop(&rxQueue, &c)) {
         if (c != CHAR_CR && c != CHAR_LF && bufferIdx < BUFFER_SIZE) {
            buffer[bufferIdx] = c;
            bufferIdx++;
         } else if (c == CHAR_LF) {
            bufferIdx = 0;
            validPacket = true;
            memcpy(packet, buffer, sizeof(uint8_t) * BUFFER_SIZE);
         }
      }
   }
	
	if (validPacket == true) {
		// Chop up string by delemiter
		kp_str = strtok(packet, delim1);
		strcpy(kp_str_cpy, kp_str);
		ki_str = strtok(NULL, delim1);
		strcpy(ki_str_cpy, ki_str);
		kd_str = strtok(NULL, delim1);
		strcpy(kd_str_cpy, kd_str);
		
		//Convert substrings to floats
		temp_kp = strToFloat(kp_str_cpy);
		temp_ki = strToFloat(ki_str_cpy);
		temp_kd = strToFloat(kd_str_cpy);
		
		//Update true values
		kp = temp_kp;
		ki = temp_ki;
		kd = temp_kd;
		
		// send response
		char resp[BUFFER_SIZE];
		sprintf(resp, "updated PID values to Kp:%f, Ki: %f, Kd: %f\r\n", kp, ki, kd);
		uart_put(UART3, resp);
	}
}

/**************************************************
* 
* Name: 		strToFloat()
*
* Description: 	Custom strtof function because the stdlib ones don't work 
*				NOTE: will return bad values if string is not clean
*
* Parameters:	*str - ptr to string to convert
*						must follow following format : "xx.xxxx"		
*
* Returns: 		parsed float value of string
*
***************************************************/
float strToFloat(char *str)
{
	char delim[2] = ".";
	char strBuf[BUFFER_SIZE];
	char *upper, *lower;
	float value = 0.0f;

	strcpy(strBuf, str);
	
	upper = strtok(strBuf, delim);
	for (uint8_t i = strlen(upper); i>0; i--) {
		uint8_t power = i - 1;
		float currentVal = upper[i-1] - '0';
		value += currentVal * pow(10.0, power);
	}

	lower = strtok(NULL, delim);
	for (uint8_t i = 0; i < strlen(lower); i++) {
		uint8_t power = i + 1;
		float currentVal = lower[i] - '0';
		value += currentVal * pow(10.0, -1.0f*power);
	}

	return value;
}


