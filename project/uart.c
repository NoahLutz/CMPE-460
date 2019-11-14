/*
 * File:        uart.c
 * Purpose:     Provide UART routines for serial IO
 *
 * Notes:		
 *
 */
#include "uart.h"
#include "MK64F12.h"
#include "servo.h"
#include <stddef.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define BAUD_RATE 9600      //default baud rate 
#define SYS_CLOCK 20485760 //default system clock (see DEFAULT_SYSTEM_CLOCK  in system_MK64F12.c)

char buffer[100];
char packet[100];
uint8_t bufferIdx = 0;
bool validPacket = false;

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
		 
		 //uart->C2 |= UART_C2_TIE_MASK | UART_C2_RIE_MASK | UART_C2_TIE_MASK;
		 //NVIC_EnableIRQ(UART3_RX_TX_IRQn);
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
void uart_getchar(UART_Type *uart)
{
   /* Wait until there is space for more data in the receiver buffer*/
   if ((uart->S1 & UART_S1_RDRF_MASK) != 0){
		 buffer[bufferIdx] = uart->D;
		 bufferIdx++;
		 
		 if (buffer[bufferIdx] == 0x0D || buffer[bufferIdx] == 0x0A) {
			 buffer[bufferIdx + 1] = 0x00;
			 bufferIdx = 0;
			 memcpy(packet, buffer, 100);
		 }
	 }

	/* Return the 8-bit data from the receiver */
  // return uart->D;
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


/**************************************************
* 
* updatePIDVars()
*
* Description: 	Sends a string via UART0
*
* Parameters:		ptr_str - string to send
*
* Returns: 			None
*
***************************************************/
void updatePIDVars(void)
{
	//float temp_kp, temp_ki, temp_kd;
	char *tempStr1, *tempStr2;
	
	uart_getchar(UART3);
	
	if (validPacket == true) {
		validPacket = false;
		kp = strtof(packet, &tempStr1);
		ki = strtof(tempStr1, &tempStr2); 
		kd = strtof(tempStr2, NULL);
		
		char resp[100];
		sprintf(resp, "updated PID values to Kp:%f, Ki: %f, Kd: %f\r\n", kp, ki, kd);
		uart_put(UART3, resp);
	}
}