/*********************************************************************
 *
 *                  External LCD access routines defs
 *
 *********************************************************************
 * FileName:        XLCD.h
 * Dependencies:    compiler.h
 * Processor:       PIC18
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement 
 *
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Naveen Raj     6/9/03  Original        (Rev 1.0)
 ********************************************************************/
#ifndef __XLCD_H
#define __XLCD_H
#define AddFile ///ADD_PROC_INC_FILE
#include <p18f4550.h>
#include "xlcd/XLCD.Def"

/* DATA_PORT defines the port to which the LCD data lines are connected */


#if ((XLCD_DATA_PORT ^ 0) == 0)
#define XLCD_DATAPORT       PORTA
#define XLCD_DATAPORT_TRIS  TRISA
#endif

#if ((XLCD_DATA_PORT ^ 1) == 0)
#define XLCD_DATAPORT       PORTB
#define XLCD_DATAPORT_TRIS  TRISB
#endif

#if ((XLCD_DATA_PORT ^ 2) == 0)
#define XLCD_DATAPORT       PORTC
#define XLCD_DATAPORT_TRIS  TRISC
#endif

#if ((XLCD_DATA_PORT ^ 3) == 0)
#define XLCD_DATAPORT       PORTD
#define XLCD_DATAPORT_TRIS  TRISD
#endif

#if ((XLCD_DATA_PORT ^ 4) == 0)
#define XLCD_DATAPORT       PORTE
#define XLCD_DATAPORT_TRIS  TRISE
#endif

#if ((XLCD_DATA_PORT ^ 5) == 0)
#define XLCD_DATAPORT       PORTF
#define XLCD_DATAPORT_TRIS  TRISF
#endif

#if ((XLCD_DATA_PORT ^ 6) == 0)
#define XLCD_DATAPORT       PORTG
#define XLCD_DATAPORT_TRIS  TRISG
#endif

#if ((XLCD_DATA_PORT ^ 7) == 0)
#define XLCD_DATAPORT       PORTH
#define XLCD_DATAPORT_TRIS  TRISH
#endif

#if ((XLCD_DATA_PORT ^ 8) == 0)
#define XLCD_DATAPORT       PORTJ
#define XLCD_DATAPORT_TRIS  TRISJ
#endif

/* CTRL_PORT defines the port where the control lines are connected.
 * These are just samples, change to match your application.
 */

//ReadWrite Pin
#if ((XLCD_RW_PIN ^ 0x00) == 0)
#define XLCD_RWPIN   PORTAbits.RA0
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA0
#endif
#if ((XLCD_RW_PIN ^ 0x01) == 0)
#define XLCD_RWPIN   PORTAbits.RA1
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA1
#endif
#if ((XLCD_RW_PIN ^ 0x02) == 0)
#define XLCD_RWPIN   PORTAbits.RA2
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA2
#endif
#if ((XLCD_RW_PIN ^ 0x03) == 0)
#define XLCD_RWPIN   PORTAbits.RA3
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA3
#endif
#if ((XLCD_RW_PIN ^ 0x04) == 0)
#define XLCD_RWPIN   PORTAbits.RA4
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA4
#endif
#if ((XLCD_RW_PIN ^ 0x05) == 0)
#define XLCD_RWPIN   PORTAbits.RA5
#define XLCD_RWPIN_TRIS  TRISAbits.TRISA5
#endif

#if ((XLCD_RW_PIN ^ 0x10) == 0)
#define XLCD_RWPIN   PORTBbits.RB0
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB0
#endif
#if ((XLCD_RW_PIN ^ 0x11) == 0)
#define XLCD_RWPIN   PORTBbits.RB1
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB1
#endif
#if ((XLCD_RW_PIN ^ 0x12) == 0)
#define XLCD_RWPIN   PORTBbits.RB2
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB2
#endif
#if ((XLCD_RW_PIN ^ 0x13) == 0)
#define XLCD_RWPIN   PORTBbits.RB3
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB3
#endif
#if ((XLCD_RW_PIN ^ 0x14) == 0)
#define XLCD_RWPIN   PORTBbits.RB4
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB4
#endif
#if ((XLCD_RW_PIN ^ 0x15) == 0)
#define XLCD_RWPIN   PORTBbits.RB5
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB5
#endif
#if ((XLCD_RW_PIN ^ 0x16) == 0)
#define XLCD_RWPIN   PORTBbits.RB6
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB6
#endif
#if ((XLCD_RW_PIN ^ 0x17) == 0)
#define XLCD_RWPIN   PORTBbits.RB7
#define XLCD_RWPIN_TRIS  TRISBbits.TRISB7
#endif

