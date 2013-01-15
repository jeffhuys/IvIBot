//******************************************************************************
//  
//  TUTOR3: Demonstration of task synchronizaton with binary semaphores
// 
//          (Demo-board with 16F887 from pickit2 used as a hardware)
//  
//******************************************************************************
// 

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

#define PORT_LEDS   PORTD



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

void Task_LEDS_ON (void)
{
    static char s_i;      // Cycle counter
    static char s_cMask;  // LEDs mask

    for (;;)
    {
        OS_Bsem_Wait(BS_LEDS_ARE_FREE); // Wait for another task will end
                                        // working with LEDs
                                        
        s_cMask = 1;                    // First LED will be ON first

        for (s_i = 0; s_i < 8; s_i++)
        {
            PORT_LEDS |= s_cMask;       // Switch ON current LED
            s_cMask <<= 1;              // Take next LED
            OS_Delay(100);              // Wait 100 ms
        }

        OS_Bsem_Set(BS_LEDS_ARE_FREE);  // Free LEDs
    }
}

//------------------------------------------------------------------------------

void Task_LEDS_OFF (void)
{
    static char s_i;      // Cycle counter
    static char s_cMask;  // LEDs mask

    for (;;)
    {
        OS_Bsem_Wait(BS_LEDS_ARE_FREE); // Wait for another task will end
                                        // working with LEDs

        s_cMask = 0x80;                 // Last LED will be OFF first

        for (s_i = 0; s_i < 8; s_i++)
        {
            PORT_LEDS &= ~s_cMask;      // Switch OFF current LED
            s_cMask >>= 1;              // Take next LED
            OS_Delay(150);              // Wait 150 ms
        }

        OS_Bsem_Set(BS_LEDS_ARE_FREE);  // Free LEDs
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
//  main
//******************************************************************************

void main (void)
{
    init();                             // Init perifery
    OS_Init();                          // System init
    
    
    OS_Task_Create(3, Task_LEDS_ON);    // Creating tasks
    OS_Task_Create(3, Task_LEDS_OFF);

    OS_Bsem_Set(BS_LEDS_ARE_FREE);      // Tell to tasks that LEDs are free now

    OS_EI();                            // Enable interrupts

    OS_Run();                           // Run scheduler
}

//******************************************************************************
//  end of file
//******************************************************************************

