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
  *  Compilers:     HT PICC STD
  *
  *  Controller:    PIC16F887
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
 

#include <htc.h>
#include <osa.h>


//------------------------------------------------------------------------------
#if     defined(_16F887) || defined(_16F886)
//------------------------------------------------------------------------------

    __CONFIG(INTIO & WDTDIS & PWRTEN & MCLRDIS & LVPDIS & UNPROTECT & BORDIS & IESODIS & FCMDIS & DEBUGDIS);

//------------------------------------------------------------------------------
#elif   defined(_16F690)
//------------------------------------------------------------------------------

    __CONFIG (INTIO & WDTDIS & PWRTEN & MCLRDIS & UNPROTECT & BORDIS & IESODIS & FCMDIS);

//------------------------------------------------------------------------------
#elif   defined(_16F88)
//------------------------------------------------------------------------------

    __CONFIG (INTIO & WDTDIS & PWRTEN & MCLRDIS & LVPDIS & UNPROTECT & BORDIS & DEBUGDIS);
    __CONFIG (FCMDIS & IESODIS);

//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------




//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

//------------------------------------------------------------------------------
#if     defined(_16F886)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x01
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define PORTE_CONST     0x00
    #define TRISE_CONST     0x08

    #define pin_BUTTON      RE3
    #define PORTLEDS        PORTB

    #define NUMBER_OF_LEDS  4 
    #define TABLE_MASK      3

//------------------------------------------------------------------------------
#elif   defined(_16F887)
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

    #define pin_BUTTON      RB0
    #define PORTLEDS        PORTD

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

//------------------------------------------------------------------------------
#elif     defined(_16F690)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x09
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00

    #define PORTC_CONST     0x00
    #define TRISC_CONST     0x00

    #define pin_BUTTON      RA3
    #define PORTLEDS        PORTC

    #define NUMBER_OF_LEDS  4
    #define TABLE_MASK      3

//------------------------------------------------------------------------------
#elif   defined(_16F88)
//------------------------------------------------------------------------------

    #define PORTA_CONST     0x00
    #define TRISA_CONST     0x03
    
    #define PORTB_CONST     0x00
    #define TRISB_CONST     0x00

    #define pin_BUTTON      RA1
    #define PORTLEDS        PORTB

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

    #define T0IF    TMR0IF
    #define T0IE    TMR0IE
    
//------------------------------------------------------------------------------
#endif
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------

// Timer0 used as a counter for software PWM

#define T0CON_CONST     0x01        // prs = 4 (period = 256 * 4 * 0.5us = 500 us)

// TImer2 used for system ticks

#define T2CON_CONST     0x34        // post = 8, period = 250 * 8 * 0.5us = 1 ms
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
    //  Set internal oscilator frequency = 8 ÌÃö
    //------------------------------------------------------------------------------

    OSCCON  = 0b01110000;
    OSCTUNE = 0b00011111;

    //------------------------------------------------------------------------------
    //  I/O ports configuration
    //------------------------------------------------------------------------------

    PORTA = PORTA_CONST;
    PORTB = PORTB_CONST;

    TRISA = TRISA_CONST;
    TRISB = TRISB_CONST;

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

    ADCON0 = 0;
    ADCON1 = 0;

    #if defined(_16F88) || defined(_16F690)
    ADCS2 = 0;
    #endif
    ADCS1 = 1;                      // Frc
    ADCS0 = 1;
    ADFM  = 0;                      // Left justify

    ANSEL  = 0x01;                  // RA0 - analog input

    #if defined(_16F886) || defined(_16F887) || defined(_16F690)
    ANSELH = 0x00;   
    #endif

    ADON = 1;                       // Âêëþ÷àåì ÀÖÏ

    //------------------------------------------------------------------------------
    //  Timers init
    //------------------------------------------------------------------------------
    
    OPTION = 0x80 | T0CON_CONST;

    T2CON = T2CON_CONST;
    PR2 = 250-1;

    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------
    
    INTCON = 0;
    T0IE = 1;
    PEIE = 1;
    TMR2IE = 1;

}

/********************************************************************************
 *
 *  Interrupts service routine
 *
 ********************************************************************************/

void interrupt isr (void)
{
    static char cCounter;   // PWM steps counter
           char cPosition;  // Position for rotation
           char cLedsMask;  // Current LED's mask
           char i;          // Loop variable

    OS_EnterInt();

    //******************************************************************************
    //  Software PWM
    //******************************************************************************

    if (T0IF && T0IE)
    {
        T0IF = 0;
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
    
    if (TMR2IF)
    {
        TMR2IF = 0;
        OS_Timer();
    }

    OS_LeaveInt();
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
        CHS0 = 0;                   // Set AD channel 0
        CHS1 = 0;                   //
        CHS2 = 0;                   //
    
        #if defined(_16F886) || defined(_16F887) || defined(_16F690)
        CHS3 = 0;                   //
        #endif

        GODONE = 1;                 // Run conversion
        OS_Cond_Wait(!GODONE);      // Wait for conversion complete

        m_cSpeed = ADRESH;          // Set new speed value

        OS_Delay(100 ms);           
    }
}




//******************************************************************************
//  THE END
//******************************************************************************



