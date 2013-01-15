#include <includes.h>
#include <stdlib.h>
#include <stdio.h>
#include "RotatingQueue.h"

#define SIZE 50

int internalstack[SIZE];
int nextEmpty = 0, bottomOfStack = 0, numberOfElements = 0;
//int i = 0;

void push(int i) {
    if (isFull()!=1) {
        internalstack[nextEmpty]= i;
        nextEmpty++;
        nextEmpty = nextEmpty%SIZE;
        numberOfElements++;
    }else{
//        printf("FULL\n");
    }
}

int pop(void) {
    if (isEmpty() == 1) {
        return -1;
    } else {
        bottomOfStack++;
        bottomOfStack = bottomOfStack%SIZE;
        numberOfElements--;
        if (bottomOfStack-1 == -1)
            bottomOfStack=SIZE;
        return internalstack[bottomOfStack-1];
    }
}

int peek(void) {
    return internalstack[bottomOfStack];
}

int isEmpty(void) {
    return  numberOfElements == 0 ? 1 : 0;
}

int isFull(void) {
    return numberOfElements == SIZE ? 1 : 0;
}

void clearQueue(void) {
    nextEmpty = 0;
    bottomOfStack = 0;
    for (numberOfElements = 0; numberOfElements < SIZE; numberOfElements++) {
        internalstack[numberOfElements] = 0;
    }
    numberOfElements = 0;
}
//void displayQueue(void){
//    for (i=0; i<SIZE; i++) {
//        printf("%i\n",internalstack[i]);
//    }
//}
