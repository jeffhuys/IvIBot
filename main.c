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

extern void Task_Usart(void) ;

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
    PORTBbits.RB0 = 0;
    for (;;) {
        PORTBbits.RB0 = ~PORTBbits.RB0;
        if (PORTAbits.RA4 == 0) XLCDClear();
        OS_Delay(300);
        OS_Yield();
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
int started = 0;

int deltaLR = 0;
int deltaPower = 0;
int leftPower = 130;
int rightPower = 130;
char lastTurn = 'x';

int iviType = 2;

int trackLostTimer = 0;

void Task_Run(void) {
    OS_Delay(100);

    TRISB = 0; // Port is output

    //LeftPWM(leftPower, 0);
    //RightPWM(rightPower, 0);

    for (;;) {
        OS_Delay(50);

        leftIR = getAD1();
        frontIR = getAD2();
        rightIR = getAD3();

//        XLCDL2home(); // home but no cursor
//        PrintbyteToHex(leftIR);
//        XLCDPut(':');
//        PrintbyteToHex(frontIR);
//        XLCDPut(':');
//        PrintbyteToHex(rightIR);
//        XLCDPut(':');

        deltaLR = leftIR - rightIR;

        if (frontIR < 520) {
            LeftPWM(0, 0);
            RightPWM(0, 0);
        } else {
            if (leftIR > rightIR - 20 && leftIR < rightIR + 20 && rightIR > leftIR - 20 && rightIR < leftIR + 20) {
                // Track lost (or straight)
                trackLostTimer++;

                if (trackLostTimer > 20) {
                    XLCDPut('L');
                    if (lastTurn != 'x') {
                        if (lastTurn == 'r') {
                            // Turn right HARD
                            LeftPWM(iviType*130, 0);
                            RightPWM(iviType*40 + (trackLostTimer / 10), 0);
                        }
                        if (lastTurn == 'l') {
                            // Turn left HARD
                            LeftPWM(iviType*40 + (trackLostTimer / 10), 0);
                            RightPWM(iviType*130, 0);
                        }
                    }
                }
            } else {
                XLCDPut('N');

                if(started == 1)
                {
                    if (leftIR > rightIR + 10) {
                        // Turn left
                        LeftPWM(iviType*60, 0);
                        RightPWM(iviType*100, 0);
                        lastTurn = 'l';
                        trackLostTimer = 0;
                    }
                    if (rightIR > leftIR + 10) {
                        // Turn right
                        LeftPWM(iviType*100, 0);
                        RightPWM(iviType*60, 0);
                        lastTurn = 'r';
                        trackLostTimer = 0;
                    }

                }
            }

        }
        XLCDPut(lastTurn);

        OS_Yield();
    }
}

// BlueGiga Wt12 commands, wiimote connection
char command[] = "CALL 00:23:cc:9c:fb:dd 13 l2cap\r"; // Connect to specified wiimote
//char command[] = "CALL 00:23:cc:9d:19:41 13 l2cap\r"; // Connect to specified wiimote
//char command[] = "PING 00:1c:be:25:b0:55\r";
char cresult[]  = "CALL 0\rCONNECT 0 L2CAP 19\r" ;
char reset[] = "\r\nreset\r\n";   // In commandmode reset modem
char plus[] = "+++";          // If connected return to commandmode
char at[] = "AT\r" ;
char rat[] = "OK\r" ;
char nu[] = "\000" ;

int sendAndExpect(char *command, char *result, int echo) ;

void Task_Wiimote(void) {
	int stat = 0 ;
	OS_Delay(1500) ;
	XLCDClear() ;
	if ( sendAndExpect(command, nu , 0 ) == 0 ) {
	} ;
	while (1) {
		OS_Yield() ;
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

void pressedA()
{
    if(started == 0)
    {
        started = 1;
        XLCDPut('R');
    }
    else
    {
        LeftPWM(0, 0);
        RightPWM(0, 0);
        started = 0;
        XLCDPut('S');
    }
}

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
    OS_Task_Create(1, Task_Hartbeat); // Show I am alive (called by scheduler)//
    OS_Task_Create(1, Task_Run); // Run me through the maze (called by scheduler)//

    OS_Task_Create(2, Task_Usart); // BT Connection
    OS_Task_Create(2, Task_Wiimote); // BT Connection

    OS_Run(); // Run scheduler
}