#if ((XLCD_RW_PIN ^ 0x20) == 0)
#define XLCD_RWPIN   PORTCbits.RC0
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC0
#endif
#if ((XLCD_RW_PIN ^ 0x21) == 0)
#define XLCD_RWPIN   PORTCbits.RC1
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC1
#endif
#if ((XLCD_RW_PIN ^ 0x22) == 0)
#define XLCD_RWPIN   PORTCbits.RC2
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC2
#endif
#if ((XLCD_RW_PIN ^ 0x23) == 0)
#define XLCD_RWPIN   PORTCbits.RC3
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC3
#endif
#if ((XLCD_RW_PIN ^ 0x24) == 0)
#define XLCD_RWPIN   PORTCbits.RC4
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC4
#endif
#if ((XLCD_RW_PIN ^ 0x25) == 0)
#define XLCD_RWPIN   PORTCbits.RC5
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC5
#endif
#if ((XLCD_RW_PIN ^ 0x26) == 0)
#define XLCD_RWPIN   PORTCbits.RC6
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC6
#endif
#if ((XLCD_RW_PIN ^ 0x27) == 0)
#define XLCD_RWPIN   PORTCbits.RC7
#define XLCD_RWPIN_TRIS  TRISCbits.TRISC7
#endif

#if ((XLCD_RW_PIN ^ 0x30) == 0)
#define XLCD_RWPIN   PORTDbits.RB0
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD0
#endif
#if ((XLCD_RW_PIN ^ 0x31) == 0)
#define XLCD_RWPIN   PORTDbits.RD1
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD1
#endif
#if ((XLCD_RW_PIN ^ 0x32) == 0)
#define XLCD_RWPIN   PORTDbits.RD2
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD2
#endif
#if ((XLCD_RW_PIN ^ 0x33) == 0)
#define XLCD_RWPIN   PORTDbits.RD3
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD3
#endif
#if ((XLCD_RW_PIN ^ 0x34) == 0)
#define XLCD_RWPIN   PORTDbits.RD4
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD4
#endif
#if ((XLCD_RW_PIN ^ 0x35) == 0)
#define XLCD_RWPIN   PORTDbits.RD5
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD5
#endif
#if ((XLCD_RW_PIN ^ 0x36) == 0)
#define XLCD_RWPIN   PORTDbits.RD6
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD6
#endif
#if ((XLCD_RW_PIN ^ 0x37) == 0)
#define XLCD_RWPIN   PORTDbits.RD7
#define XLCD_RWPIN_TRIS  TRISDbits.TRISD7
#endif

#if ((XLCD_RW_PIN ^ 0x40) == 0)
#define XLCD_RWPIN   PORTEbits.RE0
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE0
#endif
#if ((XLCD_RW_PIN ^ 0x41) == 0)
#define XLCD_RWPIN   PORTEbits.RE1
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE1
#endif
#if ((XLCD_RW_PIN ^ 0x42) == 0)
#define XLCD_RWPIN   PORTEbits.RE2
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE2
#endif
#if ((XLCD_RW_PIN ^ 0x43) == 0)
#define XLCD_RWPIN   PORTEbits.RE3
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE3
#endif
#if ((XLCD_RW_PIN ^ 0x44) == 0)
#define XLCD_RWPIN   PORTEbits.RE4
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE4
#endif
#if ((XLCD_RW_PIN ^ 0x45) == 0)
#define XLCD_RWPIN   PORTEbits.RE5
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE5
#endif
#if ((XLCD_RW_PIN ^ 0x46) == 0)
#define XLCD_RWPIN   PORTEbits.RE6
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE6
#endif
#if ((XLCD_RW_PIN ^ 0x47) == 0)
#define XLCD_RWPIN   PORTEbits.RE7
#define XLCD_RWPIN_TRIS  TRISEbits.TRISE7
#endif

#if ((XLCD_RW_PIN ^ 0x50) == 0)
#define XLCD_RWPIN   PORTFbits.RF0
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF0
#endif
#if ((XLCD_RW_PIN ^ 0x51) == 0)
#define XLCD_RWPIN   PORTFbits.RF1
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF1
#endif
#if ((XLCD_RW_PIN ^ 0x52) == 0)
#define XLCD_RWPIN   PORTFbits.RF2
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF2
#endif
#if ((XLCD_RW_PIN ^ 0x53) == 0)
#define XLCD_RWPIN   PORTFbits.RF3
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF3
#endif
#if ((XLCD_RW_PIN ^ 0x54) == 0)
#define XLCD_RWPIN   PORTFbits.RF4
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF4
#endif
#if ((XLCD_RW_PIN ^ 0x55) == 0)
#define XLCD_RWPIN   PORTFbits.RF5
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF5
#endif
#if ((XLCD_RW_PIN ^ 0x56) == 0)
#define XLCD_RWPIN   PORTFbits.RF6
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF6
#endif
#if ((XLCD_RW_PIN ^ 0x57) == 0)
#define XLCD_RWPIN   PORTFbits.RF7
#define XLCD_RWPIN_TRIS  TRISFbits.TRISF7
#endif

