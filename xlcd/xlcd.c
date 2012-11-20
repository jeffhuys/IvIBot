/*********************************************************************
 *
 *                  External LCD access routines
 *
 *********************************************************************
 * FileName:        XLCD.c
 * Dependencies:    xlcd.h
 * Processor:       PIC18
 * Complier:        MCC18 v1.00.50 or higher
 *                  HITECH PICC-18 V8.10PL1 or higher
 * Company:         Microchip Technology, Inc.
 *
 * Software License Agreement
 * The software supplied herewith by Microchip Technology Incorporated
 * (the “Company”) for its PICmicro® Microcontroller is intended and
 * supplied to you, the Company’s customer, for use solely and
 * exclusively on Microchip PICmicro Microcontroller products. The
 * software is owned by the Company and/or its supplier, and is
 * protected under applicable copyright laws. All rights are reserved.
 * Any use in violation of the foregoing restrictions may subject the
 * user to criminal sanctions under applicable laws, as well as to
 * civil liability for the breach of the terms and conditions of this
 * license.
 *
 * THIS SOFTWARE IS PROVIDED IN AN “AS IS” CONDITION. NO WARRANTIES,
 * WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED
 * TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. THE COMPANY SHALL NOT,
 * IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL OR
 * CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 *
 * HiTech PICC18 Compiler Options excluding device selection:
 *                  -FAKELOCAL -G -E -C
 *
 * Author               Date    Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Naveen Raj          6/9/03         Original        (Rev 1.0)
 ********************************************************************/
#include "xlcd.h"
char _vXLCDreg =0;          //Used as a flag to check if from XLCDInit()

/*********************************************************************
 * Function         : void XLCDInit(void)
 * PreCondition     : None
 * Input            : None
 * Output           : None
 * Side Effects     : None
 * Overview         : LCD is intialized
 * Note             : This function will work with all Hitachi HD447780
 *                    LCD controller.
 ********************************************************************/
