#include "task_run.h"

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

void Task_Run(void) {
    OS_Delay(100);

    //TRISB = 0; // Port is output

    //LeftPWM(leftPower, 0);
    //RightPWM(rightPower, 0);

    for (;;) {
        PORTBbits.RB5 = 0;
        OS_Delay(2000);
        PORTBbits.RB5 = 0;

        leftIR = getAD1();
        frontIR = getAD2();
        rightIR = getAD3();

        XLCDL2home(); // home but no cursor
        PrintbyteToHex(leftIR);
        XLCDPut(':');
        PrintbyteToHex(frontIR);
        XLCDPut(':');
        PrintbyteToHex(rightIR);
        XLCDPut(':');

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