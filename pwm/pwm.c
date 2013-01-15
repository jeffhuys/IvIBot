//******************************************************************************
//
// Filename :       pwm.c
// Dependencies:    pwm.h
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
#include "pwm/pwm.h"
#include "iviType.h"

#define FORWARD 1
#define BACKWARD 0

#define FALSE 0
#define TRUE  1

#define BYTE unsigned char

BYTE stored_CCPR1L , stored_CCPR2L  ;

//******************************************************************************
//  PWM_init
//
//  Inits both PWM generatore on 18f4550.
//  The timer used for generating the pwm values is also been used
//  voor the generation of the system timer.
//
//  Timerticks/second = 12.000.000 / (4 * 255 * 11) =  1069.....
//  TODO 12.000.000 / ( 4 * 249 * 12 ) = 1000  should be possible
//  than giving a pwm freq of PWMPeriod = [(PR2)+1]�4�TOSC � (TMR2 Prescale Value) = 1/3000
//******************************************************************************

void PWM_init(void) {
    // INIT both PWMS en enable there output pins
    //
//    PR2 = 250; //set PR2 register to set PWM period to 19.53 kHz before prescale
//    T2CON = 0b01011101; //set T2CON register/timer TMR2 to prescale 1:4 gives a PWM freq of 5 khz

    PR2   = 0xFF ;				//set PR2 register to set PWM period to 19.53 kHz before prescale
    T2CON = 0x05;				//set T2CON register/timer TMR2 to prescale 1:4 gives a PWM freq of 5 khz

    //and set post scale to 11
    PIE1bits.TMR2IE = 1; //Timer 2 int enable
    IPR1bits.TMR2IP = 0; //Timer 2 int priority low

    TRISCbits.TRISC2 = 0; //set pin RC2/CCP1/17 as output
    CCP1CON = 0x0C; //set CCP1 to PWM mode

    TRISCbits.TRISC1 = 0; //set pin RC1/CCP2/16 as output
    CCP2CON = 0x0C; //set CCP2 to PWM mode

    CCPR2L = 0; // Start with no output
    CCPR1L = 0;

    TRISEbits.TRISE0 = 0;
    TRISEbits.TRISE1 = 0;
    PORTEbits.RE0 = 0;
    PORTEbits.RE1 = 0;

    RCONbits.IPEN = 1; //enable priority levels
    INTCONbits.GIEL = 1; //enable low prio
    INTCONbits.GIEH = 1; //enable high prio (USB)
}

void RightPWM(int pwmDuty, int threshold) {
    if (pwmDuty < 0) {
        PORTEbits.RE1 = BACKWARD;
        pwmDuty = -pwmDuty + threshold;

        if (pwmDuty > 255) pwmDuty = 255;
        CCPR1L = pwmDuty; // PIC PWM 1 register 8 high bits in PWM reg
    } else {
        PORTEbits.RE1 = FORWARD;
        // Motor turns the other way by inverting the h-bridge
        // the duty cycly should be the 255 complement
        // CCPR2L counter reg pwm2

        if (pwmDuty != 0) pwmDuty += threshold;

        if (pwmDuty > 255) pwmDuty = 255;
        CCPR1L = (BYTE) (255 - (int) pwmDuty); // PIC PWM 1 register 8 high bits in PWM reg (complement)
    }
}

void LeftPWM(int pwmDuty, int threshold) {
    PORTEbits.RE0 = FORWARD;

    if(pwmDuty < 0) {
        PORTEbits.RE0 = BACKWARD;
        pwmDuty = -pwmDuty;
    }

    CCPR2L = pwmDuty; // PIC PWM 1 register 8 high bits in PWM reg

    /*
    if (pwmDuty < 0) {
        PORTEbits.RE0 = BACKWARD;
        pwmDuty = -pwmDuty + threshold;
        if (pwmDuty > 255) pwmDuty = 255;
        CCPR2L = pwmDuty; // PIC PWM 1 register 8 high bits in PWM reg
    } else {
        PORTEbits.RE0 = FORWARD;

        // Motor turns the other way by inverting the h-bridge
        // the duty cycly should be the 255 complement
        // CCPR2L counter reg pwm2

        if (pwmDuty != 0) pwmDuty += threshold;

        if (pwmDuty > 255) pwmDuty = 255;
        CCPR2L = (BYTE) (255 - (int) pwmDuty); // PIC PWM 1 register 8 high bits in PWM reg (complement)
    }
     */
}

void setPR2_REG(BYTE value)
{
	PR2 = value;
}

void setT2CON_REG(BYTE value)
{
	T2CON = value;
}

void setCCP1_MODE_REG(BYTE value)
{
	CCP1CON = value;
}

void setCCP2_MODE_REG(BYTE value)
{
	CCP2CON = value;
}

void setCCPR1L_REG(BYTE value)
{
	CCPR1L = value;
}

void setCCPR2L_REG(BYTE value)
{
	CCPR2L = value;
}

BYTE getPR2_REG(void)
{
	return (BYTE)PR2;
}

BYTE getT2CON_REG(void)
{
	return (BYTE)T2CON;
}

BYTE getCCP1_MODE_REG(void)
{
	return (BYTE)CCP1CON;
}

BYTE getCCP2_MODE_REG(void)
{
	return (BYTE)CCP2CON;
}

BYTE getCCPR1L_REG(void)
{
	return (BYTE)CCPR1L;
}

BYTE getCCPR2L_REG(void)
{
	return (BYTE)CCPR2L;
}