#if ((XLCD_RW_PIN ^ 0x60) == 0)
#define XLCD_RWPIN   PORTGbits.RG0
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG0
#endif
#if ((XLCD_RW_PIN ^ 0x61) == 0)
#define XLCD_RWPIN   PORTGbits.RG1
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG1
#endif
#if ((XLCD_RW_PIN ^ 0x62) == 0)
#define XLCD_RWPIN   PORTGbits.RG2
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG2
#endif
#if ((XLCD_RW_PIN ^ 0x63) == 0)
#define XLCD_RWPIN   PORTGbits.RG3
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG3
#endif
#if ((XLCD_RW_PIN ^ 0x64) == 0)
#define XLCD_RWPIN   PORTGbits.RG4
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG4
#endif
#if ((XLCD_RW_PIN ^ 0x65) == 0)
#define XLCD_RWPIN   PORTGbits.RG5
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG5
#endif
#if ((XLCD_RW_PIN ^ 0x66) == 0)
#define XLCD_RWPIN   PORTGbits.RG6
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG6
#endif
#if ((XLCD_RW_PIN ^ 0x67) == 0)
#define XLCD_RWPIN   PORTGbits.RG7
#define XLCD_RWPIN_TRIS  TRISGbits.TRISG7
#endif

#if ((XLCD_RW_PIN ^ 0x70) == 0)
#define XLCD_RWPIN   PORTHbits.RH0
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH0
#endif
#if ((XLCD_RW_PIN ^ 0x71) == 0)
#define XLCD_RWPIN   PORTHbits.RH1
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH1
#endif
#if ((XLCD_RW_PIN ^ 0x72) == 0)
#define XLCD_RWPIN   PORTHbits.RH2
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH2
#endif
#if ((XLCD_RW_PIN ^ 0x73) == 0)
#define XLCD_RWPIN   PORTHbits.RH3
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH3
#endif
#if ((XLCD_RW_PIN ^ 0x74) == 0)
#define XLCD_RWPIN   PORTHbits.RH4
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH4
#endif
#if ((XLCD_RW_PIN ^ 0x75) == 0)
#define XLCD_RWPIN   PORTHbits.RH5
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH5
#endif
#if ((XLCD_RW_PIN ^ 0x76) == 0)
#define XLCD_RWPIN   PORTHbits.RH6
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH6
#endif
#if ((XLCD_RW_PIN ^ 0x77) == 0)
#define XLCD_RWPIN   PORTHbits.RH7
#define XLCD_RWPIN_TRIS  TRISHbits.TRISH7
#endif

#if ((XLCD_RW_PIN ^ 0x80) == 0)
#define XLCD_RWPIN   PORTJbits.RJ0
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ0
#endif
#if ((XLCD_RW_PIN ^ 0x81) == 0)
#define XLCD_RWPIN   PORTJbits.RJ1
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ1
#endif
#if ((XLCD_RW_PIN ^ 0x82) == 0)
#define XLCD_RWPIN   PORTJbits.RJ2
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ2
#endif
#if ((XLCD_RW_PIN ^ 0x83) == 0)
#define XLCD_RWPIN   PORTJbits.RJ3
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ3
#endif
#if ((XLCD_RW_PIN ^ 0x84) == 0)
#define XLCD_RWPIN   PORTJbits.RJ4
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ4
#endif
#if ((XLCD_RW_PIN ^ 0x85) == 0)
#define XLCD_RWPIN   PORTJbits.RJ5
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ5
#endif
#if ((XLCD_RW_PIN ^ 0x86) == 0)
#define XLCD_RWPIN   PORTJbits.RJ6
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ6
#endif
#if ((XLCD_RW_PIN ^ 0x87) == 0)
#define XLCD_RWPIN   PORTJbits.RJ7
#define XLCD_RWPIN_TRIS  TRISJbits.TRISJ7
#endif

//////////////////////////////////////////////////////////////////////////////

//RS Pin
//////////////////////////////////////////////////////////////////////////////

