//******************************************************************************
//
// Filename :       main.c
// Dependencies:    all
// Processor:       PIC18
// Complier:        MCC18 v3.37 or higher
// Company:         HVA.
// Auther:	    Ferry
// Date:            2012-02-20
// Version:         1.0
//
//******************************************************************************

#include <p18f4550.h>
#include <osa.h>
#include "xlcd/xlcd.h"
#include "pwm/pwm.h"
#include "usart/usart.h"
#include "myadc.h"


//
//------------------------------------------------------------------------------
//

char hexChar[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void PrintbyteToHex(int b) {
    char hn, ln, tn;
    tn = hexChar[(b >> 8) & 0x0f];
    hn = hexChar[(b >> 4) & 0x0f];
    ln = hexChar[b & 0x0f];
    XLCDPut('x');
    XLCDPut(tn);
    XLCDPut(hn);
    XLCDPut(ln);
}

//******************************************************************************
//  Tasks
//******************************************************************************
rom char *WelcomeLine1 = "- Running BOT - ";
rom char *WelcomeLine2 = "- Maze        - ";

OST_QUEUE queue;
OST_MSG buffer[10];

void Task_Display(void) {
    OST_MSG msg;
    char *str;

    XLCDInit(); // initialize the LCD module
    XLCDClear();
    XLCDPutRomString(WelcomeLine1); // Hello world
    XLCDL2home(); // home but no cursor
    XLCDPutRomString(WelcomeLine2);

    OS_Queue_Create(queue, buffer, 10);

    for (;;) {
        OS_Queue_Wait(queue, msg); // Wait for message and store it into msg
        str = msg;
        XLCDL1home(); // home but no cursor
        XLCDPutRomString((rom char*) str);

        OS_Queue_Wait(queue, msg); // Wait for message and store it into msg
        str = msg;
        XLCDL2home(); // home but no cursor
        XLCDPutRomString((rom char*) str);
    }
}

//---------testing os shedular on RB4-------------------------------------------

void Task_Hartbeat(void) {
    OS_Delay(100);
    TRISBbits.TRISB4 = 0; // Port is output
    PORTBbits.RB4 = 0;
    for (;;) {
        PORTBbits.RB4 = ~PORTBbits.RB4;
        if (PORTAbits.RA4 == 0) XLCDClear();
        OS_Delay(300);
    }
}

typedef int bool;

enum {
    false, true
};

int frontIR = 0;
int leftIR = 0;
int rightIR = 0;

bool trackLost;

int deltaLR = 0;
int deltaPower = 0;
int leftPower = 130;
int rightPower = 130;
char lastTurn = 'x';

int trackLostTimer = 0;

void Task_Run(void) {
    OS_Delay(100);

    TRISB = 0; // Port is output

    //LeftPWM(leftPower, 0);
    //RightPWM(rightPower, 0);

    for (;;) {
        OS_Delay(48);
        PORTBbits.RB0 = 1;
        PORTBbits.RB1 = 1;
        PORTBbits.RB2 = 1;
        OS_Delay(2);
        leftIR = getAD1();
        frontIR = getAD2();
        rightIR = getAD3();

        PORTBbits.RB0 = 0;
        PORTBbits.RB1 = 0;
        PORTBbits.RB2 = 0;

        XLCDL2home(); // home but no cursor
        //PrintbyteToHex(leftIR);
        //XLCDPut(':');
        //PrintbyteToHex(frontIR);
        //XLCDPut(':');
        //PrintbyteToHex(rightIR);
        //XLCDPut(':');

        deltaLR = leftIR - rightIR;

        if (frontIR < 520) {
            LeftPWM(0, 0);
            RightPWM(0, 0);
        } else {
            if (leftIR > rightIR - 20 && leftIR < rightIR + 20 && rightIR > leftIR - 20 && rightIR < leftIR + 20) {
                // Track lost (or straight)
                trackLostTimer++;

                if (trackLostTimer < 500) {
                    XLCDPut('L');
                    if (lastTurn != 'x') {
                        if (lastTurn == 'r') {
                            // Turn right HARD
                            LeftPWM(140, 0);
                            RightPWM(70, 0);
                        }
                        if (lastTurn == 'l') {
                            // Turn left HARD
                            LeftPWM(70, 0);
                            RightPWM(140, 0);
                        }
                    }
                }
            } else {
                XLCDPut('N');

                if (leftIR > rightIR + 10) {
                    // Turn left
                    LeftPWM(70, 0);
                    RightPWM(110, 0);
                    lastTurn = 'l';
                    trackLostTimer = 0;
                }
                if (rightIR > leftIR + 10) {
                    // Turn right
                    LeftPWM(110, 0);
                    RightPWM(70, 0);
                    lastTurn = 'r';
                    trackLostTimer = 0;
                }
            }

        }
        XLCDPut(lastTurn);
    }
}

//******************************************************************************
//** Reset vector mapping **
//******************************************************************************
extern void _startup(void); // See c018i.c in your C18 compiler dir
// Vector moved hid bootloader in place
#pragma code _RESET_INTERRUPT_VECTOR = 0x001000

void _reset(void) {
    _asm goto _startup _endasm
}
// end reset vector code
#pragma code

//******************************************************************************
//  main
//******************************************************************************

void main(void) {

    OS_Init(); // OS System init

    ADC_init(); // Should be done first
    PWM_init(); // Beware pwm ports go together with ANALOG in

    XLCDInit(); // initialize the LCD module
    XLCDClear();

    OS_Task_Create(1, Task_Display); // be called by scheduler
    OS_Task_Create(0, Task_Hartbeat); // Show I am alive (called by scheduler)//
    OS_Task_Create(0, Task_Run); // Run me through the maze (called by scheduler)//

    OS_Run(); // Run scheduler
}
