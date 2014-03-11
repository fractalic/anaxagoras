#include <stdlib.h>
#include <stdio.h>
#include <p89lpc9351.h>

// include .c files, because crosside gets mad a .h //
// pins should be included in every file
// utilities should probably be included in every file
#include "pins.c"
#include "utilities.c"
#include "lcd.c"
#include "pwm.c"

char time_string[8];
// display the current time on the LCD
void display_time(void);

// initialize the ports to proper I/O mode
void init_ports();

// make some lights flash
void lights(char i);

void main(void)
{
	// set I/O mode of ports and pins on the microcontroller
	init_ports();
	
	// wake up the LCD
	LCD_init();
	
	while(1)
	{
		LCD_cmd(0x01); //clear screen
		lights(0x02);
	//	LCD_write(0x41);
		delay();
	//	LCD_write(0x42);
		LCD_writeString("HI");
		LCD_setCursor(0,4);
		LCD_writeString("HI");
		LCD_setCursor(1,1);
		LCD_writeString("Hello");
		
		lights(0x01);
		delay();
		
		display_time();
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
	light_0 = (i) & 0x01;
	light_1 = (i>>1) & 0x01;
}

// display the current time on the LCD
void display_time()
{
	time_string[0] = (char)(tenths%10);
	time_string[1] = (char)(tenths%100);
	LCD_writeString(time_string);
}

