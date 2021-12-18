#ifndef _INCL_UART_H
#define _INCL_UART_H  //It is used to check if define has been given for other file earlier
//use UART as a way to print out
#define BAUD_RATE 9600
//#define BAUD_PRESCALER (((F_CPU / (BAUD_RATE * 16UL))) - 1)
#define BAUD_PRESCALER (((16000000UL / (BAUD_RATE * 16UL))) - 1)

#include <stdio.h>

void UART_init();

void UART_send( unsigned char data);

void UART_putstring(char* StringPtr);

//passing value
char String[25];

#endif 