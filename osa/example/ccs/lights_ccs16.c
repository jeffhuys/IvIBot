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
  *  Compilers:     CCS
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
 
#include <16F887.h>

#fuses INTRC,NOWDT,NOMCLR,NOBROWNOUT,NOLVP,NODEBUG,NOIESO,NOFCMEN

#device ADC=8
#use fast_io (D)
#use fast_io (B)

#include <osa.h>



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

#define PORTD_CONST     0x00
#define TRISD_CONST     0x00

#define PORTE_CONST     0x00
#define TRISE_CONST     0x08

#define pin_BUTTON      input(PIN_B0)
#define PORTLEDS        PORTD

#define write_leds(value)   output_d(value)
#define read_leds()         input_d()

#define NUMBER_OF_LEDS  8
#define TABLE_MASK      7



//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------

// Timer0 used as a counter for software PWM

#define T0CON_CONST     0x01        // prs = 4 (period = 256 * 4 * 0.2us = 200 us)
                                    // 8-bit mode

// TImer2 used for system ticks
// post = 4, period = 250*4*5* 0.2 us = 1 ms

#define T2CON_CONST     T2_DIV_BY_4        
#define PR2_CONST       (250-1)     
#define T2POST_CONST    5

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

    OS_Task_Define(Task_Rolling);       // Define tasks.
    OS_Task_Define(Task_SetSpeed);      // 
    OS_Task_Define(Task_Button);        // 

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
    #if __DEVICE__ == 887
    setup_oscillator(OSC_8MHZ, 0x1F);
    #endif

    //------------------------------------------------------------------------------
    //  I/O ports configuration
    //------------------------------------------------------------------------------

    output_a(PORTA_CONST);
    output_b(PORTB_CONST);

    set_tris_a(TRISA_CONST);
    set_tris_b(TRISB_CONST);

    #if defined(PORTC_CONST)
        output_c(PORTC_CONST);
        set_tris_c(TRISC_CONST);
    #endif


    #if defined(PORTD_CONST)
        output_d(PORTD_CONST);
        set_tris_d(TRISD_CONST);
    #endif

    #if defined(PORTE_CONST)
        output_e(PORTE_CONST);
        set_tris_e(TRISE_CONST);
    #endif

    //------------------------------------------------------------------------------
    //  ADC
    //------------------------------------------------------------------------------

    setup_adc(ADC_CLOCK_DIV_32);
    
    #if __DEVICE__ == 887
    setup_adc_ports(sAN0);
    #else
    setup_adc_ports(RA0_ANALOG);
    #endif
    

    //------------------------------------------------------------------------------
    //  Timers init
    //------------------------------------------------------------------------------
    
    setup_timer_0(T0CON_CONST);
    setup_timer_2(T2CON_CONST, PR2_CONST, T2POST_CONST);


    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------
    
    enable_interrupts(INT_TIMER0);
    enable_interrupts(INT_TIMER2);
    enable_interrupts(GLOBAL);
}

/********************************************************************************
 *
 *  Interrupts service routine
 *
 ********************************************************************************/

//******************************************************************************
//  Software PWM
//******************************************************************************
#INT_TIMER0
void timer0_isr (void)
{
    static char cCounter;   // PWM steps counter
           char cPosition;  // Position for rotation
           char cLedsMask;  // Current LED's mask
           char i;          // Loop variable
           
    cCounter++;
    cPosition = m_cPosition;    // Position of brightness for first LED

    i = NUMBER_OF_LEDS;         // Loop on all LEDS
    cLedsMask = 0x01;

    do
    {
        //----------------------------------------------------------------------
        // Check for PWM duty cycle
        //----------------------------------------------------------------------
        if (cCounter > Brightness[cPosition & TABLE_MASK])  
            write_leds(read_leds() & ~cLedsMask);
        else 
            write_leds(read_leds() | cLedsMask);

        cLedsMask <<= 1;            // Make mask for next LED
        cPosition += m_cDirection;  // Take next position of brightness

    } while (--i);
    
    cCounter &= 0x1F;               // PWM is 5-bit, msb are zeroed
}    


//******************************************************************************
//  System timer (for system ticks)
//******************************************************************************
#INT_TIMER2
void timer2_isr (void)
{
    OS_Timer();
}




/********************************************************************************
 *                                                                              *
 *  TASK:           Task_Rolling                                                * 
 *                                                                              *
 *------------------------------------------------------------------------------*
 *
 *  description:    Performs rotation of brightesses for each LED
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
        set_adc_channel(0);
    
        m_cSpeed = read_adc();         // Set new speed value

        OS_Delay(100 ms);
    }
}




//******************************************************************************
//  THE END
//******************************************************************************

