//******************************************************************************
//
// Filename :       adc.c
// Dependencies:    none
// Processor:       PIC18
// Complier:        MCC18 v3.40 or higher
// Company:         HVA.
// Auther:	    Ferry
// Date:            2012-02-09
// Version:         1.0
//
//
//******************************************************************************

#include <p18f4550.h>

void ADC_init() ;
int getAD(char adcselector) ;

#define  AD0SELECTOR 0x03
#define  AD1SELECTOR 0x07
#define  AD2SELECTOR 0x0B
#define  AD3SELECTOR 0x0F
#define  AD8SELECTOR 0x23



#define  getAD0() getAD(AD0SELECTOR)
#define  getAD1() getAD(AD1SELECTOR)
#define  getAD2() getAD(AD2SELECTOR)
#define  getAD3() getAD(AD3SELECTOR)
#define  getAD8() getAD(AD8SELECTOR)


//******************************************************************************
//  adc_init
//
//  Inits analog ports this is really important because the analog ports
//  are multiplexed with the digitalports failing to initialize will
//  result in erratic behavior.
//******************************************************************************
void ADC_init() {
    //Configure analog pins, voltage reference and digital IO, ADCON1
    TRISA = 0xDF; // All input port A5 as output
    ADCON1 = 0x06; //Use AN0 to AN8, 8 channel

    //Select AD acquisition time and AD conversion clock, ADCON2
    ADCON2 = 0xA6;

    //Turn on AD module, ADCON0 bit 0;
    ADCON0 |= 0x1;
}

int getAD(char adcselector) {
	//set channel to ad0, start conversion
	ADCON0 = adcselector;
	//wait for adconversion to be done
	while(ADCON0 & 2) {;} //nop

	// 10 bit A/D last 2 bit are higest bits
	return  ((unsigned int)ADRESH << 8)|(ADRESL) ;
}
