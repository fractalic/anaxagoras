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

typedef enum {RStart, RStraight, RRightPrep, RRight, RLeftPrep, RLeft, RFinish, RTest} RobotState_t;
RobotState_t RobotState = RTest;

char time_string[12];

// display the current time on the LCD
void display_time(void);

// display the current battery on the LCD
void display_battery(void);

// initialize the ports to proper I/O mode
void init_ports();

// initializa analogue inputs
void InitADC(void);

// make some lights flash
void lights(char i);

void main(void)
{
	// set I/O mode of ports and pins on the microcontroller
	init_ports();
	
	// set analog inputs
	InitADC();
	
	// wake up the LCD
	LCD_init();
	
	// start timer
	timer0_init();
	
	reset_millis();
	
	while(1)
	{
		display_time();
		display_battery();
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
	/*int seconds = millis()/1000;
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
	LCD_writeString(time_string);*/
	
	long time = millis();
	long seconds = time/1000.0;
	long minutes = seconds / 60.0;
	if (seconds >= 60.0) seconds-=minutes*60.0;
	
	sprintf(time_string,"%li XX %li:%li",time,minutes,seconds);
	LCD_writeString(time_string);
}

// display the current battery on the LCD TODO: TEST THIS
void display_battery()
{

	//batterypin = AD1DAT3;
	//char battery_string[4];	
	int battery = AD1DAT3*5.0/255/1.2927-0.2439;
	int batterydec = AD1DAT3*50.0/255/1.2927-0.2439-battery*10;

	
	char str[4];
	char strdec[4];
    sprintf(str, "%d", battery);
    sprintf(strdec, "%d", batterydec);
	LCD_setCursor(0,1);
	//battery_string[0] = num2char(battery);
	//battery_string[1] = '.';
	//battery_string[2] = num2char(batterydec);
	//battery_string[3] = '\0';
	LCD_writeString("Battery: ");
<<<<<<< HEAD
	//LCD_writeString(battery_string);	
	LCD_writeString(str);
	LCD_writeString(".");
	LCD_writeString(strdec);
=======
	LCD_writeString(battery_string);
>>>>>>> 463747a8a977fc2d75bbbfb958516e3428ce5e08
}

// statemachine
// control the current state of the robot
void statemachine()
{
	// state transitions
	switch (RobotState) {
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

void InitADC(void)
{
	// Set adc1 channel pins as input only 
	P0M1 |= (P0M1_4 | P0M1_3 | P0M1_2 | P0M1_1);
	P0M2 &= ~(P0M1_4 | P0M1_3 | P0M1_2 | P0M1_1);

	BURST1 = 1; //Autoscan continuos conversion mode
	ADMODB = CLK0; //ADC1 clock is 7.3728MHz/2
	ADINS  = (ADI13|ADI12|ADI11|ADI10); // Select the four channels for conversion
	ADCON1 = (ENADC1|ADCS10); //Enable the converter and start immediately
	while((ADCI1&ADCON1)==0); //Wait for first conversion to complete
}