#if ((XLCD_RS_PIN ^ 0x00) == 0)
#define XLCD_RSPIN   PORTAbits.RA0
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA0
#endif
#if ((XLCD_RS_PIN ^ 0x01) == 0)
#define XLCD_RSPIN   PORTAbits.RA1
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA1
#endif
#if ((XLCD_RS_PIN ^ 0x02) == 0)
#define XLCD_RSPIN   PORTAbits.RA2
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA2
#endif
#if ((XLCD_RS_PIN ^ 0x03) == 0)
#define XLCD_RSPIN   PORTAbits.RA3
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA3
#endif
#if ((XLCD_RS_PIN ^ 0x04) == 0)
#define XLCD_RSPIN   PORTAbits.RA4
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA4
#endif
#if ((XLCD_RS_PIN ^ 0x05) == 0)
#define XLCD_RSPIN   PORTAbits.RA5
#define XLCD_RSPIN_TRIS  TRISAbits.TRISA5
#endif

#if ((XLCD_RS_PIN ^ 0x10) == 0)
#define XLCD_RSPIN   PORTBbits.RB0
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB0
#endif
#if ((XLCD_RS_PIN ^ 0x11) == 0)
#define XLCD_RSPIN   PORTBbits.RB1
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB1
#endif
#if ((XLCD_RS_PIN ^ 0x12) == 0)
#define XLCD_RSPIN   PORTBbits.RB2
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB2
#endif
#if ((XLCD_RS_PIN ^ 0x13) == 0)
#define XLCD_RSPIN   PORTBbits.RB3
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB3
#endif
#if ((XLCD_RS_PIN ^ 0x14) == 0)
#define XLCD_RSPIN   PORTBbits.RB4
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB4
#endif
#if ((XLCD_RS_PIN ^ 0x15) == 0)
#define XLCD_RSPIN   PORTBbits.RB5
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB5
#endif
#if ((XLCD_RS_PIN ^ 0x16) == 0)
#define XLCD_RSPIN   PORTBbits.RB6
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB6
#endif
#if ((XLCD_RS_PIN ^ 0x17) == 0)
#define XLCD_RSPIN   PORTBbits.RB7
#define XLCD_RSPIN_TRIS  TRISBbits.TRISB7
#endif

#if ((XLCD_RS_PIN ^ 0x20) == 0)
#define XLCD_RSPIN   PORTCbits.RC0
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC0
#endif
#if ((XLCD_RS_PIN ^ 0x21) == 0)
#define XLCD_RSPIN   PORTCbits.RC1
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC1
#endif
#if ((XLCD_RS_PIN ^ 0x22) == 0)
#define XLCD_RSPIN   PORTCbits.RC2
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC2
#endif
#if ((XLCD_RS_PIN ^ 0x23) == 0)
#define XLCD_RSPIN   PORTCbits.RC3
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC3
#endif
#if ((XLCD_RS_PIN ^ 0x24) == 0)
#define XLCD_RSPIN   PORTCbits.RC4
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC4
#endif
#if ((XLCD_RS_PIN ^ 0x25) == 0)
#define XLCD_RSPIN   PORTCbits.RC5
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC5
#endif
#if ((XLCD_RS_PIN ^ 0x26) == 0)
#define XLCD_RSPIN   PORTCbits.RC6
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC6
#endif
#if ((XLCD_RS_PIN ^ 0x27) == 0)
#define XLCD_RSPIN   PORTCbits.RC7
#define XLCD_RSPIN_TRIS  TRISCbits.TRISC7
#endif

#if ((XLCD_RS_PIN ^ 0x30) == 0)
#define XLCD_RSPIN   PORTDbits.RB0
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD0
#endif
#if ((XLCD_RS_PIN ^ 0x31) == 0)
#define XLCD_RSPIN   PORTDbits.RD1
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD1
#endif
#if ((XLCD_RS_PIN ^ 0x32) == 0)
#define XLCD_RSPIN   PORTDbits.RD2
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD2
#endif
#if ((XLCD_RS_PIN ^ 0x33) == 0)
#define XLCD_RSPIN   PORTDbits.RD3
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD3
#endif
#if ((XLCD_RS_PIN ^ 0x34) == 0)
#define XLCD_RSPIN   PORTDbits.RD4
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD4
#endif
#if ((XLCD_RS_PIN ^ 0x35) == 0)
#define XLCD_RSPIN   PORTDbits.RD5
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD5
#endif
#if ((XLCD_RS_PIN ^ 0x36) == 0)
#define XLCD_RSPIN   PORTDbits.RD6
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD6
#endif
#if ((XLCD_RS_PIN ^ 0x37) == 0)
#define XLCD_RSPIN   PORTDbits.RD7
#define XLCD_RSPIN_TRIS  TRISDbits.TRISD7
#endif

