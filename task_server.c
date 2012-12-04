#include "task_server.h"

unsigned char ReportData[64];
unsigned char CommandData[50];
unsigned int  CommandLength = 0 ;
unsigned char NextCharIn = 0;

unsigned long counter0;
unsigned long counter1;
unsigned long SystemTime;

extern void RightPWM(int pwmDuty, int threshold) ;
extern void LeftPWM(int pwmDuty, int threshold) ;

void procesCommand(void) ;
void sendReport(void) ;
void initTimer(void) ;

char c;

void Task_Server(void)
{
    PORTB=0x55 ;
    OS_Delay(2000) ;  // modem has to init
    initUSART();
    OS_Delay(2000) ;  // modem has to init
    PORTB= 0 ;

    //putStrUSART((char *)"reset\n") ;  // RESET modem
    OS_Delay(500) ;  // modem has to init

    CommandData[0] = 0;
    NextCharIn = 0;

    PORTB = 0 ;

    while(1) {
        int stuffed = 0; // Are we in a escape sequence?
        NextCharIn = 0; //

        while(1) {
            OS_Wait(PIR1bits.RCIF);
            c = RCREG ;
            PIR1bits.RCIF = 0;

//            if (stuffed == 0) {
//                if (c == '\\') { // entered escape sequense stage
//                    stuffed = 1;
//                    continue;
//                }
//                stuffed = 0; // Only one byte escaped

                if (c == 27) { // Recieved ascii ESC reset input buffer and start over
                    NextCharIn = 0;
                    continue;
                }
                if (c == 13 || c == 10) { // ascii NL or CR
                    CommandData[NextCharIn] = 0;
                    if (NextCharIn == 0) continue; // Recieved multiple NL or CR start over
                    else break; // we have a command break out while
                }
//            }

            CommandData[NextCharIn++] = c;
//            if (NextCharIn == 32) break; // Command should not be langer than 32 bytes
            //PORTB = c ; // small debug on leds.
        }

        CommandLength = NextCharIn; // Can do without, make NextChar in the target
        procesCommand();
        sendReport();
    }
}
