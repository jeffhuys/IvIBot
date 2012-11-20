#ifndef __USART_H
#define __USART_H
#include "commands.h"

void initUSART(void) ;
unsigned char getcUSART(void) ;

void putcUSART(char c); 
void putStrUSART(char *str) ;

#endif