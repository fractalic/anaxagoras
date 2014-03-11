#include <stdio.h>
#include <stdlib.h>
#include <p89lpc9351.h>

#define XTAL 7373000L
#define BAUD 115600L

//We want timer 0 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define TIMER0_FREQ 10000L
//16 bit timer, counting upwards
#define TIMER0_RELOAD_VALUE (65536L-((XTAL)/(2*TIMER0_FREQ)))

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char pwm1;

void timer0_init (void)
{
	// Initialize timer 0 for ISR 'pwmcounter' below
	TR0=0; // Stop timer 0
	TF0=0; // Clear the overflow flag

	TMOD=(TMOD&0xf0)|0x01; // 16-bit timer
	
	// load a value into timer0 and restart
	timer0_restart();

	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
}

// load a time value into the timer
void timer0_restart()
{
	TF0=0; // Clear the overflow flag
	
	TR0=0; // Stop timer 0

	// load the timer
	TH0=TIMER0_RELOAD_VALUE/0x100; // upper8 bits
	TL0=TIMER0_RELOAD_VALUE%0x100;

	TR0=1; // Start timer 0
}

//bind this to interrupt 1 (timer 0)
void timer0_event (void) interrupt 1 using 1
{
	// load the timer and start it
	timer0_restart();

	// count timer interrupts
	if(++pwmcount>99) pwmcount=0;

	P1_6=(pwm1>pwmcount)?1:0;
}

void main (void)
{
	timer0_init();
	pwm1=20; //50% duty cycle wave at 100Hz
}
