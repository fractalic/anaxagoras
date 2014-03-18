#ifndef PWM
#define PWM

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

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char left_wheel_pwm;
volatile unsigned char right_wheel_pwm;

// count timer0 ticks (every 100us)
volatile unsigned int t0_ticks = 0;
volatile long millis_v;

// TODO: set these in the state machine
short int drive_right = 0;
short int drive_right_speed = 0;
short int drive_left = 0;
short int drive_left_speed = 0;

// timer0_init()
// setup the timer0 and begin running it
void timer0_init();

// timer0_restart()
// stop, load a time value, and start timer0
void timer0_restart();

// millis()
// gets the number of milliseconds since last reset
long millis();

// reset_millis()
// reset the global tenths and hundredths counters
void reset_millis();

// crosside got made when I tried to make this a prototype
// timer0_event()
// called whenever the timer overflows
// the time is determind by the frequency defined at the top of this file
void timer0_event (void) interrupt 1 using 1
{
	// load the timer and start it
	timer0_restart();

	// only count 100 ticks before setting to zero
	// (arbitrary, but should be multiple of 10 and 100)
	if(++t0_ticks>99) t0_ticks=0;

	// turn the motors on for the fraction of time specified by
	// X_pwm, as a fraction of 100
	/*if (drive_left) {
		left_wheel=(left_wheel_pwm> (t0_ticks%100))?1:0;
	}
	if (drive_right) {
		right_wheel = (right_wheel_pwm> (t0_ticks%100))?1:0;
	}*/
	
	// count milliseconds (every ten 100us timer ticks) 
	if( ((t0_ticks)%10) == 0 ) {
		millis_v++;
	}
	
}

// timer0_init()
// setup the timer0 and begin running it
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

// timer0_restart()
// stop, load a time value, and start timer0
void timer0_restart()
{
	TF0=0; // Clear the overflow flag
	
	TR0=0; // Stop timer 0

	// load the timer
	TH0=TIMER0_RELOAD_VALUE/0x100; // upper8 bits
	TL0=TIMER0_RELOAD_VALUE%0x100;

	TR0=1; // Start timer 0
}

// millis()
// gets the number of milliseconds since last reset
long millis()
{
	long interim = millis_v;
	return interim;
}

// reset_time()
// reset the global tenths and hundredths counters
void reset_millis()
{
	millis_v = 0;
}

#endif