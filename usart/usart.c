// Init ussrt at 112500 baud for connecting to Wt12
#include <p18f4550.h>
#include <osa.h>

#include "xlcd/xlcd.h"

#define mDataRdyUSART() PIR1bits.RCIF
#define mTxRdyUSART()   TXSTAbits.TRMT


void initUSART(void) {
	char c ;
// Transmit and recv mode
	TXSTA = 0b00100100;       	// TX enable BRGH=1
//            76543210
	RCSTA = 0b10010000;       	// Single Character RX
//            76543210
// Baudrate config	
	BAUDCON = 0b00001000;     	// BRG16 = 1
//              76543210
//   SPBRGH:SPBRG: =((FOSC/Desired Baud Rate)/4) – 1 
	SPBRGH = 0x00;      	
	SPBRG  = 0x67;
	c = RCREG;				    // read clear data 
}//end InitializeUSART


void putcUSART(char c) {
    PORTB = 0x0f;
	while(!mTxRdyUSART());
	TXREG = c;
    PORTB = 0x0;
}

void putStrUSART(char *str) {
	int i = 0 ;
	while ( str[i] ) putcUSART(str[i++]) ;
}

//  getcUSART() wait until a valid char arrived in usart;
//

unsigned char getcUSART(void) {
	char  c;

	if (RCSTAbits.OERR)  { // in case of overrun error we should never see an overrun error, but if we do, 
		RCSTAbits.CREN = 0;  // reset the port
		c = RCREG;
		RCSTAbits.CREN = 1;  // and keep going.
	}
	else {
	    while ( !mDataRdyUSART() ) ; // Wait in input
    	c = RCREG;
 	}   
	XLCDPut(c) ;
// not necessary.  EUSART auto clears the flag when RCREG is cleared
    PIR1bits.RCIF = 0;    // clear Flag

	return c;
}
//------------------------------------------------------------------------------
extern void initUSART(void) ;
extern unsigned char getcUSART(void) ;

extern void ADC_init(void);
extern void PWM_init(void);
extern void RightPWM(int pwmDuty, int threshold) ;
extern void LeftPWM(int pwmDuty, int threshold) ;

#define MVALUE  150 ;
#define MADD    40	
int      lm = 0 , rm = 0 ;
char c;
unsigned char b1, b2 ;

void Task_Usart(void) {

	initUSART() ;

    for (;;) {
		lm = 0 ;
		rm = 0 ;
        OS_Wait(PIR1bits.RCIF ) ;
	    c = RCREG ; 
		PIR1bits.RCIF = 0 ;

		if ( c == 0xa1 ) {
	        OS_Wait(PIR1bits.RCIF ) ;
			c = RCREG ; 
			PIR1bits.RCIF = 0 ;
	        
			if ( c == 0x30 ) { 
				OS_Wait(PIR1bits.RCIF ) ;
			    b1 = RCREG ; 
				PIR1bits.RCIF = 0 ;

		        OS_Wait(PIR1bits.RCIF ) ;
			    b2 = RCREG ; 
				PIR1bits.RCIF = 0 ;

				if (b1 & 0x01 ) { // button left
					rm += MADD ;
					lm += MADD ;
					XLCDPut('L');
				} 
				if (b1 & 0x02 ) { // button right
					XLCDPut('R');
					rm -= MADD ;
					lm -= MADD ;
				} 
				if (b1 & 0x04 ) { // button down
					rm += MADD ;
					lm -= MADD ;
					XLCDPut('D');
				} 
				if (b1 & 0x08 ) { // button up
					rm -= MADD ;
					lm += MADD ;
					XLCDPut('U');
				} 
				if (b1 & 0x10 ) { // button +
					XLCDPut('+');
				} 

				if (b2 & 0x01 ) { // button 2
					lm += MVALUE ;
					rm += MVALUE ;
					XLCDPut('2');
				} 
				if (b2 & 0x02 ) { // button 1
					lm -= MVALUE ;
					rm -= MVALUE ;
					XLCDPut('1');
				} 
				if (b2 & 0x04 ) { // button B
					XLCDPut('B');
				} 
				if (b2 & 0x08 ) { // button A
					XLCDPut('A');
				} 
				if (b2 & 0x10 ) { // button -
					XLCDPut('-');
				} 
				if (b2 & 0x80 ) { // button home
					XLCDPut('H');
				} 
				//CCPR1L = rm ;
 				//CCPR2L = lm ;
 				RightPWM(rm, 0) ;
 				LeftPWM(lm, 0) ;
			}
			else {
				XLCDPut('?') ;
			}
 		}
		else  { 
			XLCDPut(c); 
		}
    }
}

int sendAndExpect(char *command, char * result, int echo) {
	int i = 0 ; 
    char c ;
	//XLCDPutRamString(command) ;	
	//while ( mDataRdyUSART() ) {
	//	c = getcUSART() ;
		// sleep so to be sure there is no char in transmission
	//	OS_Delay(1) ;
	//} 	
	
    while ( command[i] ) {
		//XLCDPut(command[i]) ;
		putcUSART(command[i]) ;
		if ( echo ) {
			c = getcUSART() ;
			//XLCDPut(c) ;

			if ( c != command[i] ) {
				// There is an echo error
				// Show error
				//return 0 ; 
			}
		}
		// next part get the expected response
		i++ ;
	}
	i = 0 ;
    while ( result[i] ) {
		c = getcUSART() ;
		if ( c != result[i] ) {
			// not the expected result
			return 0 ;
		} 
		
		i++ ;
	}
	return 1 ;
}
