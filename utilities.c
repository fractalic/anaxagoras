// this file contains useful functions that have no other depencies
// do not modify the include list
#ifndef UTIL
#define UTIL

#include "pins.c"

// waitabit
void delay(void);

// num2char(unsigned int)
// convert an integer from 0 to 9
// to its ascii equivalent
char num2char(unsigned int number);

// waitabit
void delay(void)
{
    int j, k;
    for(j=0; j<10; j++)
    {
        for(k=0; k<100; k++);
    }
}

// num2char(unsigned int)
// convert an integer from 0 to 9
// to its ascii equivalent
char num2char(unsigned int number)
{
	return (char)((number % 10) + 48);
}

#endif