#include <includes.h>
#include <stdlib.h>
#include <stdio.h>
#include "Stack.h"

#define SIZE 50

int *tos, *bos, i, internalstack[SIZE];

void stack(void) {
    clearStack();
    tos = internalstack; /* tos points to the top of stack */
    bos = (internalstack + 1); /* bos points to the bottom of stack */
}

void push(int i) {
    tos++;

    if (isFull()) {
        XLCDClear();
        XLCDPutRomString("Stack overflow!");
        OS_Delay(5000);
    } else {
        *tos = i;
    }
}

int pop(void) {
    if (isEmpty() == 1) {
        XLCDClear();
        XLCDPutRomString("Stack underflow!");
        OS_Delay(5000);
    } else {
        bos++;
        return *(bos - 1);
    }
}

int peek(void) {
    return *bos;
}

int isEmpty(void) {
    return tos == (bos-1) ? 1 : 0;
}

int isFull(void) {
    return tos == (bos + SIZE) ? 1 : 0;
}

void clearStack(void) {
    for (i = 0; i < SIZE; i++) {
        internalstack[i] = NULL;
    }
}