void XLCDInit(void)
{
/*This par of the code is initialization by instruction*/
_vXLCDreg=1; 

//PORT initialization  
#ifdef  XLCD_8BIT                           //8-bit mode, use whole port
    XLCD_DATAPORT_TRIS  = 0x00;             //make DATAPORT output
    XLCD_DATAPORT = 0;
#endif                       

#ifdef  XLCD_4BIT                           //4bit mode
    #ifdef XLCD_UPPER                       //Upper 4-bits of the DATAPORT output
    XLCD_DATAPORT_TRIS  &= 0x0f;
    XLCD_DATAPORT &= 0x0f;
    #else                                   //Lower 4-bits of the DATAPORT output
    XLCD_DATAPORT_TRIS  &= 0xf0;
    XLCD_DATAPORT &= 0xf0;
    #endif
#endif
//end of data port initialization


//control port initialization
XLCD_RSPIN_TRIS =0;                         //make control ports output
XLCD_ENPIN_TRIS =0;
#ifndef XLCD_RW_GROUND
XLCD_RWPIN_TRIS =0;                         //if RW pin grounded
#endif

XLCD_RSPIN  =0;                             //clear control ports
XLCD_ENPIN  =0;
#ifndef XLCD_RW_GROUND
XLCD_RWPIN=0;                               //if RW pin grounded
#endif



//initialization by instruction

XLCDDelay15ms(); 
#ifdef XLCD_8BIT                    // 8-bit mode interface
    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
#endif    

#ifdef XLCD_4BIT    
    #ifdef XLCD_UPPER               // Upper nibble interface
    XLCD_DATAPORT   &= 0x0f;        // Clear upper port
    XLCD_DATAPORT   |= 0b00110000;
    #else                           // Lower nibble interface
    XLCD_DATAPORT       &= 0xf0;    // Clear lower port
    XLCD_DATAPORT   |= 0b00000011;  // Function set cmd(4-bit interface)
    #endif
#endif
    XLCD_ENPIN = 1;                 // Clock the cmd in
    XLCD_Delay500ns();   
    XLCD_ENPIN = 0;
/////////////////////////////////////////////////////////////////////////
    XLCDDelay4ms();
#ifdef XLCD_8BIT                    // 8-bit mode interface
    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
#endif    

#ifdef XLCD_4BIT    
    #ifdef XLCD_UPPER               // Upper nibble interface
    XLCD_DATAPORT   &= 0x0f;        // Clear upper port
    XLCD_DATAPORT   |= 0b00110000;
    #else                           // Lower nibble interface
    XLCD_DATAPORT       &= 0xf0;    // Clear lower port
    XLCD_DATAPORT   |= 0b00000011;  // Function set cmd(4-bit interface)
    #endif
#endif
    XLCD_ENPIN = 1;                 // Clock the cmd in
    XLCD_Delay500ns();   
    XLCD_ENPIN = 0;
//////////////////////////////////////////////////////////////////////////
 //       XLCDDelay100us();
    XLCDDelay4ms(); 
#ifdef XLCD_8BIT                    // 8-bit mode interface
    XLCD_DATAPORT   = 0b00110000;   // Function set cmd(8-bit interface)
#endif    

#ifdef XLCD_4BIT    
    #ifdef XLCD_UPPER               // Upper nibble interface
    XLCD_DATAPORT   &= 0x0f;        // Clear upper port
    XLCD_DATAPORT   |= 0b00110000;
    #else                           // Lower nibble interface
    XLCD_DATAPORT       &= 0xf0;    // Clear lower port
    XLCD_DATAPORT   |= 0b00000011;  // Function set cmd(4-bit interface)
    #endif
#endif

    XLCD_ENPIN = 1;                 // Clock the cmd in
    XLCD_Delay500ns();   
    XLCD_ENPIN = 0;
    
    
//required only for 4 bit interface as per LCDdatasheet    
#ifdef XLCD_4BIT
    XLCDDelay4ms();    
    #ifdef XLCD_UPPER               // Upper nibble interface
    XLCD_DATAPORT   &= 0x0f;        // Clear upper port
    XLCD_DATAPORT   |= 0b00100000;
    #else                           // Lower nibble interface
    XLCD_DATAPORT       &= 0xf0;    // Clear lower port
    XLCD_DATAPORT   |= 0b00000010;  // Function set cmd(4-bit interface)
    #endif

    XLCD_ENPIN = 1;                 // Clock the cmd in
    XLCD_Delay500ns();   
    XLCD_ENPIN = 0;
#endif    
//-----------------------------------------------------------------------
//function set command "0 0 1 DL N F X X"
//-----------------------------------------------------------------------

#ifdef XLCD_8BIT                    // if 8bit

    #ifdef XLCD_1LINE
        #ifdef XLCD_FONT5x8
        XLCDCommand(0b00110000);    //if 1Line 5x8
        #else
        XLCDCommand(0b00110100);    //if 1Line 5x10
        #endif
    #endif
    
    #ifdef XLCD_2LINE
        #ifdef XLCD_FONT5x8
        XLCDCommand(0b00111000);    //if 2Line 5x8
        #else
        XLCDCommand(0b00111100);    //if 2Line 5x10
        #endif
    #endif      
#endif

#ifdef XLCD_4BIT                    //if 4bit
    #ifdef XLCD_1LINE
        #ifdef XLCD_FONT5x8
        XLCDCommand(0b00100000);    //if 1Line 5x8
        #else
        XLCDCommand(0b00100100);    //if 1Line 5x10
        #endif
    #else
        #ifdef XLCD_FONT5x8
        XLCDCommand(0b00101000);    //if 2Line 5x8
        #else
        XLCDCommand(0b00101100);    //if 2Line 5x10
        #endif
    #endif  
#endif    
    XLCDCommand(0b00001000);        //display off
    XLCDCommand(0b00000001);        //display clear
/////////////////////////////////////////////////////////////////////////////////
//Entry mode setting
////////////////////////////////////////////////////////////////////////////////
//Entry mode command " 0 0 0 0 0 1 ID S "
//ID =0 no cursor increment during read and write
//ID =1 cursor increment during read and write
//S =0 no display during read and write
//S =1 display shift 
       
#ifdef XLCD_CURSOR_INCREMENT
    #ifdef XLCD_DISPLAY_SHIFT
    XLCDCommand(0b00000111);    //if cursor inc and display shift
    #endif
    #ifdef XLCD_DISPLAY_NOSHIFT
    XLCDCommand(0b00000110);    //if cursor inc and no display shift
    #endif
#endif

#ifdef  XLCD_CURSOR_NOINCREMENT
    #ifdef XLCD_DISPLAY_SHIFT
    XLCDCommand(0b00000101);    //if no cursor increment, but with display shift
    #endif
    #ifdef XLCD_DISPLAY_NOSHIFT
    XLCDCommand(0b00000100);    //if no cursor increment, and no display shift
    #endif
#endif 
///////////////////////////////////////////////////////////////////////////////////
//Display on off ,Blink ,cursor command set 
// ///////////////////////////////////////////////////////////////////////////////
//"0 0 0 0 1 D C B "
//D=1 dislay on, C=1 cursor on, B=1 blink on

#ifdef  XLCD_DISPLAYON
    #ifdef XLCD_CURSORON
        #ifdef XLCD_BLINKON
        XLCDCommand(0b00001111);    //display on cursor on blink on
        #else
        XLCDCommand(0b00001110);    //display on cursor on blink off
        #endif
    #endif    
   
    #ifdef XLCD_CURSOROFF
        #ifdef XLCD_BLINKON
        //XLCDCommand(0b00001001);    //display on cursor off blink on
        #else
        XLCDCommand(0b00001100);    // display on cursor off blink off
        #endif
    #endif
#endif


#ifdef  XLCD_DISPLAYOFF
    XLCDCommand(0b00001000);        //display off
#endif            
_vXLCDreg=0;
// end of initialization
      return;
}

