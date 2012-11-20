//******************************************************************************
//  
//  TUTOR2: This example shows why local variables should be deckared with 
//          'static' keyword. Try this program in simulator and you will see
//          that variables cTemp1 (in Task_T1) and cTemp2 (in Task_T2) will
//          be overwritten by itself. 
//          
//          Then try to redeclare variables cTemp1 and cTemp2 with 'static':
//          
//          static char cTemp1;
// 
//          and see that program begin work correctly.
// 
//******************************************************************************




#include <osa.h>

//******************************************************************************
//  Global variables
//******************************************************************************

char m_cTest1;
char m_cTest2;

//******************************************************************************
//  Tasks
//******************************************************************************

void Task_T1 (void)
{
    char cTemp1;

    m_cTest1 = 0;

    for (;;)
    {
        cTemp1 = 1;              // Value of non-static variable will be 
                                 // lost after switching to scheduler
        OS_Yield();
        m_cTest1 = cTemp1;
    }
}

//------------------------------------------------------------------------------

void Task_T2 (void)
{
    char cTemp2;

    m_cTest2 = 0;

    for (;;)
    {
        cTemp2 = 1;              // Value of non-static variable will be 
                                 // lost after switching to scheduler
        OS_Yield();
        m_cTest2 = cTemp2;
    }
}

//******************************************************************************
//  main
//******************************************************************************

void main (void)
{
    OS_Init();                  // System init

    OS_Task_Create(3, Task_T1); // Creating task (tell to OS that these 
    OS_Task_Create(3, Task_T2); // functions will be called indirrectly
                                // by scheduler

    OS_Run();                   // Run scheduler
}

//******************************************************************************
//  end of file
//******************************************************************************
