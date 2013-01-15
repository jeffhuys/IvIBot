#include "xlcd.h"
#include "osa.h" 
/*The user  is require to write this 15 milli second delay in his routine,this delay */
/*is required as it is used in XLCDInit() which is used to initialize the LCD module*/

#ifdef __OSA__
void XLCDDelay15ms (void){
    OS_Delay(15)  ;
    return;
}
#else
void XLCDDelay15ms (void){
    int i;
    for(i=0;i<10000;i++) {
    	Nop();
    }
    return;
}
#endif


/*The user  is require to write this 4 milli second delay in his routine,this  delay */
/*is required as it is used in XLCDInit() which is used to initialize the LCD module*/
#ifdef __OSA__
void XLCDDelay4ms (void){
	OS_Delay(4) ;
    return;
}

#else
void XLCDDelay4ms (void){
    int i;
    for(i=0;i<4800;i++){
    	Nop();
    }
    return;
}
#endif
/*The user  is require to write this 500 nano second in his routine  this  delay */
/*is required as it is used in all read and write commaands in the XLCD routines*/

void XLCD_Delay500ns(void) {
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
    Nop();
}
/*The user  is require to write this XLCDDelay() in his routine,this is required to write if */
/*the mode selected is by delay , it is used in all XLCD read and write commands of this routine */
#ifdef __OSA__
void XLCDDelay(void) {
     OS_Delay(3) ;
	return;
}
#else
void XLCDDelay(void) {
    int i;
    for(i=0;i<3000;i++) {
        Nop();
    }
    return;
}
#endif
