void ADC_init() ;
int getAD(char adcselector) ;

#define  AD0SELECTOR 0x03
#define  AD1SELECTOR 0x07
#define  AD2SELECTOR 0x0B
#define  AD3SELECTOR 0x0F

#define  getAD0() getAD(AD0SELECTOR)
#define  getAD1() getAD(AD1SELECTOR)
#define  getAD2() getAD(AD2SELECTOR)
#define  getAD3() getAD(AD3SELECTOR)

