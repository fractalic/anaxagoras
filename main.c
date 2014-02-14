#include <stdlib.h>
#include <stdio.h>
#include <p89lpc9351.h>

// including .c is not usually a good idea,
// but I can't get headers to work
#include "utilities.c"
#include "lcd.c"

#define XTAL 7373000L
#define BAUD 115200L

// initialize the ports to proper I/O mode
void init_ports();

// make some light
void lights(char i);

void this_does_nothing(void) {
// added locally
}
// added globablly
void main(void)
{
	init_ports();
	
	LCD_init();
	
	while(1)
	{
		lights(0x02);
		LCD_write(0x41);
		delay();
		LCD_write(0x42);
		lights(0x01);
		delay();
	}		
}

void init_ports() {
	// set port 1 to quasi-bidirectional
	P1M1 = 0;
	P1M2 = 0;
	// set port 2 to quasi-bidirectional
	P2M1 = 0;
	P2M2 = 0;
}

void lights(char i) {
	// run lights
	P1_3 = (i) & 0x01;
	P1_2 = (i>>1) & 0x01;
}


