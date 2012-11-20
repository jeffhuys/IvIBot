 /*
  ************************************************************************************************
  *
  *  OSA example:   Running lights
  *
  *  URL:           http://wiki.pic24.ru/doku.php/en/osa/ref/intro
  *                 http://picosa.narod.ru
  *
  *----------------------------------------------------------------------------------------------
  *
  *  File:          lights_mikroc.c
  *
  *  Compilers:     Microchip C18
  *
  *  Controller:    PIC18F252
  *
  *  Programmer:    Timofeev Victor
  *                 osa@pic24.ru, testerplus@mail.ru
  *
  *  Description:   This is simple program written with RTOS OSA.
  *                 There are eight LEDs controlled by the program. The program
  *                 changes brightness of each LED and changes it in time.
  *
  ************************************************************************************************
  */
 

#include <osa.h>
#include <p18f252.h>

#pragma config WDT = OFF
#pragma config OSC = HS 
#pragma config LVP = OFF
#pragma config BOR = OFF


//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

#define PORTA_CONST     0x00
#define TRISA_CONST     0x01

#define PORTB_CONST     0x00
#define TRISB_CONST     0x01

#define PORTC_CONST     0x00
#define TRISC_CONST     0x00

#define pin_BUTTON      PORTBbits.RB0
#define PORTLEDS        PORTC

#define NUMBER_OF_LEDS  8
#define TABLE_MASK      7



//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------

// Timer0 used as a counter for software PWM

#define T0CON_CONST     0x41        // prs = 4 (period = 256 * 4 * 0.2us = 200 us)
                                    // 8-bit mode
// TImer2 used for system ticks

#define T2CON_CONST     0x25        // post = 8, period = 250*4*5* 0.2 us = 1 ms
#define PR2_CONST       (250-1)     
#define ms              / 1         // 







//****************************************************************************** 
// 
//      LED's brightness table
// 
//****************************************************************************** 


//------------------------------------------------------------------------------
#if     NUMBER_OF_LEDS == 4
//------------------------------------------------------------------------------
    const char Brightness[] = {31, 11,  4,  0};
//------------------------------------------------------------------------------
#elif   NUMBER_OF_LEDS == 8
//------------------------------------------------------------------------------
    const char Brightness[] = {31, 20, 11,  7,  4, 2, 1, 0};
//------------------------------------------------------------------------------
#else
//------------------------------------------------------------------------------
    #error "Incorrect NUMBER_OF_LEDS constant value (should be 4 or 8)"
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


//******************************************************************************
//  
//      Global variables
// 
//******************************************************************************

volatile char   m_ucSpeed;       // Rotation speed
volatile char   m_ucPosition;    // Current rotation phase (position of brightness value in 
                                // Brightness table) 
volatile char   m_scDirection;   // Rotation direction (-1, +1)


//******************************************************************************
//  
//      Function prototypes
// 
//******************************************************************************

void    Init (void);
void    Task_Rolling (void);
void    Task_SetSpeed (void);
void    Task_Button (void);






/********************************************************************************
 *                                                                              *
 *  Function:       main                                                        * 
 *                                                                              *
 *------------------------------------------------------------------------------* 
 *                                                                              *
 ********************************************************************************/

void main (void)
{
    Init();                             // Init periphery

    OS_Init();                          // Init OS

    OS_Task_Create(0, Task_Rolling);    // Create tasks.
    OS_Task_Create(0, Task_SetSpeed);   // 
    OS_Task_Create(0, Task_Button);     // 

                                        // Starting values:
    m_ucPosition  = 0;                  // rotation phase
    m_scDirection = 1;                  // dircetion

    OS_EI();                            // Enable interrupts

    OS_Run();                           // Running scheduler

}


/********************************************************************************
 *                                                                              *
 *  Function:       Init                                                        *
 *                                                                              *
 *------------------------------------------------------------------------------* 
 *
 *  description:    Makes periphery initialization:
 *                  - I/O ports
 *                  - ADC
 *                  - timers
 *                  - interrupts
 *
 *  parameters:     void
 *
 *  on return:      void
 *
 ********************************************************************************/

