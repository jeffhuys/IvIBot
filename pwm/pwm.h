#ifndef PWM_H
#define PWM_H

#include "includes.h"

extern void ADC_init(void);
extern void PWM_init(void);
extern void RightPWM(int pwmDuty, int threshold) ;
extern void LeftPWM(int pwmDuty, int threshold) ;

extern void setPR2_REG(BYTE);
extern void setT2CON_REG(BYTE);
extern void setCCP1_MODE_REG(BYTE);
extern void setCCP2_MODE_REG(BYTE);
extern void setCCPR1L_REG(BYTE);
extern void setCCPR2L_REG(BYTE);

extern BYTE getPR2_REG(void);
extern BYTE getT2CON_REG(void);
extern BYTE getCCP1_MODE_REG(void);
extern BYTE getCCP2_MODE_REG(void);
extern BYTE getCCPR1L_REG(void);
extern BYTE getCCPR2L_REG(void);

#endif
