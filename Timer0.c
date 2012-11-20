//******************************************************************************
//  
// Filename :       Timer0.c  
// Dependencies:    PIC18
// Processor:       PIC18
// Complier:        MCC18 v3.37 or higher
// Company:         HVA.
// Auther:	        Ferry
// Date:            2011-03-11
// Version:         1.0
//   
// PURPOSE-
// Initilize timer 0 en set isr vor timertick
//******************************************************************************

#include <p18f4550.h>
#include <OSA.h>

//----------------------------------------------------------------------------
// Init Timer 0  with enabled INTERRupt routine
// Currently noy used
//
#define LOWTIMERBYTE     0x6a

// NOTE:
// As of the implemantation of OSA the timer0 is no longer used as system clock.
//
void InitTimer0(){
  RCONbits.IPEN = 1;            //enable priority levels
  INTCONbits.TMR0IE = 1;        //TMR0 interrupt on overflow
  INTCONbits.GIEL = 1;          //enable low prio
  INTCONbits.GIEH = 1;          //enable high prio (USB)	
  INTCON2bits.TMR0IP = 0;       //TMR0 low priority

/* T0CON values
			bit 7 TMR0ON: Timer0 On/Off Control bit 
			1 = Enables Timer0 
			0 = Stops Timer0
			bit 6 T08BIT: Timer0 8-Bit/16-Bit Control bit 
			1 = Timer0 is configured as an 8-bit timer/counter 
			0 = Timer0 is configured as a 16-bit timer/counter 
			bit 5 T0CS: Timer0 Clock Source Select bit 
			1 = Transition on T0CKI pin 
			0 = Internal instruction cycle clock (CLKO) 
			bit 4 T0SE: Timer0 Source Edge Select bit
			1 = Increment on high-to-low transition on T0CKI pin 
			0 = Increment on low-to-high transition on T0CKI pin 
			bit 3 PSA: Timer0 Prescaler Assignment bit 
			1 = TImer0 prescaler is NOT assigned. Timer0 clock input bypasses prescaler. 
			0 = Timer0 prescaler is assigned. Timer0 clock input comes from prescaler output.
			bit 2-0 T0PS2:T0PS0: Timer0 Prescaler Select bits    
			111 = 1:256 Prescale value
			110 = 1:128 Prescale value
			101 = 1:64   Prescale value
			100 = 1:32   Prescale value
			011 = 1:16   Prescale value
			010 = 1:8     Prescale value
			001 = 1:4     Prescale value
			000 = 1:2     Prescale value
*/
//  T0CON = 0x82;                 //set up timer0 see abive
    T0CON = 0b11000010;           //set up timer0 see above
    TMR0L = LOWTIMERBYTE;          //set timer int on overflow

    INTCONbits.GIEH = 1;          //enable interrupts
    T0CONbits.TMR0ON = 1 ;        // Turn on timer
}

//----------------------------------------------------------------------------
// Low priority interrupt vector
void InterruptHandlerLow() ;
#pragma code InterruptVectorLow = 0x1018
void InterruptVectorLow(void) {
  _asm
    goto InterruptHandlerLow //jump to interrupt routine
  _endasm
}

//----------------------------------------------------------------------------
// Low priority interrupt routine
#pragma code
#pragma interrupt InterruptHandlerLow
//
// Timer2 expired
void InterruptHandlerLow() {
    if (PIR1bits.TMR2IF) {   //check for timer2 postscaled int
		PIR1bits.TMR2IF = 0 ;
		//PORTBbits.RB4 = ~PORTBbits.RB4 ; 
		OS_Timer() ;  // OS timer tick needed for OS_delay() functions.
		return ;
	}
}