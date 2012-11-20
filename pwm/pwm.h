#ifndef PWM_H
#define PWM_H

extern void ADC_init(void);
extern void PWM_init(void);
extern void RightPWM(int pwmDuty, int threshold) ;
extern void LeftPWM(int pwmDuty, int threshold) ;

#endif
