#ifndef TIMER
#define TIMER

#include <stdlib.h>
#include <stdio.h>
#include <p89lpc9351.h>

// include .c files, because crosside gets mad a .h //
// pins should be included in every file
// utilities should probably be included in every file
#include "pins.c"

//We want timer 0 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define TIMER0_FREQ 10000L // don't change this from 10000L
//16 bit timer, counting upwards
#define TIMER0_RELOAD_VALUE (65536L-((XTAL)/(2*TIMER0_FREQ)))

//We want timer 1 to interrupt every 10000 microseconds ((1/100Hz)=10000 us)
#define TIMER1_FREQ 100L // don't change this from 100L
//16 bit timer, counting upwards
#define TIMER1_RELOAD_VALUE (65536L-((XTAL)/(2*TIMER1_FREQ)))

//These variables are used in the ISR
volatile unsigned char drive_right_speed;
volatile unsigned char drive_left_speed;

// count timer ticks
volatile char pwm_ticks = 0;
volatile unsigned t1_ticks = 0;

// timer0_init()
// setup the timer0 and begin running it
void Timer0Start();

// millis()
// gets the number of milliseconds since last reset
unsigned millis();

// reset_millis()
// reset the lap timer
void reset_millis();

// freeze_millis()
// freeze the lap timer
void freeze_millis();

// unfreeze_millis()
// restart the lap timer from its current value
void unfreeze_millis();

// timer0_init()
// setup the timer0 and begin running it
void Timer0Start (void)
{
	// Initialize timer 0 for ISR 'pwmcounter' below
	TR0=0; // Stop timer 0
	TF0=0; // Clear the overflow flag

	TMOD=(TMOD&0xf0)|0x01; // 16-bit timer
	
	// load a value into timer0 and restart
	TF0=0; // Clear the overflow flag
	TR0=0; // Stop timer 0
	// load the timer
	TH0=TIMER0_RELOAD_VALUE/0x100; // upper8 bits
	TL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0

	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
}

// crosside got made when I tried to make this a prototype
// timer0_event()
// called whenever the timer overflows
// the time is determind by the frequency defined at the top of this file
void Timer0Tick (void) interrupt 1 using 1
{
	// load a value into timer0 and restart
	TF0=0; // Clear the overflow flag
	TR0=0; // Stop timer 0
	// load the timer
	TH0=TIMER0_RELOAD_VALUE/0x100; // upper8 bits
	TL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0

	// only count 100 ticks before setting to zero
	// (arbitrary, but should be multiple of 10 and 100)
	if(++pwm_ticks>99) pwm_ticks = 0;

	// turn the motors on for the fraction of time specified by
	// X_pwm, as a fraction of 100
	/*if (drive_left) {
		left_wheel=(left_wheel_pwm> (t0_ticks%100))?1:0;
	}
	if (drive_right) {
		right_wheel = (right_wheel_pwm> (t0_ticks%100))?1:0;
	}*/
	
}

// timer1_init()
// setup the timer0 and begin running it
void Timer1Start (void)
{
	// Initialize timer 0 for ISR 'pwmcounter' below
	TR1=0; // Stop timer 0

	TF1=0; // Clear the overflow flag

	TMOD=(TMOD&0x0f)|0x10; // 16-bit timer
	
	// load a value into timer0 and restart
	TF1=0; // Clear the overflow flag
	TR1=0; // Stop timer 0
	// load the timer
	TH1=TIMER1_RELOAD_VALUE/0x100; // upper8 bits
	TL1=TIMER1_RELOAD_VALUE%0x100;
	TR1=1; // Start timer 0


	ET1=1; // Enable timer 1 interrupt
	EA=1;  // Enable global interrupts
}

// timer0_event()
// called whenever the timer overflows
// the time is determind by the frequency defined at the top of this file
void Timer1Tick (void) interrupt 3 using 3
{
	// load a value into timer0 and restart
	TF1=0; // Clear the overflow flag
	TR1=0; // Stop timer 0
	// load the timer
	TH1=TIMER1_RELOAD_VALUE/0x100; // upper8 bits
	TL1=TIMER1_RELOAD_VALUE%0x100;
	TR1=1; // Start timer 0

	t1_ticks++;
}

// millis()
// gets the number of milliseconds since last reset
unsigned millis()
{
	return t1_ticks*10.0;
}

// reset_time()
// reset the global tenths and hundredths counters
void reset_millis()
{
	t1_ticks = 0;
}

// freeze_millis()
// freeze the lap timer
void freeze_millis()
{
	TR1 = 0; // stop timer1
}

// unfreeze_millis()
// restart the lap timer from its current value
void unfreeze_millis()
{
	TR1 = 1;
}

#endif