/*********************************************************************
 * Function         : void XLCDCommand(unsigned char cmd)
 * PreCondition     : None
 * Input            : cmd - Command to be set to LCD.
 * Output           : None
 * Side Effects     : None
 * Overview         : None
 * Note             : None
 ********************************************************************/
void XLCDCommand(unsigned char cmd)
{
if(_vXLCDreg==1)                            //if  called from XLCDinit routine is always Blocking
{
    #ifdef  XLCD_DELAYMODE
    XLCDDelay();
    #endif
    #ifdef  XLCD_READBFMODE
    XLCDIsBusy();
    #endif
}


if(_vXLCDreg==0)                            //if not called from XLCDinit routine
{                                           //if NON Block the user need to call XLCDIsBusy 
#ifdef  XLCD_BLOCK                          //and check the w reg status to check if the
    #ifdef  XLCD_DELAYMODE                  //module is free
    XLCDDelay();
    #endif
    #ifdef  XLCD_READBFMODE
    XLCDIsBusy();
    #endif
#endif
}

XLCD_RSPIN=0;
XLCD_ENPIN=0;
#ifndef XLCD_RW_GROUND
XLCD_RWPIN=0;
#endif

#ifdef XLCD_8BIT	
    XLCD_DATAPORT = cmd;                    // Write command to data port
    XLCD_ENPIN = 1;                         // Clock the cmd in
    XLCD_Delay500ns();   
    XLCD_ENPIN = 0;
#endif

#ifdef XLCD_4BIT
    #ifdef XLCD_UPPER
        XLCD_DATAPORT &=0x0f;               //clear port
        XLCD_DATAPORT |= cmd&0xf0;          //write upper nibble to port
        XLCD_ENPIN = 1;                     // Clock the cmd in
        XLCD_Delay500ns();   
        XLCD_ENPIN = 0;
        
        XLCD_DATAPORT &= 0x0f;              //clear port
        XLCD_DATAPORT |= (cmd<<4)&0xf0;	    //shift left 4 times
        XLCD_ENPIN = 1;
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
    #endif 

    #ifdef XLCD_LOWER
        XLCD_DATAPORT &=0xF0;               //clear port
        XLCD_DATAPORT |=((cmd>>4)&0x0f);
        XLCD_ENPIN = 1;                     // Clock the cmd in
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
        
        XLCD_DATAPORT &= 0xF0;              //clear port
        XLCD_DATAPORT |= cmd&0x0f ;	        //shift left 4 times
        XLCD_ENPIN = 1;
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
    #endif 

#endif

	
    return;
}
/*********************************************************************
 * Function         :XLCDPut()
 * PreCondition     :None
 * Input            :cmd - Command to be set to LCD.
 * Output           :None
 * Side Effects     :None
 * Overview         :None
 * Note             :None
 ********************************************************************/