#if ((XLCD_RS_PIN ^ 0x40) == 0)
#define XLCD_RSPIN   PORTEbits.RE0
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE0
#endif
#if ((XLCD_RS_PIN ^ 0x41) == 0)
#define XLCD_RSPIN   PORTEbits.RE1
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE1
#endif
#if ((XLCD_RS_PIN ^ 0x42) == 0)
#define XLCD_RSPIN   PORTEbits.RE2
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE2
#endif
#if ((XLCD_RS_PIN ^ 0x43) == 0)
#define XLCD_RSPIN   PORTEbits.RE3
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE3
#endif
#if ((XLCD_RS_PIN ^ 0x44) == 0)
#define XLCD_RSPIN   PORTEbits.RE4
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE4
#endif
#if ((XLCD_RS_PIN ^ 0x45) == 0)
#define XLCD_RSPIN   PORTEbits.RE5
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE5
#endif
#if ((XLCD_RS_PIN ^ 0x46) == 0)
#define XLCD_RSPIN   PORTEbits.RE6
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE6
#endif
#if ((XLCD_RS_PIN ^ 0x47) == 0)
#define XLCD_RSPIN   PORTEbits.RE7
#define XLCD_RSPIN_TRIS  TRISEbits.TRISE7
#endif

#if ((XLCD_RS_PIN ^ 0x50) == 0)
#define XLCD_RSPIN   PORTFbits.RF0
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF0
#endif
#if ((XLCD_RS_PIN ^ 0x51) == 0)
#define XLCD_RSPIN   PORTFbits.RF1
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF1
#endif
#if ((XLCD_RS_PIN ^ 0x52) == 0)
#define XLCD_RSPIN   PORTFbits.RF2
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF2
#endif
#if ((XLCD_RS_PIN ^ 0x53) == 0)
#define XLCD_RSPIN   PORTFbits.RF3
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF3
#endif
#if ((XLCD_RS_PIN ^ 0x54) == 0)
#define XLCD_RSPIN   PORTFbits.RF4
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF4
#endif
#if ((XLCD_RS_PIN ^ 0x55) == 0)
#define XLCD_RSPIN   PORTFbits.RF5
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF5
#endif
#if ((XLCD_RS_PIN ^ 0x56) == 0)
#define XLCD_RSPIN   PORTFbits.RF6
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF6
#endif
#if ((XLCD_RS_PIN ^ 0x57) == 0)
#define XLCD_RSPIN   PORTFbits.RF7
#define XLCD_RSPIN_TRIS  TRISFbits.TRISF7
#endif

#if ((XLCD_RS_PIN ^ 0x60) == 0)
#define XLCD_RSPIN   PORTGbits.RG0
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG0
#endif
#if ((XLCD_RS_PIN ^ 0x61) == 0)
#define XLCD_RSPIN   PORTGbits.RG1
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG1
#endif
#if ((XLCD_RS_PIN ^ 0x62) == 0)
#define XLCD_RSPIN   PORTGbits.RG2
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG2
#endif
#if ((XLCD_RS_PIN ^ 0x63) == 0)
#define XLCD_RSPIN   PORTGbits.RG3
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG3
#endif
#if ((XLCD_RS_PIN ^ 0x64) == 0)
#define XLCD_RSPIN   PORTGbits.RG4
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG4
#endif
#if ((XLCD_RS_PIN ^ 0x65) == 0)
#define XLCD_RSPIN   PORTGbits.RG5
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG5
#endif
#if ((XLCD_RS_PIN ^ 0x66) == 0)
#define XLCD_RSPIN   PORTGbits.RG6
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG6
#endif
#if ((XLCD_RS_PIN ^ 0x67) == 0)
#define XLCD_RSPIN   PORTGbits.RG7
#define XLCD_RSPIN_TRIS  TRISGbits.TRISG7
#endif

#if ((XLCD_RS_PIN ^ 0x70) == 0)
#define XLCD_RSPIN   PORTHbits.RH0
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH0
#endif
#if ((XLCD_RS_PIN ^ 0x71) == 0)
#define XLCD_RSPIN   PORTHbits.RH1
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH1
#endif
#if ((XLCD_RS_PIN ^ 0x72) == 0)
#define XLCD_RSPIN   PORTHbits.RH2
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH2
#endif
#if ((XLCD_RS_PIN ^ 0x73) == 0)
#define XLCD_RSPIN   PORTHbits.RH3
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH3
#endif
#if ((XLCD_RS_PIN ^ 0x74) == 0)
#define XLCD_RSPIN   PORTHbits.RH4
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH4
#endif
#if ((XLCD_RS_PIN ^ 0x75) == 0)
#define XLCD_RSPIN   PORTHbits.RH5
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH5
#endif
#if ((XLCD_RS_PIN ^ 0x76) == 0)
#define XLCD_RSPIN   PORTHbits.RH6
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH6
#endif
#if ((XLCD_RS_PIN ^ 0x77) == 0)
#define XLCD_RSPIN   PORTHbits.RH7
#define XLCD_RSPIN_TRIS  TRISHbits.TRISH7
#endif

