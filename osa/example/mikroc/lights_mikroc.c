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
  *  Compilers:     mikroC
  *
  *  Controller:    PIC18
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



//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

//------------------------------------------------------------------------------
#if     defined(P18F252) || defined(P18F258) || defined(P18F242) || defined(P18F248)\
     || defined(P16F873) || defined(P16F876) || defined(P16F873A) || defined(P16F876A)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x01
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x01

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define pin_BUTTON      PORTB.B0
    #define PORTLEDS        PORTC

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

//------------------------------------------------------------------------------
#elif   defined(P18F452) || defined(P18F458) || defined(P18F442) || defined(P18F448)\
     || defined(P16F877) || defined(P16F874) || defined(P16F877A) || defined(P16F874A)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x01

    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x01

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define PORTD_CONST     0x00
    #define TRISD_CONST     0x00

    #define PORTE_CONST     0x00
    #define TRISE_CONST     0x00

    #define pin_BUTTON      PORTB.B0
    #define PORTLEDS        PORTC

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


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

// Tell to linker that these functions will be called indirrectly

#pragma funcall main Task_Rolling
#pragma funcall main Task_SetSpeed
#pragma funcall main Task_Button

void main (void)
{
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

    NOT_RBPU_bit = 0;
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
    
    #ifdef __OSAMIKROC18__
    T0CON = 0x80 | T0CON_CONST;
    #endif
    
    #ifdef __OSAMIKROC16__
    OPTION_REG = 0x00 | T0CON_CONST;
    #endif

    T2CON = T2CON_CONST;
    PR2 = 250-1;

    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------
    
    INTCON = 0;
    T0IE_bit = 1;
    PEIE_bit = 1;
    TMR2IE_bit = 1;
}

/********************************************************************************
 *
 *  Interrupts service routine
 *
 ********************************************************************************/

void interrupt (void)
{
    static char cCounter;   // PWM steps counter
           char cPosition;  // Position for rotation
           char cLedsMask;  // Current LED's mask
           char i;          // Loop variable

    //******************************************************************************
    //  Software PWM
    //******************************************************************************
    
    if (T0IF_bit && T0IE_bit)
    {
        T0IF_bit = 0;
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


    //******************************************************************************
    //  System timer (for system ticks)
    //******************************************************************************
    
    if (TMR2IF_bit)
    {
        TMR2IF_bit = 0;
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
        ADCON0 &= ~0x38;            // Set AD channel 0
    
        GO_bit = 1;                 // Run conversion
        OS_Cond_Wait(!NOT_DONE_bit);// Wait for conversion complete

        m_cSpeed = ADRESH;          // Set new speed value

        OS_Delay(100 ms);
    }
}




//******************************************************************************
//  THE END
//******************************************************************************