void XLCDPut(char data)
{
#ifdef  XLCD_BLOCK
    #ifdef  XLCD_DELAYMODE
    XLCDDelay();
    #endif
    #ifdef  XLCD_READBFMODE
    XLCDIsBusy();
    #endif
#endif


#ifndef XLCD_RW_GROUND
XLCD_RWPIN=0;
#endif
XLCD_RSPIN=1;
XLCD_ENPIN=0;
#ifdef XLCD_8BIT
    XLCD_DATAPORT=data;
    XLCD_ENPIN = 1;
    XLCD_Delay500ns();
    XLCD_ENPIN = 0;
#endif
#ifdef XLCD_4BIT
    #ifdef XLCD_UPPER
        XLCD_DATAPORT &=0x0f;               //clear port
        XLCD_DATAPORT |= data&0xf0;         //write upper nibble to port
        XLCD_ENPIN = 1;                     // Clock the cmd in
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
        
        XLCD_DATAPORT &= 0x0f;              //clear port
        XLCD_DATAPORT |= (data<<4)&0xf0;	//shift left 4 times
        XLCD_ENPIN = 1;
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
    #endif
    #ifdef XLCD_LOWER
        XLCD_DATAPORT &=0xF0;               //clear port
        XLCD_DATAPORT |=((data>>4)&0x0f);
        XLCD_ENPIN = 1;                     // Clock the cmd in
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
        
        XLCD_DATAPORT &= 0xF0;              //clear port
        XLCD_DATAPORT |= data&0x0f ;	    //shift left 4 times
        XLCD_ENPIN = 1;
        XLCD_Delay500ns();
        XLCD_ENPIN = 0;
    #endif  



#endif

   return;
}



#ifndef XLCD_RW_GROUND    //need not compile any read command if RWpin grounded

/*********************************************************************
 * Function         :char XLCDIsBusy(void)
 * PreCondition     :None
 * Input            :None
 * Output           :non-zero if LCD controller is ready to accept new
 *                   data or commandzero otherwise.
 * Side Effects     :None
 * Overview         :None
 * Note             :None
 ********************************************************************/