#if ((XLCD_RS_PIN ^ 0x80) == 0)
#define XLCD_RSPIN   PORTJbits.RJ0
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ0
#endif
#if ((XLCD_RS_PIN ^ 0x81) == 0)
#define XLCD_RSPIN   PORTJbits.RJ1
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ1
#endif
#if ((XLCD_RS_PIN ^ 0x82) == 0)
#define XLCD_RSPIN   PORTJbits.RJ2
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ2
#endif
#if ((XLCD_RS_PIN ^ 0x83) == 0)
#define XLCD_RSPIN   PORTJbits.RJ3
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ3
#endif
#if ((XLCD_RS_PIN ^ 0x84) == 0)
#define XLCD_RSPIN   PORTJbits.RJ4
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ4
#endif
#if ((XLCD_RS_PIN ^ 0x85) == 0)
#define XLCD_RSPIN   PORTJbits.RJ5
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ5
#endif
#if ((XLCD_RS_PIN ^ 0x86) == 0)
#define XLCD_RSPIN   PORTJbits.RJ6
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ6
#endif
#if ((XLCD_RS_PIN ^ 0x87) == 0)
#define XLCD_RSPIN   PORTJbits.RJ7
#define XLCD_RSPIN_TRIS  TRISJbits.TRISJ7
#endif

//////////////////////////////////////////////////////////////////////////////

//Enable Pin
//////////////////////////////////////////////////////////////////////////////
#if ((XLCD_EN_PIN ^ 0x00) == 0)
#define XLCD_ENPIN   PORTAbits.RA0
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA0
#endif
#if ((XLCD_EN_PIN ^ 0x01) == 0)
#define XLCD_ENPIN   PORTAbits.RA1
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA1
#endif
#if ((XLCD_EN_PIN ^ 0x02) == 0)
#define XLCD_ENPIN   PORTAbits.RA2
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA2
#endif
#if ((XLCD_EN_PIN ^ 0x03) == 0)
#define XLCD_ENPIN   PORTAbits.RA3
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA3
#endif
#if ((XLCD_EN_PIN ^ 0x04) == 0)
#define XLCD_ENPIN   PORTAbits.RA4
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA4
#endif
#if ((XLCD_EN_PIN ^ 0x05) == 0)
#define XLCD_ENPIN   PORTAbits.RA5
#define XLCD_ENPIN_TRIS  TRISAbits.TRISA5
#endif

#if ((XLCD_EN_PIN ^ 0x10) == 0)
#define XLCD_ENPIN   PORTBbits.RB0
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB0
#endif
#if ((XLCD_EN_PIN ^ 0x11) == 0)
#define XLCD_ENPIN   PORTBbits.RB1
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB1
#endif
#if ((XLCD_EN_PIN ^ 0x12) == 0)
#define XLCD_ENPIN   PORTBbits.RB2
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB2
#endif
#if ((XLCD_EN_PIN ^ 0x13) == 0)
#define XLCD_ENPIN   PORTBbits.RB3
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB3
#endif
#if ((XLCD_EN_PIN ^ 0x14) == 0)
#define XLCD_ENPIN   PORTBbits.RB4
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB4
#endif
#if ((XLCD_EN_PIN ^ 0x15) == 0)
#define XLCD_ENPIN   PORTBbits.RB5
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB5
#endif
#if ((XLCD_EN_PIN ^ 0x16) == 0)
#define XLCD_ENPIN   PORTBbits.RB6
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB6
#endif
#if ((XLCD_EN_PIN ^ 0x17) == 0)
#define XLCD_ENPIN   PORTBbits.RB7
#define XLCD_ENPIN_TRIS  TRISBbits.TRISB7
#endif

#if ((XLCD_EN_PIN ^ 0x20) == 0)
#define XLCD_ENPIN   PORTCbits.RC0
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC0
#endif
#if ((XLCD_EN_PIN ^ 0x21) == 0)
#define XLCD_ENPIN   PORTCbits.RC1
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC1
#endif
#if ((XLCD_EN_PIN ^ 0x22) == 0)
#define XLCD_ENPIN   PORTCbits.RC2
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC2
#endif
#if ((XLCD_EN_PIN ^ 0x23) == 0)
#define XLCD_ENPIN   PORTCbits.RC3
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC3
#endif
#if ((XLCD_EN_PIN ^ 0x24) == 0)
#define XLCD_ENPIN   PORTCbits.RC4
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC4
#endif
#if ((XLCD_EN_PIN ^ 0x25) == 0)
#define XLCD_ENPIN   PORTCbits.RC5
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC5
#endif
#if ((XLCD_EN_PIN ^ 0x26) == 0)
#define XLCD_ENPIN   PORTCbits.RC6
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC6
#endif
#if ((XLCD_EN_PIN ^ 0x27) == 0)
#define XLCD_ENPIN   PORTCbits.RC7
#define XLCD_ENPIN_TRIS  TRISCbits.TRISC7
#endif

