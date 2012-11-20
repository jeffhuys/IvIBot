//******************************************************************************
//
// Filename :       Quadrature.h
// Dependencies:    NONE
// Processor:       PIC18, PIC24
// Complier:        MCC18 v3.37 or higher
// Company:         HVA.
// Auther:              Ferry
// Date:            2011-03-11
// Version:         1.0
//
//
//******************************************************************************

#ifndef _QUADRATURE_
#define _QUADRATURE_

#include <p18f4550.h>

struct Quadrature {
    short long      position;
    unsigned char   oldQuad ;
};

void Q_Update(struct Quadrature *qp, unsigned char quad) ;

#endif