char XLCDIsBusy(void)
{
XLCD_RSPIN=0;
XLCD_RWPIN=1;
XLCD_ENPIN=0;

#ifdef XLCD_8BIT
    XLCD_DATAPORT_TRIS=0xFF;                //make port input    
    XLCD_DATAPORT=0;      
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    
    if(_vXLCDreg==1)                        //will execute only if  called from XLCDInit
    { 
    while(XLCD_DATAPORT&0x80);
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS=0x00;                //make port output
    return;
    }  
      
    #ifdef  XLCD_BLOCK  
    if(_vXLCDreg==0)                        // will execute only if not called from XLCDInit
    {    
    while(XLCD_DATAPORT&0x80);
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS=0x00;                //make port input
    return;
    }
    #endif
    
    
    #ifdef  XLCD_NONBLOCK
    if(_vXLCDreg==0)                        //will execute only if not called from XLCDInit
    {
        if(XLCD_DATAPORT&0x80)              //Read bit 7 (busy bit)
        {   
        XLCD_ENPIN=0;                   
        XLCD_DATAPORT_TRIS=0x00;            //make port op
        return 1;                           //Return TRUE
        }       
        else                                
        {
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS=0x00;            //make port op
        return 0;                           //Return FALSE
        }      
    }
    #endif           
#endif           


#ifdef XLCD_4BIT 
    
    #ifdef  XLCD_UPPER   
    XLCD_DATAPORT_TRIS|=0xF0;               //make upper port input
    XLCD_DATAPORT   &=0x0F;
    XLCD_ENPIN=1;
    XLCD_Delay500ns();    
    if(_vXLCDreg==1)                        // will execute only if  called from XLCDInit
    { 
        while(XLCD_DATAPORT&0x80);
        XLCD_ENPIN=0;
        XLCD_Delay500ns();
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0x0F;           //make upper port output
        return;
    } 
    
    #ifdef  XLCD_BLOCK    
    if(_vXLCDreg==0)                        // When not called from the XLCDInit
    { 
        while(XLCD_DATAPORT&0x80);
        XLCD_ENPIN=0;
        XLCD_Delay500ns();
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0x0F;           //make upper port output
        return;
    }    
    #endif

    #ifdef  XLCD_NONBLOCK    
    if(_vXLCDreg==0)                        // will execute only if not called from XLCDInit
    {
    if(XLCD_DATAPORT&0x80)                  
        {  
        XLCD_ENPIN=0;                                 
        XLCD_Delay500ns();
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0x0F;           //make port output
        return 1;                           //Return TRUE
        }       
    else                                
        {
        XLCD_ENPIN=0; 
        XLCD_Delay500ns();                  // If high
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0x0F;           //make port input
        return 0;                           // Return FALSE
        }      

    }
    #endif     
    #endif      
    
    
    #ifdef  XLCD_LOWER
    XLCD_DATAPORT_TRIS|=0x0F;               //make lower port input
    XLCD_DATAPORT   &=0xF0; 
    XLCD_ENPIN=1;
    XLCD_Delay500ns();    
    if(_vXLCDreg==1)                        // will execute only if  called from XLCDInit
        { 
        while(XLCD_DATAPORT&0x08);
        XLCD_ENPIN=0;
        XLCD_Delay500ns();
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0xF0;           //make port output
        return 0;
        }      
    #ifdef XLCD_BLOCK 
    if(_vXLCDreg==0)                        //will execute only if  called from XLCDInit
        { 
        while(XLCD_DATAPORT&0x08);
        XLCD_ENPIN=0;
        XLCD_Delay500ns();
        XLCD_ENPIN=1;
        XLCD_Delay500ns();
        XLCD_ENPIN=0;
        XLCD_DATAPORT_TRIS&=0xF0;           //make port output
        return 0;
        } 
    #endif
  
    #ifdef XLCD_NONBLOCK 
    if(_vXLCDreg==0)                        // will execute only if  called from XLCDInit
        { 
            if(XLCD_DATAPORT&0x08)                  
            {  
            XLCD_ENPIN=0;                               
            XLCD_Delay500ns();
            XLCD_ENPIN=1;
            XLCD_Delay500ns();
            XLCD_ENPIN=0;
            XLCD_DATAPORT_TRIS=0x00;        //make port input
            return 1;                       // Return TRUE
            }        
        else                                
            {
            XLCD_ENPIN=0; 
            XLCD_Delay500ns();              
            XLCD_ENPIN=1;
            XLCD_Delay500ns();
            XLCD_ENPIN=0;
            XLCD_DATAPORT_TRIS=0x00;        //make port input
            return 0;                       // Return FALSE
            }      

        } 
    #endif
    #endif 
#endif 

}

/*********************************************************************
 * Function         :unsigned char XLCDGetAddr(void)
 * PreCondition     :None
 * Input            :None
 * Output           :Current address byte from LCD
 * Side Effects     :None
 * Overview         :None
 * Note             :The address is read from the character generator
 *                   RAM or display RAM depending on current setup.
 ********************************************************************/

unsigned char XLCDGetAddr(void)

{
char addr =0;
#ifdef  XLCD_BLOCK
    #ifdef  XLCD_DELAYMODE
    XLCDDelay();
    #endif
    #ifdef  XLCD_READBFMODE
    XLCDIsBusy();
    #endif
#endif

XLCD_RSPIN=0;
XLCD_RWPIN=1;
XLCD_ENPIN=0;

#ifdef XLCD_8BIT
    XLCD_DATAPORT_TRIS=0xFF;                //make port input        
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    addr=XLCD_DATAPORT;  
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS=0x00;                //make port input
    return(addr&0x7F);     
#endif        
#ifdef XLCD_4BIT    
    #ifdef  XLCD_UPPER 
    XLCD_DATAPORT_TRIS|=0xF0;               //make upper port input      
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    addr=XLCD_DATAPORT&0xF0;
    XLCD_ENPIN=0;;
    XLCD_Delay500ns();   
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    addr|=(XLCD_DATAPORT>>4)&0x0F;
    XLCD_ENPIN=0;    
    XLCD_DATAPORT_TRIS&=0x0F;               //make upper port output
    return(addr&0x7F);
    #endif  
          
    #ifdef  XLCD_LOWER
    XLCD_DATAPORT_TRIS|=0x0F;               //make lower port input  
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    addr=(XLCD_DATAPORT<<4)&0xF0;
    XLCD_ENPIN=0;    
    XLCD_Delay500ns();
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    addr|=XLCD_DATAPORT&0x0F;
    XLCD_ENPIN=0;    
    XLCD_DATAPORT_TRIS&=0xF0;               //make port output
    return(addr&0x7F);
    #endif  
 
#endif  

}


