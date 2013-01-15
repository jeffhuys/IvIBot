//******************************************************************************
//  
//  TUTOR3: Demonstration of delays in tasks (OS_Delay)
// 
//          (Demo-board with 16F887 from pickit2 used as a hardware)
//  
//******************************************************************************


#include <pic.h>
#include <osa.h>



//------------------------------------------------------------------------------
// Configuration bits:
//   - internal RC-oscilator
//   - WDT OFF
//   - low-voltage programming OFF
//   - debugging OFF
//------------------------------------------------------------------------------

__CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & LVPDIS & UNPROTECT & BORDIS 
               & IESODIS & FCMDIS & DEBUGDIS);


//------------------------------------------------------------------------------
//  Define outputs where leds are connected
//------------------------------------------------------------------------------

#define PIN_LED1    RD0
#define PIN_LED2    RD2
#define PIN_LED3    RD4

//------------------------------------------------------------------------------
//  Timer's parameters:
//  - prscaler = 4, 
//  - postscaler = 1,
//  - count limit = 250
// 
//  Fosc = 4 ÌÃö.
// 
//  TMR2 interrupt period = 4 * 1 * 250 * Tcyc = 1 ms
// 
//------------------------------------------------------------------------------

#define PR2_CONST       250-1
#define TMR2_PRS        1                           // prs = 4
#define TMR2_POST       0                           // post = 1
#define T2CON_CONST     (TMR2_POST<<3) | TMR2_PRS


//******************************************************************************
//  Interrupt service routine. (Interrupt occures every 1 ms)
//******************************************************************************

void interrupt isr (void)
{
    if (TMR2IF)
    {   
        OS_Timer();
        TMR2IF = 0;
    }
}

//******************************************************************************
//  Tasks
//******************************************************************************

void Task_T1 (void)
{
    for (;;)
    {
        PIN_LED1 ^= 1;       // Switch LED 1
        OS_Delay(500);       // Wait 500 ms
    }
}

//------------------------------------------------------------------------------

void Task_T2 (void)
{
    for (;;)
    {
        PIN_LED2 ^= 1;       // Switch LED 2
        OS_Delay(1000);      // Wait 1000 ms
    }
}

//------------------------------------------------------------------------------

void Task_T3 (void)
{
    for (;;)
    {
        PIN_LED3 ^= 1;       // Switch LED 3
        OS_Delay(1500);      // Wait 1500 ms
    }
}

//******************************************************************************
//  Perifery init
//******************************************************************************

void init (void)
{
    //------------------------------------------------------------------------------
    //  I/O ports setup
    //------------------------------------------------------------------------------

    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;

    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISD = 0;

    //------------------------------------------------------------------------------
    //  Timer setup
    //------------------------------------------------------------------------------

    PR2 = PR2_CONST;
    T2CON = T2CON_CONST | 0x04;
                                        
    //------------------------------------------------------------------------------
    //  Interrupts setup
    //------------------------------------------------------------------------------

    PIR1 = 0;
    PIR2 = 0;
    INTCON = 0;

    TMR2IE = 1;         // Enable TMR2 interrupt
    PEIE = 1;           // Enable periphery interrupts
                        // Global interrupts will be enabled
                        // in main just before running scheduler

}

//******************************************************************************
//  MAIN
//******************************************************************************

void main (void)
{
    init();             // Init perifery
    OS_Init();          // System init
    
    // Creating Tasks
    OS_Task_Create(2, Task_T1);
    OS_Task_Create(3, Task_T2);
    OS_Task_Create(4, Task_T3);

    OS_EI();            // Enable interrupts
                        
    OS_Run();           // Run scheduler
}

//******************************************************************************
//  END
//******************************************************************************


