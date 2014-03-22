#include <string.h>
#include <stdio.h>
#include <p89lpc9351.h>

// include .c files, because crosside gets mad at .h //
// pins should be included in every file
// utilities should probably be included in every file
#include "pins.c"
#include "utilities.c"
#include "lcd.c"
#include "timer.c"

// rover state machine information
typedef enum {RStart = 0, RStraight, RRightPrep, RRight, RLeftPrep, RLeft, RFinish, RTest} RobotState_t;
RobotState_t RobotState = RTest;
const char *state_names[8] ={ "St", "stgt", "rpr", "rtn", "lpr", "ltn", "fn","tst" };

// DisplayInfo()
// show lap time, battery and status information on the screen
void DisplayInfo();

// initialize the ports to proper I/O mode
void InitPorts();

// initialize analogue inputs
void InitADC(void);

// statemachine
// control the current state of the rover
void StateMachine();

// make some lights flash
void lights(char i);

// make the robot move using pid
void pid(void);

void main(void)
{
	// set I/O mode of ports and pins on the microcontroller
	InitPorts();
	
	// set analog inputs
	InitADC();
	
	// wake up the LCD
	LCD_init();
	
	// start timer
	Timer0Start();
	Timer1Start();
	
	reset_millis();
	
	while(1)
	{
		DisplayInfo();
		delay();
	}		
}

void InitPorts() {
	// set port 1 to quasi-bidirectional
	P1M1 = 0;
	P1M2 = 0;
	// set port 2 to quasi-bidirectional
	P2M1 = 0;
	P2M2 = 0;
}

void lights(char i) {
	// run lights
	/*light_0 = (i) & 0x01;
	light_1 = (i>>1) & 0x01;*/
}

// DisplayInfo()
// show lap time, battery and status information on the screen
void DisplayInfo()
{
	// Lap time settings
	char time_string[12];
	long time = millis();
	float seconds = time/1000.0;
	long minutes = seconds / 60.0;

	// battery level settings
	char battery_string[20];
	float battery_d = 5.0 * (battery / 255.0); // TODO: Test that this works

	// current state display
	char state_string[6];

	// write lap time to display
	LCD_setCursor(0,0);
	if (seconds >= 60.0) seconds-=minutes*60.0;
	sprintf(time_string,"%li:%05.02f",minutes,seconds);
	LCD_writeString(time_string);

	// write current state to display
	LCD_setCursor(9,0);
	strcpy(state_string,state_names[0]);

	// write battery indicator to display
	LCD_setCursor(0,1);
	sprintf(battery_string,"0x%02x,0x%02x,0x%02x",AD1DAT0, AD1DAT1, AD1DAT2);
	LCD_writeString(battery_string);
}

// statemachine
// control the current state of the robot
void StateMachine()
{
	// state transitions
	switch (RobotState) {
		case RStart:
			pid();
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

void pid(void)
{
}