#if ((XLCD_EN_PIN ^ 0x30) == 0)
#define XLCD_ENPIN   PORTDbits.RB0
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD0
#endif
#if ((XLCD_EN_PIN ^ 0x31) == 0)
#define XLCD_ENPIN   PORTDbits.RD1
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD1
#endif
#if ((XLCD_EN_PIN ^ 0x32) == 0)
#define XLCD_ENPIN   PORTDbits.RD2
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD2
#endif
#if ((XLCD_EN_PIN ^ 0x33) == 0)
#define XLCD_ENPIN   PORTDbits.RD3
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD3
#endif
#if ((XLCD_EN_PIN ^ 0x34) == 0)
#define XLCD_ENPIN   PORTDbits.RD4
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD4
#endif
#if ((XLCD_EN_PIN ^ 0x35) == 0)
#define XLCD_ENPIN   PORTDbits.RD5
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD5
#endif
#if ((XLCD_EN_PIN ^ 0x36) == 0)
#define XLCD_ENPIN   PORTDbits.RD6
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD6
#endif
#if ((XLCD_EN_PIN ^ 0x37) == 0)
#define XLCD_ENPIN   PORTDbits.RD7
#define XLCD_ENPIN_TRIS  TRISDbits.TRISD7
#endif

#if ((XLCD_EN_PIN ^ 0x40) == 0)
#define XLCD_ENPIN   PORTEbits.RE0
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE0
#endif
#if ((XLCD_EN_PIN ^ 0x41) == 0)
#define XLCD_ENPIN   PORTEbits.RE1
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE1
#endif
#if ((XLCD_EN_PIN ^ 0x42) == 0)
#define XLCD_ENPIN   PORTEbits.RE2
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE2
#endif
#if ((XLCD_EN_PIN ^ 0x43) == 0)
#define XLCD_ENPIN   PORTEbits.RE3
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE3
#endif
#if ((XLCD_EN_PIN ^ 0x44) == 0)
#define XLCD_ENPIN   PORTEbits.RE4
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE4
#endif
#if ((XLCD_EN_PIN ^ 0x45) == 0)
#define XLCD_ENPIN   PORTEbits.RE5
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE5
#endif
#if ((XLCD_EN_PIN ^ 0x46) == 0)
#define XLCD_ENPIN   PORTEbits.RE6
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE6
#endif
#if ((XLCD_EN_PIN ^ 0x47) == 0)
#define XLCD_ENPIN   PORTEbits.RE7
#define XLCD_ENPIN_TRIS  TRISEbits.TRISE7
#endif

#if ((XLCD_EN_PIN ^ 0x50) == 0)
#define XLCD_ENPIN   PORTFbits.RF0
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF0
#endif
#if ((XLCD_EN_PIN ^ 0x51) == 0)
#define XLCD_ENPIN   PORTFbits.RF1
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF1
#endif
#if ((XLCD_EN_PIN ^ 0x52) == 0)
#define XLCD_ENPIN   PORTFbits.RF2
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF2
#endif
#if ((XLCD_EN_PIN ^ 0x53) == 0)
#define XLCD_ENPIN   PORTFbits.RF3
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF3
#endif
#if ((XLCD_EN_PIN ^ 0x54) == 0)
#define XLCD_ENPIN   PORTFbits.RF4
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF4
#endif
#if ((XLCD_EN_PIN ^ 0x55) == 0)
#define XLCD_ENPIN   PORTFbits.RF5
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF5
#endif
#if ((XLCD_EN_PIN ^ 0x56) == 0)
#define XLCD_ENPIN   PORTFbits.RF6
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF6
#endif
#if ((XLCD_EN_PIN ^ 0x57) == 0)
#define XLCD_ENPIN   PORTFbits.RF7
#define XLCD_ENPIN_TRIS  TRISFbits.TRISF7
#endif

#if ((XLCD_EN_PIN ^ 0x60) == 0)
#define XLCD_ENPIN   PORTGbits.RG0
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG0
#endif
#if ((XLCD_EN_PIN ^ 0x61) == 0)
#define XLCD_ENPIN   PORTGbits.RG1
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG1
#endif
#if ((XLCD_EN_PIN ^ 0x62) == 0)
#define XLCD_ENPIN   PORTGbits.RG2
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG2
#endif
#if ((XLCD_EN_PIN ^ 0x63) == 0)
#define XLCD_ENPIN   PORTGbits.RG3
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG3
#endif
#if ((XLCD_EN_PIN ^ 0x64) == 0)
#define XLCD_ENPIN   PORTGbits.RG4
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG4
#endif
#if ((XLCD_EN_PIN ^ 0x65) == 0)
#define XLCD_ENPIN   PORTGbits.RG5
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG5
#endif
#if ((XLCD_EN_PIN ^ 0x66) == 0)
#define XLCD_ENPIN   PORTGbits.RG6
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG6
#endif
#if ((XLCD_EN_PIN ^ 0x67) == 0)
#define XLCD_ENPIN   PORTGbits.RG7
#define XLCD_ENPIN_TRIS  TRISGbits.TRISG7
#endif

