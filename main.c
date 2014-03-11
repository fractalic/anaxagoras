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


//////////////////////////////////////////////////
// from pwm.c
/////////////////////////////////////////////////////


char time_string[8];
// display the current time on the LCD
void display_time(void);

// display the current battery on the LCD
void display_battery(void);

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
	
	// start timer
	timer0_init();
	
	reset_time();
	
	while(1)
	{
		display_time();
		delay();
		LCD_setCursor(0,0);
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
	int seconds = tenths/10;
	int minutes = seconds / 60;
	if (seconds >= 60) seconds-=60;

	time_string[0] = num2char(minutes/10);
	time_string[1] = num2char(minutes);
	time_string[2] = ':';
	time_string[3] = num2char(seconds/10);
	time_string[4] = num2char(seconds);
	time_string[5] = '.';
	time_string[6] = num2char(tenths);
	time_string[7] = '\0';
	LCD_writeString(time_string);
}

// display the current battery on the LCD
void display_battery()
{
	float battery;
	LCD_setCursor(0,1);
	// TO DO: read in from a pins
	// battery = readpin(yyy);
	// lcd_writeString("Battery: " + numtostring(battery));
	
}

