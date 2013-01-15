#include "usart.h"

void initUSART(void) {
    BYTE c ;
    TXSTA = 0x24;       	// TX enable BRGH=1
    RCSTA = 0x90;       	// Single Character RX
    SPBRG = 0x67;
    SPBRGH = 0x0;
    BAUDCON = 0x08;     	// BRG16 = 1
    c = RCREG;				// read

}//end InitializeUSART


void putcUSART(char c) {
//    PORTB = 0x0f;
    while(!mTxRdyUSART());
	TXREG = c;
//    PORTB = 0x0;
}

void putStrUSART(char *str) {
	int i = 0 ;
        XLCDClear();
	while ( str[i] ) {
            XLCDPut(str[i]);
            putcUSART(str[i++]);
        }
        putcUSART((char)13);
}

void sendCommand(rom char *string) {
    while(*string) {
        putcUSART(*string);
        XLCDPut(*string);
        *string++;
    }
    putcUSART((char)13);
    XLCDPut((char)13);
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
	//XLCDPut(c) ;
// not necessary.  EUSART auto clears the flag when RCREG is cleared
    PIR1bits.RCIF = 0;    // clear Flag

	return c;
}
