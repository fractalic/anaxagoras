#include <stdio.h>
#include <p89lpc9351.h>

// include .c files, because crosside gets mad at .h //
// pins should be included in every file
// utilities should probably be included in every file
#include "pins.c"
#include "utilities.c"
#include "lcd.c"
#include "timer.c"
#include "pid.c"

// rover state machine information
typedef enum {RStart = 0, RStraight, RRightPrep, RRight, RLeftPrep, RLeft, RFinish, RTest} RobotState_t;
RobotState_t robot_state = RTest;

// DisplayInfo()
// show lap time, battery and status information on the screen
void DisplayInfo();

// initialize the ports to proper I/O mode
void InitPorts();

// initadc()
// set up adc 1, with four input channels
void InitADC(void);

// statemachine
// control the current state of the rover
void StateMachine();

// make some lights flash
void lights(char i);

//  output to motors using pid with lc sensor inputs
void pid(void); 

// turn robot until line is reached  0 - turn left, 1 - turn right
void turn(char);

// stop if no signal is detected
void ShouldIStop(void);

// determine change state options
void ChangeState(void);

// count iterations of the main control sequence
int loopcount = 0;

void main(void)
{
	// set I/O mode of ports and pins on the microcontroller
	InitPorts();
	
	// set analog inputs
	InitADC();
	
	// wake up the LCD
	InitLCD();
	
	// start timer
	Timer0Start();
	Timer1Start();
	
	reset_millis();
	
	while(1)
	{
		// don't refresh the display all the time
		if (++loopcount>19) {
			loopcount = 0;
			DisplayInfo();
		}
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


// set up adc 1, with four input channels
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

void lights(char i) {
	// run lights
	/*light_0 = (i) & 0x01;
	light_1 = (i>>1) & 0x01;*/
	i;
}

// DisplayInfo()
// show lap time, battery and status information on the screen
void DisplayInfo()
{
	// compute lap time
	char time_string[8];
	unsigned time = millis();
	float seconds = time/1000.0;
	short minutes = seconds / 60.0;

	// read pins and convert to voltage values
	char battery_string[20];

	// store string representation of current state
	char state_string[2];

	// write lap time to display
	LCD_setCursor(0,0);
	if (seconds >= 60.0) seconds-=minutes*60.0;
	sprintf(time_string,"%1li:%05.02f",minutes,seconds);
	LCD_writeString(time_string);

	// write current state to display
	LCD_setCursor(9,0);
	sprintf(state_string,"%2d",(int)robot_state);
	LCD_writeString(state_string);

	// write battery indicator to display
	LCD_setCursor(0,1);
	sprintf(battery_string,"%3.1f,%3.1f,%3.1f,%3.1f", 5.0 * (inductorL / 255.0), 5.0 * (inductorM / 255.0), 5.0 * (inductorR / 255.0), 5.0 * (battery / 255.0));
	LCD_writeString(battery_string);
}

// statemachine
// control the current state of the robot
void StateMachine()
{
	// state transitions
	switch (robot_state) {
		case RStart:
			pid(); 
			ShouldIStop();
			ChangeState(); //TODO: write change state thinking maybe something where we pass in number of Xings passed
			//TODO: transition: 4blips -> RStraight
			break;
		case RStraight:
			pid();
			ShouldIStop();
			// TODO: transition: 2?blips -> RRightPrep, 3?blips -> RLeftPrep, 4blips -> RFinish
			break;
		case RRightPrep:
			pid();
			ShouldIStop();
			// TODO: transition: 1blip -> RRight
			break;
		case RRight:
			turn(1); // turns right until hits wire 
			// TODO: transition: time? -> RStraight
			break;
		case RLeftPrep:
			pid();
			ShouldIStop();
			// TODO: transition: 1blip -> RLeft
			break;
		case RLeft:
			turn(0); // turns left until hits wire
			// TODO: transition: time? -> RStraight
			break;
		case RFinish:
			drive_left_speed = 0;
			drive_right_speed = 0;
			//TODO: do we need a reset?
			break;
		case RTest:
			// TODO: output test stuff
		default:
			// do nothing
	}
}