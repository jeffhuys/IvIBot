#include "includes.h"

void initPorts(void)
{
	setPortBIO(0xFF);
	setPortECIO(0xFF);
	setPortDIO(0xFF);
}

void setPortBIO(BYTE data)
{
	//LATB = 0x00;
	TRISB = data;
}

void setPortECIO(BYTE data)
{
	TRISEbits.TRISE0 = data & 1;
	data = data >> 1;
	TRISEbits.TRISE1 = data & 1;
	data = data >> 1;
	TRISEbits.TRISE2 = data & 1;
	data = data >> 1;
	TRISCbits.TRISC7 = data & 1;
	data = data >> 1;
	TRISCbits.TRISC6 = data & 1;
	data = data >> 1;
	TRISCbits.TRISC0 = data & 1;
	data = data >> 1;
	TRISCbits.TRISC1 = data & 1;
	data = data >> 1;
	TRISCbits.TRISC2 = data & 1;
}

void setPortDIO(BYTE data)
{
	//LATD = 0x00;
	TRISD = data;
}

void setPortBData(BYTE data)
{
	//LATB = 0x00;
	PORTB = data;
}

// Protect PWM outputs
//
void setPortECData(BYTE data) {
	PORTEbits.RE0 = data & 1;
	data = data >> 1;
	PORTEbits.RE1 = data & 1;
	data = data >> 1;
	//PORTEbits.RE2 = data & 1;
	data = data >> 1;
	//PORTCbits.RC7 = data & 1;
	data = data >> 1;
	//PORTCbits.RC6 = data & 1;
	data = data >> 1;
	//PORTCbits.RC0 = data & 1;
	data = data >> 1;
	//PORTCbits.RC1 = data & 1;
	data = data >> 1;
	//PORTCbits.RC2 = data & 1;
}

void setPortDData(BYTE data)
{
	LATD = 0x00;
	PORTD = data;
}

//BYTE getPortB(void)
//{
//	return PORTB;
//}

BYTE getPortEC(void)
{
	BYTE tmp ;
    tmp = PORTEbits.RE0;//0
	tmp |= PORTEbits.RE1 << 1;
	tmp |= PORTEbits.RE2 << 2;
	tmp |= PORTCbits.RC7 << 3;
	tmp |= PORTCbits.RC6 << 4;
	tmp |= PORTCbits.RC0 << 5;
	tmp |= PORTCbits.RC1 << 6;
	tmp |= PORTCbits.RC2 << 7;
	return tmp;
}

BYTE getPortEC_TRIS()
{
	BYTE tmp = 0;
	tmp = TRISEbits.TRISE0;
	tmp |= TRISEbits.TRISE1 << 1;
	tmp |= TRISEbits.TRISE2 << 2;
	tmp |= TRISCbits.TRISC7 << 3;
	tmp |= TRISCbits.TRISC6 << 4;
	tmp |= TRISCbits.TRISC0 << 5;
	tmp |= TRISCbits.TRISC1 << 6;
	tmp |= TRISCbits.TRISC2 << 7;
	return tmp;
}
