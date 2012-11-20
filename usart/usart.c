// Init ussrt at 112500 baud for connecting to Wt12
#include <p18f4550.h>
#include <osa.h>
#include "GenericTypeDefs.h"                        // Required

#include "xlcd/xlcd.h"
#include "port.h"

/** V A R I A B L E **********************************************************/
unsigned char ReportData[50];
unsigned char CommandData[50];
unsigned int  CommandLength = 0 ;
unsigned char NextCharIn = 0;

unsigned long SystemTime = 0;
unsigned long counter0   = 0 ;
unsigned long counter1   = 0 ;

#define mDataRdyUSART() PIR1bits.RCIF
#define mTxRdyUSART()   TXSTAbits.TRMT

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
    PORTB = 0x0f;
	while(!mTxRdyUSART());
	TXREG = c;
    PORTB = 0x0;
}

void putStrUSART(char *str) {
	int i = 0 ;
	while ( str[i] ) {
            putcUSART(str[i++]);
        }
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
//------------------------------------------------------------------------------
extern void initUSART(void) ;
extern unsigned char getcUSART(void) ;

extern void ADC_init(void);
extern void PWM_init(void);
extern void RightPWM(int pwmDuty, int threshold) ;
extern void LeftPWM(int pwmDuty, int threshold) ;

void procesCommand(void) ;
void sendReport(void) ;
void initTimer(void) ;

#define MVALUE  150 ;
#define MADD    40	
int      lm = 0 , rm = 0 ;
char c;
unsigned char b1, b2 ;

void Task_Usart(void) {
    setPortBIO(0x00); // Set port B in output mode
    setPortDIO(0x00); // Set port D in output mode

    PORTB=0x55 ;
    OS_Delay(2000) ;  // modem has to init
    initUSART();
    OS_Delay(2000) ;  // modem has to init
    PORTB= 0 ;

    putStrUSART((char *)"reset\n") ;  // RESET modem
    OS_Delay(500) ;  // modem has to init

    CommandData[0] = 0;
    NextCharIn = 0;

    PORTB = 0 ;

    while (1) {

        int stuffed = 0; // Are we in a escape sequence?
        NextCharIn = 0; //

        OS_Delay(100);

        while (1) {

            OS_Delay(100);

            if (mDataRdyUSART()) { // USART has serial data ready
                c = getcUSART();
                if (!stuffed) {
                    if (c == '\\') { // entered escape sequense stage
                        stuffed = 1;
                        continue;
                    }
                    stuffed = 0; // Only one byte escaped

                    if (c == 27) { // Recieved ascii ESC reset input buffer and start over
                        NextCharIn = 0;
                        continue;
                    }
                    if (c == 13 || c == 10) { // ascii NL or CR
                        CommandData[NextCharIn] = 0;
                        if (NextCharIn == 0) continue; // Recieved multiple NL or CR start over
                        else break; // we have a command break out while
                    }
                }
                CommandData[NextCharIn++] = c;
                if (NextCharIn == 32) break; // Command should not be langer than 32 bytes
                //PORTB = c ; // small debug on leds.
            }
        }
        CommandLength = NextCharIn; // Can do without, make NextChar in the target
        procesCommand();
        sendReport();
        OS_Delay(50);
    }
}

//int sendAndExpect(char *command, char * result, int echo) {
//	int i = 0 ;
//    char c ;
//	//XLCDPutRamString(command) ;
//	//while ( mDataRdyUSART() ) {
//	//	c = getcUSART() ;
//		// sleep so to be sure there is no char in transmission
//	//	OS_Delay(1) ;
//	//}
//
//    while ( command[i] ) {
//		//XLCDPut(command[i]) ;
//		putcUSART(command[i]) ;
//		if ( echo ) {
//			c = getcUSART() ;
//			//XLCDPut(c) ;
//
//			if ( c != command[i] ) {
//				// There is an echo error
//				// Show error
//				//return 0 ;
//			}
//		}
//		// next part get the expected response
//		i++ ;
//	}
//	i = 0 ;
//    while ( result[i] ) {
//		c = getcUSART() ;
//		if ( c != result[i] ) {
//			// not the expected result
//			return 0 ;
//		}
//
//		i++ ;
//	}
//	return 1 ;
//}
