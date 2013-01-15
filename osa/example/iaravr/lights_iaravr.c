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
  *  File:          lights_iaravr.c
  *
  *  Compilers:     IAR 5.30
  *
  *  Controller:    AT90S4433, 8MHz
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

#define ENABLE_BIT_DEFINITIONS

#include <ioavr.h>
#include <intrinsics.h>


//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

//------------------------------------------------------------------------------
#if     defined(__AT90S4433__)
//------------------------------------------------------------------------------

    #define DDRB_CONST      0x00    // all inputs
    #define DDRC_CONST      0x00    // all inputs
    #define DDRD_CONST      0xFF    // all outputs

    #define PORTB_CONST     0xFF    // pull-ups ON
    #define PORTC_CONST     0xFF    // pull-ups ON
    #define PORTD_CONST     0x00

    #define PORTLEDS        PORTD

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

    #define pin_BUTTON      (PINC & (1 << PINC1))

//------------------------------------------------------------------------------
//#elif   defined(...)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------

// Timer0 used as a counter for software PWM

#define TCCR0_CONST     0x02        // prs = 8 (period = 256 * 8 * 0.125us = 250 us)

// Timer1 used for system ticks

#define TCCR1B_CONST    0x01        // prs = 1
#define OCR1_CONST      8000        // period = 8000 * 1 * 0.125us = 1 ms

#define ms              / 1 





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

volatile char   m_cSpeed;       // Rotation speed
volatile char   m_cPosition;    // Current rotation phase (position of brightness value in 
                                // Brightness table) 
volatile char   m_cDirection;   // Rotation direction (-1, +1)


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

int  main (void)
{
    volatile char a, b, c;
    
    switch (a)
    { 
        case 1:
            {
                switch (b)
                {
                    case 1: c = 10; break;
                    case 2: c = 20; break;
                }
                
                case 3: c = 30; break;
                break;
            }
    }

    Init();                             // Init periphery

    OS_Init();                          // Init OS

    OS_Task_Create(0, Task_Rolling);    // Create tasks.
    OS_Task_Create(0, Task_SetSpeed);   // 
    OS_Task_Create(0, Task_Button);     // 

                                        // Starting values:
    m_cPosition  = 0;                   // rotation phase
    m_cDirection = 1;                   // dircetion

    OS_EI();                            // Enable interrupts

    OS_Run();                           // Running scheduler

}


/********************************************************************************
 *
 *  Interrupts service routine
 *
 ********************************************************************************/
#pragma  vector = TIMER0_OVF_vect
__interrupt void TIMER0_OVF(void)
{
    static char cCounter;   // PWM steps counter
           char cPosition;  // Position for rotation
           char cLedsMask;  // Current LED's mask
           char i;          // Loop variable

    //******************************************************************************
    //  Software PWM
    //******************************************************************************

    cCounter++;

    cPosition = m_cPosition;    // Position of brightness for first LED

    i = NUMBER_OF_LEDS;         // Loop on all LEDS
    cLedsMask = 0x01;

    do
    {
        //----------------------------------------------------------------------
        // Check for PWM duty cycle
        // 
        //----------------------------------------------------------------------
        if (cCounter > Brightness[cPosition & TABLE_MASK])  PORTLEDS &= ~cLedsMask;
        else                                                PORTLEDS |=  cLedsMask;

        cLedsMask <<= 1;            // Make mask for next LED
        cPosition += m_cDirection;  // Take next position of brightness


    } while (--i);

    cCounter &= 0x1F;               // PWM is 5-bit, msb are zeroed

}

#pragma  vector = TIMER1_COMP_vect
__interrupt void TIMER1_COMP(void)
{

    //******************************************************************************
    //  System timer (for system ticks)
    //******************************************************************************
    
    TCNT1 = 0;    
    OS_Timer();
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
    static char cDelay;

    for (;;)
    {
        cDelay = 0;
        while (cDelay++ <= m_cSpeed) OS_Delay(1);   // Wait delay according current
                                                    // rotation speed
        m_cPosition ++;                             // Change brightness position
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
        m_cDirection = -m_cDirection;

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
        m_cSpeed = ADC >> 2;          // Set new speed value

        OS_Delay(100 ms);           
    }
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

    #if defined(PORTB_CONST)
        DDRB  = DDRB_CONST;
        PORTB = PORTB_CONST;
    #endif


    #if defined(PORTC_CONST)
        DDRC  = DDRC_CONST;
        PORTC = PORTC_CONST;
    #endif

    #if defined(PORTD_CONST)
        DDRD  = DDRD_CONST;
        PORTD = PORTD_CONST;
    #endif

    //------------------------------------------------------------------------------
    //  ADC
    //------------------------------------------------------------------------------

    ADMUX = 0x00;
    ADCSR = 0xE7;

    //------------------------------------------------------------------------------
    //  Timers init
    //------------------------------------------------------------------------------
    
    TCCR0   = TCCR0_CONST;
    TCCR1B  = TCCR1B_CONST;
    OCR1    = OCR1_CONST;

    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------

    TIMSK   = (1 << OCIE1) | (1 << TOIE0);

}


//******************************************************************************
//  THE END
//******************************************************************************