#if ((XLCD_EN_PIN ^ 0x70) == 0)
#define XLCD_ENPIN   PORTHbits.RH0
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH0
#endif
#if ((XLCD_EN_PIN ^ 0x71) == 0)
#define XLCD_ENPIN   PORTHbits.RH1
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH1
#endif
#if ((XLCD_EN_PIN ^ 0x72) == 0)
#define XLCD_ENPIN   PORTHbits.RH2
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH2
#endif
#if ((XLCD_EN_PIN ^ 0x73) == 0)
#define XLCD_ENPIN   PORTHbits.RH3
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH3
#endif
#if ((XLCD_EN_PIN ^ 0x74) == 0)
#define XLCD_ENPIN   PORTHbits.RH4
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH4
#endif
#if ((XLCD_EN_PIN ^ 0x75) == 0)
#define XLCD_ENPIN   PORTHbits.RH5
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH5
#endif
#if ((XLCD_EN_PIN ^ 0x76) == 0)
#define XLCD_ENPIN   PORTHbits.RH6
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH6
#endif
#if ((XLCD_EN_PIN ^ 0x77) == 0)
#define XLCD_ENPIN   PORTHbits.RH7
#define XLCD_ENPIN_TRIS  TRISHbits.TRISH7
#endif

#if ((XLCD_EN_PIN ^ 0x80) == 0)
#define XLCD_ENPIN   PORTJbits.RJ0
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ0
#endif
#if ((XLCD_EN_PIN ^ 0x81) == 0)
#define XLCD_ENPIN   PORTJbits.RJ1
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ1
#endif
#if ((XLCD_EN_PIN ^ 0x82) == 0)
#define XLCD_ENPIN   PORTJbits.RJ2
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ2
#endif
#if ((XLCD_EN_PIN ^ 0x83) == 0)
#define XLCD_ENPIN   PORTJbits.RJ3
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ3
#endif
#if ((XLCD_EN_PIN ^ 0x84) == 0)
#define XLCD_ENPIN   PORTJbits.RJ4
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ4
#endif
#if ((XLCD_EN_PIN ^ 0x85) == 0)
#define XLCD_ENPIN   PORTJbits.RJ5
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ5
#endif
#if ((XLCD_EN_PIN ^ 0x86) == 0)
#define XLCD_ENPIN   PORTJbits.RJ6
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ6
#endif
#if ((XLCD_EN_PIN ^ 0x87) == 0)
#define XLCD_ENPIN   PORTJbits.RJ7
#define XLCD_ENPIN_TRIS  TRISJbits.TRISJ7
#endif






void XLCDInit(void);                                //to initialise the LCD
void XLCDPut(char data);                            //to put dtat to be displayed
void XLCDPutRamString(char *string);                //to display data string in RAM
void XLCDPutRomString(rom char *string);            //to display data stringin ROM
char XLCDIsBusy(void);                              //to check Busy flag
void XLCDCommand(unsigned char cmd);                //to send commands to LCD           
unsigned char XLCDGetAddr(void);
char XLCDGet(void);

#define XLCDL1home()    			 XLCDCommand(0x80)
#define XLCDL2home()    			 XLCDCommand(0xC0)
#define XLCDClear()    				 XLCDCommand(0x01)
#define XLCDReturnHome()			 XLCDCommand(0x02)
#define XLCDCursorOnBlinkOn()        XLCDCommand(0x0F)	//the user may refer the LCD data sheet
#define XLCDCursorOnBlinkOff()       XLCDCommand(0x0E)	//and generate commands like this
#define XLCDDisplayOnCursorOff()     XLCDCommand(0x0C)
#define XLCDDisplayOff()             XLCDCommand(0x08)
#define XLCDCursorMoveLeft()         XLCDCommand(0x10)
#define XLCDCursorMoveRight()        XLCDCommand(0x14)
#define XLCDDisplayMoveLeft()        XLCDCommand(0x18)
#define XLCDDisplayMoveRight()       XLCDCommand(0x1C)

void XLCDDelay15ms(void);
void XLCDDelay4ms(void);
void XLCDDelay100us(void);
void XLCD_Delay500ns(void);
void XLCDDelay(void);

#endif
