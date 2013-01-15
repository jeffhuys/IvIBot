#include "task_run.h"
#include "RotatingQueue.h"
#include "iviType.h"

typedef int bool;

enum {
    false, true
};

#define WAIT 1000000

unsigned long long i = 0;
int asdasd = 0;

int frontIR = 0;
int leftIR = 0;
int rightIR = 0;
int outerLeftIR = 0;
int outerRightIR = 0;

bool trackLost;
int emergencyStop = 0;
int started = 0;

int deltaLR = 0;
int deltaPower = 0;
int leftPower = 130;
int rightPower = 130;
char lastTurn = 'x';
int combined = 0;

int seesBlack = 0;
int sees = 0;

int iviType = 2;

int trackLostTimer = 0;

int nextCommand = 0;
int ignoreMarkers = 0;

int blackLower;


// Dit verandert per lichtomgeving...


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
    OS_Delay(200);

    //TRISB = 0; // Port is output

    //LeftPWM(leftPower, 0);
    //RightPWM(rightPower, 0);

    if(IVITYPE == 2) {
        blackLower = 600;
    } else {
        blackLower = 800;
    }
    //blackLower = 900;

    for (;;) {
        PORTBbits.RB5 = 0;
        OS_Delay(1500);
        PORTBbits.RB5 = 0;

        leftIR = getAD1();
        frontIR = getAD2();
        if(IVITYPE == 3) {
            rightIR = getAD8();
            outerLeftIR = getAD3();
            outerRightIR = getAD0() * 4;
        } else {
            rightIR = getAD3();
            outerLeftIR = getAD8();
            outerRightIR = getAD0();
        }
        
        

        combined = leftIR + rightIR;

        if (combined > 64 && combined < 96) {
            //sees = 1;
        } else {
            sees = 0;
        }

        // >250 hex = 592 dec
        
        XLCDL1home(); // home but no cursor
        XLCDPut('l');
        PrintbyteToHex(leftIR);

        XLCDPut('f');
        PrintbyteToHex(frontIR);

        XLCDPut('r');
        PrintbyteToHex(rightIR);

        XLCDL2home(); // home but no cursor
        XLCDPut('l');
        PrintbyteToHex(outerLeftIR);

        XLCDPut('f');
        PrintbyteToHex(frontIR);

        XLCDPut('r');
        PrintbyteToHex(outerRightIR);
         


        deltaLR = leftIR - rightIR;

        if (leftIR > blackLower && rightIR > blackLower && outerLeftIR > blackLower && outerRightIR > blackLower) {
            seesBlack = 1;
        } else {
            seesBlack = 0;
        }



        if (frontIR < 450 || sees == 1 || emergencyStop == 1 || isEmpty() == 1) {
            LeftPWM(0, 0);
            RightPWM(0, 0);

            OS_Delay(10000);
        } else {
            // Als de middelste twee de baan zien, rijden
            // 320-420

            // Outer left en right > 150 hex = 336

            // 80-96 bij elkaar = station

            if (seesBlack) {
                // TEMP
                // DONE: Haal dit in godsnaam weg voor de opleverdatum :DONE
                nextCommand = pop();

                XLCDPut(nextCommand);

                if(ignoreMarkers > 0) {
                    // Do nothing
                } else {
                    LeftPWM(0, 0);
                    RightPWM(0, 0);

                    OS_Delay(10000);

                    // We zien een indicator!
                    if (nextCommand != 0) {
                        switch (nextCommand) {
                            case '1':
                                // Left
                                LeftPWM(0, 0);
                                RightPWM(120, 0);
                                OS_Delay(25000 * IVITYPE);
                                break;
                            case '2':
                                // Right
                                LeftPWM(120, 0);
                                RightPWM(0, 0);
                                OS_Delay(25000 * IVITYPE);
                                break;
                            case '3':
                                // Forward
                                LeftPWM(120, 0);
                                RightPWM(124, 0);
                                OS_Delay(10000 * IVITYPE);
                                break;
                            default:
                                // Default
                                LeftPWM(80, 0);
                                RightPWM(80, 0);
                                OS_Delay(10000);
                                break;
                        }
                    }
                }
            }


            // blackLower - 400 * ivitype - 1
            // Dit zit er in zodat als de ivitype 2 is er 400 vanaf wordt gehaald
            if (outerLeftIR > blackLower - 200) {
                // Draai links
                LeftPWM(0, 0);
                RightPWM(120, 0);

                // Zet lastTurn naar links
                XLCDPut('L');
                lastTurn = 'L';
            } else if (outerRightIR > blackLower) {
                // Draai rechts
                LeftPWM(120, 0);
                RightPWM(0, 0);

                // Zet lastTurn naar rechts
                XLCDPut('R');
                lastTurn = 'R';
            } else {
                // Rijd rechtdoor
                LeftPWM(120, 0);
                RightPWM(124, 0);
            }
            
            if (!((leftIR > 832 && leftIR < 1056) || (rightIR > 832 && rightIR < 1056))) {
                // NO LINE! Search line.
                XLCDL2home(); // home but no cursor
                XLCDPut('N');
                XLCDPut('O');
                XLCDPut('L');

                // Turn towards last known line position.
                switch (lastTurn) {
                    case 'L':
                        LeftPWM(0, 0);
                        RightPWM(128, 0);
                        break;
                    case 'R':
                        LeftPWM(128, 0);
                        RightPWM(0, 0);
                        break;
                    case 'x':
                        LeftPWM(0, 0);
                        RightPWM(0, 0);
                        XLCDPut('!');
                        break;
                }

            }
            

            /*
            if(leftIR > 832 && leftIR < 1056 && rightIR > 832 && rightIR < 1056) {
                    LeftPWM(128, 0);
                    RightPWM(128, 0);
            } else {
                    LeftPWM(0, 0);
                    RightPWM(0, 0);
            }
             */
        }
        //Crossroads

        /*
        //            XLCDClear();
        //            XLCDL1home();
        //            XLCDPut('W');
        //            XLCDPut(peek());
        //            for(i=0;i<WAIT;i++);
        //XLCDPut(peek());
        //            if(false){

        if(isEmpty() == 0){//if OuterIR sensors see crossroad.
        //
        //                XLCDClear();
        //                XLCDL1home();
        //                XLCDPutRomString("NOT EMPTY");
        //                asdasd = pop();
        //                XLCDPut(asdasd);
        //                for(i=0;i<WAIT;i++);

            switch (pop()){
        //                switch (asdasd){
                case '1':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 1");
                    LeftPWM(iviType*40, 0);
                    RightPWM(iviType*130, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '2':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 2");
                    LeftPWM(iviType*63, 0);
                    RightPWM(iviType*130, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '3':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 3");
                    LeftPWM(iviType*85, 0);
                    RightPWM(iviType*130, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '4':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 4");
                    LeftPWM(iviType*108, 0);
                    RightPWM(iviType*130, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '5':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 5");
                    LeftPWM(iviType*130, 0);
                    RightPWM(iviType*130, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                 case '6':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 6");
                    LeftPWM(iviType*130, 0);
                    RightPWM(iviType*108, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '7':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 7");
                    LeftPWM(iviType*130, 0);
                    RightPWM(iviType*85, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '8':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 8");
                    LeftPWM(iviType*130, 0);
                    RightPWM(iviType*63, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '9':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Turn 9");
                    LeftPWM(iviType*130, 0);
                    RightPWM(iviType*40, 0);
                    for(i=0;i<WAIT;i++);
                    break;
                case '-1':
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Queue was empty");
                    for(i=0;i<WAIT;i++);
                    break;
                default:
                    XLCDClear();
                    XLCDL1home();
                    XLCDPutRomString("Wrong turn detected");
                    for(i=0;i<WAIT;i++);
                    break;
            }
            XLCDClear();
            XLCDL1home();
            XLCDPutRomString("- Running BOT - ");
        }
        //            else{
        //                XLCDClear();
        //                XLCDL1home();
        //                XLCDPutRomString("Queue Glitch");
        //                for(i=0;i<WAIT;i++);
        //            }

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
        //            LeftPWM(iviType*130, 0);
        //            RightPWM(iviType*130, 0);
    }
    XLCDPut(lastTurn);
         */

        OS_Yield();
    }
}