/*********************************************************************
 * Function         :char XLCDGet(void)
 * PreCondition     :None    
 * Input            :None
 * Output           :Current data byte from LCD
 * Side Effects     :None
 * Overview         :None
 * Note             :The data is read from the character generator
 *                   RAM or display RAM depending on current setup.
 ********************************************************************/
char XLCDGet(void)
{
    char data=0;
#ifdef  XLCD_BLOCK
    #ifdef  XLCD_DELAYMODE
    XLCDDelay();
    #endif
    #ifdef  XLCD_READBFMODE
    XLCDIsBusy();
    #endif
#endif
    XLCD_RSPIN=1;
    XLCD_RWPIN=1;
    XLCD_ENPIN=0;

#ifdef  XLCD_8BIT
    XLCD_DATAPORT_TRIS=0xFF;
    XLCD_ENPIN=1;
    XLCD_Delay500ns(); 
    data=XLCD_DATAPORT;
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS=0x00;
    return(data);
#endif
#ifdef  XLCD_4BIT
    #ifdef  XLCD_UPPER
    XLCD_DATAPORT_TRIS |=0xf0;              //make upper input     
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    data = XLCD_DATAPORT&0xf0;              //Read the upper nibble of data
    XLCD_ENPIN=0;
    XLCD_Delay500ns();
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    data |= ((XLCD_DATAPORT>>4)&0x0f);      //Read the upper nibble of data
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS &=0x0f;              //make output
    return(data);
    #endif
    
    #ifdef  XLCD_LOWER
    XLCD_DATAPORT_TRIS |=0x0F;              //make  input     
    XLCD_ENPIN=1;
    XLCD_Delay500ns();
    data = (XLCD_DATAPORT<<4)&0xf0;         //Read the upper nibble of data
    XLCD_ENPIN=0;
    XLCD_Delay500ns();
    XLCD_ENPIN=1;
    XLCD_Delay500ns();;
    data |= XLCD_DATAPORT&0x0f;             //Read the upper nibble of data
    XLCD_ENPIN=0;
    XLCD_DATAPORT_TRIS &=0xf0;              //make output
    return(data);
    #endif
#endif    
    

}
	
#endif		//end of #ifndef XLCD_RW_GROUND(all read commands)



/*********************************************************************
 * Function         :XLCDPutRomString(rom char *string)
 * PreCondition     :None    
 * Input            :None
 * Output           :Displays string in Program memory
 * Side Effects     :None
 * Overview         :None
 * Note             :is lways blocking till the string is written fully
 ********************************************************************/

void XLCDPutRomString(rom char *string)
{
     while(*string)                         // Write data to LCD up to null
    {    
        #ifdef  XLCD_NONBLOCK
        while(XLCDIsBusy());
        #endif 
        XLCDPut(*string);                   // Write character to LCD
        string++;                           // Increment buffer
    }
    return;
}
/*********************************************************************
 * Function         :XLCDPutRomString(rom char *string)
 * PreCondition     :None    
 * Input            :None
 * Output           :Displays string in Program memory
 * Side Effects     :None
 * Overview         :None
 * Note             :is lways blocking till the string is written fully
 ********************************************************************/
void XLCDPutRamString(char *string)
{
    while(*string)                          // Write data to LCD up to null
    {       
        #ifdef  XLCD_NONBLOCK
        while(XLCDIsBusy());
        #endif
               
        XLCDPut(*string);                   // Write character to LCD
        string++;                           // Increment buffer
    }
    return;
}



