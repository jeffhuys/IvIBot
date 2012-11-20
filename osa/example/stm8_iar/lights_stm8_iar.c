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
  *  Compilers:     IAR
  *
  *  Controller:    STM8S105C6
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

#include <iostm8.h>


//******************************************************************************
//  
//      Constants
// 
//******************************************************************************

//------------------------------------------------------------------------------
//#if     defined(__STM8__)
//------------------------------------------------------------------------------

    #define PA_DDR_CONST      0xFF    // all outputs
    #define PB_DDR_CONST      0xFF    // all outputs
    #define PC_DDR_CONST      0xFF    // all outputs
    #define PD_DDR_CONST      0xFF    // all outputs
    #define PE_DDR_CONST      0x7F    // all outputs, PE7 input (button)
    #define PG_DDR_CONST      0xFF    // all outputs

    #define PORTLEDS        PB_ODR

    #define NUMBER_OF_LEDS  8
    #define TABLE_MASK      7

    #define PIN_BUTTON      (PE_IDR & 0x80)

//------------------------------------------------------------------------------
//#elif   defined(...)
//------------------------------------------------------------------------------


//------------------------------------------------------------------------------
//#endif
//------------------------------------------------------------------------------



//------------------------------------------------------------------------------
// Timers
//------------------------------------------------------------------------------

// Timer1 used as a counter for software PWM

#define TIM1_ARR_CONST  1000        // 0.5 ms

// Timer2 used for system ticks

#define TIM2_ARR_CONST  2000        // 1 ms

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

volatile unsigned char   m_cSpeed;      // Rotation speed
volatile unsigned char   m_cPosition;   // Current rotation phase (position of brightness value in 
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

#pragma vector = TIM1_OVR_UIF_vector
__interrupt void TIM1_IRQHandler(void)
{
    static char cCounter;   // PWM steps counter
           char cPosition;  // Position for rotation
           char cLedsMask;  // Current LED's mask
           char i;          // Loop variable

    TIM1_SR1 &= ~1;
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

#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_IRQHandler(void)
{

    //******************************************************************************
    //  System timer (for system ticks)
    //******************************************************************************
    
    TIM2_SR1 &= ~1;
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
    static unsigned char cDelay;

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
            OS_Cond_Wait(!PIN_BUTTON);
            OS_Delay(40 ms);                // 40 ms for debounce
        } while (PIN_BUTTON);

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
            OS_Cond_Wait(PIN_BUTTON);
            OS_Delay(40 ms);                // 40 ms for debounce
        } while (!PIN_BUTTON);

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
        ADC_CR1 |= 1; // Freq = 7, continues = 1, ADON = 1
        OS_Delay(100 ms);           
        m_cSpeed = ADC_DRH;          // Set new speed value
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

    #if defined(PA_DDR_CONST)
        PA_DDR  = PA_DDR_CONST;
        PA_CR1  = 0xFF;
    #endif

    #if defined(PB_DDR_CONST)
        PB_DDR  = PB_DDR_CONST;
        PB_CR1  = 0xFF;
    #endif

    #if defined(PC_DDR_CONST)
        PC_DDR  = PC_DDR_CONST;
        PC_CR1  = 0xFF;
    #endif

    #if defined(PD_DDR_CONST)
        PD_DDR  = PD_DDR_CONST;
        PD_CR1  = 0xFF;
    #endif

    #if defined(PE_DDR_CONST)
        PE_DDR  = PE_DDR_CONST;
        PE_CR1  = 0xFF;
    #endif

    #if defined(PG_DDR_CONST)
        PG_DDR  = PG_DDR_CONST;
        PG_CR1  = 0xFF;
    #endif


    //------------------------------------------------------------------------------
    //  ADC
    //------------------------------------------------------------------------------

    ADC_CSR = 0x09; // All interrupts disable, Channel num = 9
    ADC_CR1 = 0x71; // Freq = 7, continues = 1, ADON = 1
    ADC_CR2 = 0x00; // Allignment left, scan mode disabled
    ADC_CR3 = 0x00; // Data buffer disable

    //------------------------------------------------------------------------------
    //  Timers init
    //------------------------------------------------------------------------------
    
    TIM1_CR1 = 0x81;
    TIM1_ARRH = TIM1_ARR_CONST >> 8;
    TIM1_ARRL = TIM1_ARR_CONST & 0xFF;

    TIM2_CR1 = 0x81;
    TIM2_ARRH = TIM2_ARR_CONST >> 8;
    TIM2_ARRL = TIM2_ARR_CONST & 0xFF;

    //------------------------------------------------------------------------------
    //  Interrupts
    //------------------------------------------------------------------------------

    TIM1_IER = 0x01;
    TIM2_IER = 0x01;

//    OS_CLRWDT();
}


//******************************************************************************
//  THE END
//******************************************************************************



