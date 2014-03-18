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

typdef enum {RStart, RStraight, RRightPrep, RRight, RLeftPrep, RLeft, RFinish, RTest} RobotState_t;
RobotState_t RobotState = RTest;

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
	
	reset_millis();
	
	while(1)
	{
		display_time();
		display_battery();
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
	int seconds = millis()/1000;
	int minutes = seconds / 60;
	if (seconds >= 60) seconds-=minutes*60;

	time_string[0] = num2char(minutes/10);
	time_string[1] = num2char(minutes);
	time_string[2] = ':';
	time_string[3] = num2char(seconds/10);
	time_string[4] = num2char(seconds);
	time_string[5] = '.';
	time_string[6] = num2char(millis()/100);
	time_string[7] = '\0';
	LCD_writeString(time_string);
}

// display the current battery on the LCD TODO: TEST THIS
void display_battery()
{
	char battery_string[3];
	int battery = batterypin*5/1048;
	int batterydec = batterypin*5/10480;
	
	LCD_setCursor(0,1);
	battery_string[0] = num2char(battery);
	battery_string[1] = '.';
	battery_string[2] = num2char(batterydec);
	LCD_writeString("Battery: ");
	LCD_writeString(battery_string);		
}

// statemachine
// control the current state of the robot
void statemachine()
{
	// state transitions
	switcth (RobotState) {
		case RStart:
			// TODO: output: pid
			// TODO: transition: 4blips -> RStraight
			break;
		case RStraight:
			// TODO: output: pid
			// TODO: transition: 2?blips -> RRightPrep, 3?blips -> RLeftPrep, 4blips -> RFinish
			break;
		case RRightPrep:
			// TODO: output: pid
			// TODO: transition: 1blip -> RRight
			break;
		case RRight:
			// TODO: output: right-biased pid for time or turn right for time
			// TODO: transition: time? -> RStraight
			break;
		case RLeftPrep:
			// TODO: output: pid
			// TODO: transition: 1blip -> RLeft
			break;
		case RLeft:
			// TODO: output: left-biased pid for time or turn left for time
			// TODO: transition: time? -> RStraight
			break;
		case RFinish:
			// TODO: output: stop driving
			break;
		case RTest:
			// TODO: output test stuff
		default:
			// do nothing
	}
}
