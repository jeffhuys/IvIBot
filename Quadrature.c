//******************************************************************************
//  
// Filename :       Quadrature.c  
// Dependencies:    Quadrature.h
// Processor:       PIC18, PIC24
// Complier:        MCC18 v3.37 or higher
// Company:         HVA (TI).
// Auther:	        Ferry
// Date:            2011-03-11
// Version:         1.0
//   
// 
//******************************************************************************

#include "osa.h" 

#include "Quadrature.h"

struct Quadrature q1, q2 ;

//  Quadrature encoder implemented as a statemachine
//  The old two bits are the current state only one bit should change
//  into the next state 
//
//  Input: stucture pointyer containing motor position and old bit value
//  Output : Modified structure inc/dec position and new bit value
void Q_Update(struct Quadrature *qp, unsigned char quad) {
   if (quad != qp->oldQuad) {
        // there is rotation
        switch (qp->oldQuad) {
            case 0b00:
                if (quad == 0b01) qp->position++;
                if (quad == 0b10) qp->position--;
                break;
            case 0b01:
                if (quad == 0b11) qp->position++;
                if (quad == 0b00) qp->position--;
                break;
            case 0b10:
                if (quad == 0b00) qp->position++;
                if (quad == 0b11) qp->position--;
                break;
            case 0b11:
                if (quad == 0b10) qp->position++;
                if (quad == 0b01) qp->position--;
                break;
        }
        qp->oldQuad = quad;
    }
}

#ifdef __OSA__
//******************************************************************************
//  Tasks Quadrature
//  Note:  Speed tweaks possible (whitout mem footprint increase)
//******************************************************************************
#define DEBUG
void Task_Quadrature(void) {
	
	q1.position = 0 ;
	q1.oldQuad  = (((PORTD >> 7) & 0b1) | ((PORTD >> 5) & 0b10)) ;
	q2.position = 0 ;
	q2.oldQuad = ((PORTD >> 4) & 0x3) ;

    for (;;) {
        Q_Update(&q1,(((PORTD >> 7) & 0b1) | ((PORTD >> 5) & 0b10)));
        Q_Update(&q2,((PORTD >> 4) & 0x3));

#ifndef DEBUG
		PORTB = q2.position ;
#endif
        OS_Yield();              // Switch context (return to scheduler)
    }
}
#endif
