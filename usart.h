#ifndef __USART_H
#define __USART_H

#include "includes.h"

#define mDataRdyUSART() PIR1bits.RCIF
#define mTxRdyUSART()   TXSTAbits.TRMT

void initUSART(void) ;
unsigned char getcUSART(void) ;

void putcUSART(char c); 
void putStrUSART(char *str) ;

#endif