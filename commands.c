#define __P18F4550

#include <p18f4550.h>
#include <string.h>
#include <stdlib.h>

#include "includes.h"
#include "commands.h"
#include "myadc.h"
#include "RotatingQueue.h"

// Firts bluetooth version
#define REP_PROTOCOLVERSION 5

extern unsigned long counter0;
extern unsigned long counter1;
extern unsigned long SystemTime;
extern int emergencyStop;

extern unsigned char CommandData[50];
extern unsigned char ReportData[64];
extern unsigned int  CommandLength;



extern BYTE stored_CCPR1L ;
extern BYTE stored_CCPR2L ;

// Prototying should be extremly complete. 
void putcUSART(char c) ;  

extern void pressedA(void);

extern void setLed(int,int);
extern void setLed1(int);
extern void setLed2(int);
extern void setLed3(int);
extern void setLed4(int);
extern void setLed5(int);
extern void setLed6(int);
extern void setLed7(int);
extern void setLed8(int);
extern void LedBar(void) ;

extern void XLCDPutRamString(char *string);

void setLed(int ldnr, int state) {
	BYTE bitl = 0x01 ;
	bitl <<= ldnr ;
	if ( state ) PORTB |= bitl ;
	else PORTB &= ~bitl ;
}

/******************************************************************************
 * Function:        void procesCommand(void)
 *
 * PreCondition:    Filled CommandData array and CommandLength both global
 *
 * Input:           Through  globals only (not so nice)
 *
 * Output:          Controls 18F4550 regs and PWM timer ints
 *
 * Side Effects:    Use with caution, side effect may control motors
 *
 * Note:            Simple protocol, new does not look like the USB version
 *                   
 *****************************************************************************/
int count = 0 ;
int temper = 0;

void procesCommand(void) {
    int i = 0;


    PORTD = ++count ; 

    // Commandstrings starts with "AT" else  invalid string than skip whole
	if ( CommandData[i] == '#') {
		i+= 1;
	}
	else return ;

    XLCDClear();
    XLCDPutRamString((char*)CommandData);

    while( i < CommandLength ) {
        switch (CommandData[i++]) {
			case 'n':  // Noise on
//				BeepOn() ;
//				PORTB = 0x55 ;
				break;
			case 'N':  // Noise off
//				BeepOff() ;
				break;
            case 'L':
                XLCDPut('L');
                //pressedA();

                setLed(CommandData[i] - '0', CommandData[i + 1]- '0');

                i += 2;
                break;
            case 'b': // Sets data on port
                setPortBData(CommandData[i]);
                i += 1;
                break;
            case 'B': // Set B port direction
                setPortBIO(CommandData[i]);
                i += 1;
                break;
            case 'd':
                setPortDData(CommandData[i]);
                i += 1;
                break;
            case 'D':
                setPortDIO(CommandData[i]);
                i += 1;
                break;
            case 'e':   // We should take some care here EC ports contain PWM en direction bits.
                setPortECData(CommandData[i]);
                i += 1;
                break;
            case 'I': //Instruction List
                clearQueue();
                XLCDClear();
                XLCDL1home();

//                for (temper=0;temper<17;temper++){
                while(CommandData[i]!= 'I'){
                    XLCDPut(CommandData[i]);
                    push((int) CommandData[i]);
                    i += 1;   
                }
                i +=1;
                             
                break;

            case 'S':
                XLCDClear();
                XLCDL1home();
                XLCDPutRomString("STAHP! =(");

                //Emergency STHAP!
                emergencyStop = 1;
                break;

//            case 'r':
//                stored_CCPR1L = CommandData[i];
//                setCCPR1L_REG(CommandData[i]);
//                //stored_CCPR1L = 140;
//                //setCCPR1L_REG(140);
//                i += 1;
//                break;
//            case 's':
//                stored_CCPR2L = CommandData[i];
//                setCCPR2L_REG(CommandData[i]);
//                //stored_CCPR2L = 140;
//                //setCCPR2L_REG(140);
//                i += 1;
//                break;
            default:
              		/* nop */ ;
        }
    }
}
// the ivibot report protocol (same as USB version probebly obsolete) 
enum REPFIELDS {
/*0*/	  REP_PORTB = 0 , REP_PORTD, REP_PORTEC, REP_AD0, REP_AD1, REP_AD2,
/*6*/     REP_AD3, REP_PR2, REP_T2CON, REP_CCP1, REP_CCP2, REP_CCPR1L,
/*12*/    REP_CCPR2L, REP_PROTOCOL, REP_TRISB, REP_TRISD, REP_TRISEC,
/*17*/    REP_SYSTEMMSTIMERL, REP_SYSTEMMSTIMERML, REP_SYSTEMMSTIMERMH, REP_SYSTEMMSTIMERH,      // SYSTEM BOOT TIME IN 0.1 MS
/*21*/    REP_COUNTER0L,      REP_COUNTER0ML,      REP_COUNTER0MH,      REP_COUNTER0H,
/*25*/    REP_COUNTER1L,      REP_COUNTER1ML,      REP_COUNTER1MH,      REP_COUNTER1H
};

