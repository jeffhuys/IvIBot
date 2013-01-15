#include "task_heartbeat.h"

void Task_Hartbeat(void) {
    OS_Delay(100);
    TRISBbits.TRISB4 = 0; // Port is output
    PORTBbits.RB0 = 0;
    for (;;) {
        PORTBbits.RB7 = ~PORTBbits.RB7;
        if (PORTAbits.RA4 == 0) XLCDClear();
        OS_Delay(5000);
    }
}
