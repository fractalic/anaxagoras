// this file contains useful functions that have no other depencies
// do not modify the include list
#ifndef UTIL
#define UTIL

#include "pins.c"

// waitabit
void delay(void);

// waitabit
void delay(void)
{
    int j, k;
    for(j=0; j<100; j++)
    {
        for(k=0; k<1000; k++);
    }
}
#endif