/******************************************************************************
 * Function:        void sendReport(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          Send report to bleutooth client
 *
 * Side Effects:    Filed ReportData array not used by others
 *
 * Note:            To reduce space get rid of the ReportData array
 *                  (it is probably better).
 *****************************************************************************/
void sendReport(void) {
    int i = 0;
    BYTE *p;
    //report back the state of the ivibot register values
    ReportData[REP_PORTB] = PORTB; //0
    ReportData[REP_PORTD] = PORTD; //1
    ReportData[REP_PORTEC] = getPortEC(); //2

    ReportData[REP_AD0] = getAD0(); //3
    ReportData[REP_AD1] = getAD1(); //4
    ReportData[REP_AD2] = getAD2(); //5
    ReportData[REP_AD3] = getAD3(); //6

    ReportData[REP_PR2] = PR2; //7
    ReportData[REP_T2CON] = T2CON; //8
    ReportData[REP_CCP1] = CCP1CON; //9
    ReportData[REP_CCP2] = CCP2CON; //10
    ReportData[REP_CCPR1L] = stored_CCPR1L; //11 CCPR1L stored, it is not allowed to read the counting REG;
    ReportData[REP_CCPR2L] = stored_CCPR2L; //12 see CCPR1L above;

    ReportData[REP_PROTOCOL] = REP_PROTOCOLVERSION; //13
    ReportData[REP_TRISB] = TRISB; //14
    ReportData[REP_TRISD] = TRISD; //15

    p = (BYTE *) & SystemTime;
    ReportData[REP_SYSTEMMSTIMERL] = p[0]; // 16 Byte 0
    ReportData[REP_SYSTEMMSTIMERML] = p[1]; // 17 ,,  1
    ReportData[REP_SYSTEMMSTIMERMH] = p[2]; // 18 ,,  2
    ReportData[REP_SYSTEMMSTIMERH] = p[3]; // 19 ,,  3

    p = (BYTE *) & counter0;
    ReportData[REP_COUNTER0L] = p[0]; // 20 Byte 0
    ReportData[REP_COUNTER0ML] = p[1]; // 21 ,,  1
    ReportData[REP_COUNTER0MH] = p[2]; // 22 ,,  2
    ReportData[REP_COUNTER0H] = p[3]; // 23 ,,  3

    p = (BYTE *) & counter1;
    ReportData[REP_COUNTER1L] = p[0]; // 24 Byte 0
    ReportData[REP_COUNTER1ML] = p[1]; // 25 ,,  1
    ReportData[REP_COUNTER1MH] = p[2]; // 26 ,,  2
    ReportData[REP_COUNTER1H] = p[3]; // 27 ,,  3

    // Start with ascii ESC followed by 'AT' so the JAVA counterpart can sync
    putcUSART((char) 27);
    putcUSART((char) 'A');
    putcUSART((char) 'T');
	
    for (i = 0; i < 32; i++) { // Java bluetooth client expecte 32 BYTES only 28 used.
        //putcUSART('B') ;  // debug
        //putcUSART((char) i + '0');
        putcUSART(ReportData[i]);
    }
    putcUSART((char) 13); // Send a single newline, end of this report transmission.

}
