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

#include "includes.h"

#include "task_display.h"
#include "task_heartbeat.h"
#include "task_server.h"
#include "task_run.h"

#include "RotatingQueue.h"

//******************************************************************************
//  Tasks
//******************************************************************************
extern void Task_Display(void);
extern void Task_Heartbeat(void);
extern void Task_Server(void);
extern void Task_Run(void);

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
//  Main
//******************************************************************************

void main(void) {
    
    OS_Init(); // OS System init

    ADC_init(); // Should be done first
    PWM_init(); // Beware pwm ports go together with ANALOG in

    setPortBIO(0x04); // Set port B in output mode
    setPortDIO(0x00); // Set port D in output mode

    XLCDInit(); // initialize the LCD module
    XLCDClear();

    // Push een kleine lijst
    //push(2);
    //push(1);
    //push(3);

    OS_Task_Create(0, Task_Server); // BT Connection
    OS_Task_Create(1, Task_Hartbeat); // Show I am alive (called by scheduler)//
    OS_Task_Create(1, Task_Run); // Run me through the maze (called by scheduler)//
    OS_Task_Create(2, Task_Display); // be called by scheduler

    OS_Run(); // Run scheduler

}