void Init (void)
{

    //------------------------------------------------------------------------------
    //  I/O ports configuration
    //------------------------------------------------------------------------------

    PORTA = PORTA_CONST;
    PORTB = PORTB_CONST;

    TRISA = TRISA_CONST;
    TRISB = TRISB_CONST;

    INTCON2bits.RBPU = 0;

    #if defined(PORTC_CONST)
        PORTC = PORTC_CONST;
        TRISC = TRISC_CONST;
    #endif


    #if defined(PORTD_CONST)
        PORTD = PORTD_CONST;
        TRISD = TRISD_CONST;
    #endif

    #if defined(PORTE_CONST)
        PORTE = PORTE_CONST;
        TRISE = TRISE_CONST;
    #endif

    //------------------------------------------------------------------------------
    //  ADC
    //------------------------------------------------------------------------------


    ADCON0 = 0xC1;                  // Channel 0
                                    // ADON = 1
                                    // Fosc/32
    
    ADCON1 = 0x0E;                  // Use only one analog input AN0 (RA0)
                                    // Left justify

    //------------------------------------------------------------------------------
    //  Timers init
    //------------------------------------------------------------------------------
    
    T0CON = 0x80 | T0CON_CONST;

    T2CON = T2CON_CONST;
    PR2 = 250-1;

    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------
    
    INTCON = 0;
    INTCONbits.T0IE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
}

/********************************************************************************
 *
 *  Interrupts service routine
 *
 ********************************************************************************/
void interrupt_high (void);

//----------------------------------------------------------------------------
// High priority interrupt vector

#pragma code InterruptVectorHigh = 0x08
void
InterruptVectorHigh (void)
{
  _asm
    goto interrupt_high //jump to interrupt routine
  _endasm
}

//----------------------------------------------------------------------------
// High priority interrupt routine

#pragma code
#pragma interrupt interrupt_high

void interrupt_high (void)
{
    static unsigned char ucCounter;   // PWM steps counter
           unsigned char ucPosition;  // Position for rotation
           unsigned char ucLedsMask;  // Current LED's mask
           char i;          // Loop variable

    //******************************************************************************
    //  Software PWM
    //******************************************************************************
    
    if (INTCONbits.T0IF && INTCONbits.T0IE)
    {
        INTCONbits.T0IF = 0;
        ucCounter++;

        ucPosition = m_ucPosition;    // Position of brightness for first LED

        i = NUMBER_OF_LEDS;         // Loop on all LEDS
        ucLedsMask = 0x01;

        do
        {
            //----------------------------------------------------------------------
            // Check for PWM duty cycle
            // 
            //----------------------------------------------------------------------
            if (ucCounter > Brightness[ucPosition & TABLE_MASK])  PORTLEDS &= ~ucLedsMask;
            else                                                  PORTLEDS |=  ucLedsMask;

            ucLedsMask <<= 1;            // Make mask for next LED
            ucPosition += m_scDirection; // Take next position of brightness


        } while (--i);
        
        ucCounter &= 0x1F;               // PWM is 5-bit, msb are zeroed
    }


    //******************************************************************************
    //  System timer (for system ticks)
    //******************************************************************************
    
    if (PIR1bits.TMR2IF)
    {
        PIR1bits.TMR2IF = 0;
        OS_Timer();
    }

}




/********************************************************************************
 *                                                                              *
 *  TASK:           Task_Rolling                                                * 
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Perfors rotation of brightesses for each LED
 *
 ********************************************************************************/

void Task_Rolling (void)
{
    static unsigned char ucDelay;

    for (;;)
    {
        ucDelay = 0;
        while (ucDelay++ <= m_ucSpeed) OS_Delay(1);  // Wait delay according current
                                                     // rotation speed
        m_ucPosition ++;                             // Change brightness position
    }
}

/********************************************************************************
 *                                                                              *
 *  TASK:           Task_Button                                                 * 
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Wait for button pressed (with debounce) and change rotation
 *                  direction
 *
 ********************************************************************************/

void Task_Button (void)
{
    for (;;)
    {
        //------------------------------------------------------------------------------
        //  Wait for button press
        //------------------------------------------------------------------------------
        do 
        {
            OS_Cond_Wait(!pin_BUTTON);
            OS_Delay(40 ms);                // 40 ms for debounce
        } while (pin_BUTTON);

        //------------------------------------------------------------------------------
        //  Change direction of rotation
        //------------------------------------------------------------------------------
        // 
        m_scDirection = -m_scDirection;

        //------------------------------------------------------------------------------
        //  Wait for button release
        //------------------------------------------------------------------------------
        do 
        {
            OS_Cond_Wait(pin_BUTTON);
            OS_Delay(40 ms);                // 40 ms for debounce
        } while (!pin_BUTTON);

    }
}

/********************************************************************************
 *                                                                              *
 *  TASK:           Task_SetSpeed                                               * 
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Once per 100 ms check the AD value and set rotation speed
 *
 ********************************************************************************/

void Task_SetSpeed (void)
{
    for (;;)
    {
        ADCON0 &= ~0x38;                    // Set AD channel 0
    
        ADCON0bits.GO = 1;                  // Run conversion
        OS_Cond_Wait(!ADCON0bits.NOT_DONE); // Wait for conversion complete

        m_ucSpeed = ADRESH;                 // Set new speed value

        OS_Delay(100 ms);
    }
}




//******************************************************************************
//  THE END
//******************************************************************************

