#include <stdio.h>
#include <stdlib.h>
#include <p89lpc9351.h>

#define XTAL 7373000L
#define BAUD 115600L

//We want timer 0 to interrupt every 100 microseconds ((1/10000Hz)=100 us)
#define FREQ 10000L
//The reload value formula comes from the datasheet...
#define TIMER0_RELOAD_VALUE (65536L-((XTAL)/(2*FREQ)))

//These variables are used in the ISR
volatile unsigned char pwmcount;
volatile unsigned char pwm1;

//Procedures
void putchar (char c)
{
	while (!TI);
	TI=0;
	SBUF=c;
}

char getchar (void)
{
	while (!RI);
	RI=0;
	return SBUF;
}

void InitSerialPort(void)
{
	BRGCON=0x00; //Make sure the baud rate generator is off
	BRGR1=((XTAL/BAUD)-16)/0x100;
	BRGR0=((XTAL/BAUD)-16)%0x100;
	BRGCON=0x03; //Turn-on the baud rate generator
	SCON=0x52; //Serial port in mode 1, ren, txrdy, rxempty
	P1M1=0x00; //Enable pins RxD and Txd
	P1M2=0x00; //Enable pins RxD and Txd
}

void InitTimer0 (void)
{
	// Initialize timer 0 for ISR 'pwmcounter' below
	TR0=0; // Stop timer 0
	TF0=0; // Clear the overflow flag
	TMOD=(TMOD&0xf0)|0x01; // 16-bit timer
	TH0=TIMER0_RELOAD_VALUE/0x100;
	TL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0
	ET0=1; // Enable timer 0 interrupt
	EA=1;  // Enable global interrupts
}

//Interrupt 1 is for timer 0.  This function is executed every 100 us.
void pwmcounter (void) interrupt 1 using 1
{
	TF0=0; // Clear the overflow flag
	//Reload the timer
	TR0=0; // Stop timer 0
	TH0=TIMER0_RELOAD_VALUE/0x100;
	TL0=TIMER0_RELOAD_VALUE%0x100;
	TR0=1; // Start timer 0
	if(++pwmcount>99) pwmcount=0;
	P1_6=(pwm1>pwmcount)?1:0;
}

void main (void)
{
	InitSerialPort();
	InitTimer0();
	pwm1=20; //50% duty cycle wave at 100Hz
	
}
