#include <stdio.h>
#include <p89lpc9351.h>
#include <string.h>

// include .c files, because crosside gets mad at .h //
// pins should be included in every file
// utilities should probably be included in every file
#include "pins.c"
#include "utilities.c"
#include "lcd.c"
#include "timer.c"
#include "pid.c"

// rover state machine information
enum {RStart = 0, RStraight, RRightPrep, RRight, RLeftPrep, RLeft, RFinish, RTest} RobotState_t;
unsigned char robot_state = RStart;

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

// add an offset to the inductors
//void ReadInductors(void);

// count iterations of the main control sequence
unsigned char loopcount = 0;

// timer control (from timer.c)
// access the motor speed settings
extern volatile unsigned char drive_right_speed, drive_left_speed;

// pid control (from pid.c)
// error, derivative of error, integral of error
extern float error, d_error, s_error;

//Inductor names
unsigned char inductorL;
unsigned char inductorR;

// count blips
char blip_count = 0;

// count first blip we see
// (for turns)
char instant = 0;

// reject blips when making sharp turns
//char reject = 0;

void main(void)
{
	// set I/O mode of ports and pins on the microcontroller
	InitPorts();
	
	// set analog inputs
	InitADC();
	
	// wake up the LCD
	InitLCD();
	
	// start timers
	Timer0Start();
	Timer1Start();
	
	reset_millis();
	
	while(1)
	{
		// check the sensors as often as possible
		CheckSensors();

		// don't refresh the display all the time
		if (loopcount%100==0) {
			DisplayInfo();
		}
		// don't change state all the time
		if (loopcount%5 == 0) {
			StateMachine();
		}

		if(++loopcount>200) loopcount = 0;
	}		
}

void InitPorts() {
	// set port 0 to quasi-bidirectional
	P0M1 = 0;
	P0M2 = 0;
	// set port 1 to quasi-bidirectional
	P1M1 = 0;
	P1M2 = 0;
	// set port 2 to quasi-bidirectional
	P2M1 = 0;
	P2M2 = 0;
	// set port 3 to quasi-bidirectional
	P3M1 = 0;
	P3M2 = 0;
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

// DisplayInfo()
// show lap time, battery and status information on the screen
void DisplayInfo()
{
	// two display lines
	xdata char top_line[17];
	xdata char bottom_line[17];

	unsigned time = millis()/10.0;
	xdata float seconds = time/100.0;
	xdata int minutes = time / 6000.0;

	// write lap time, state, other stuff
	if (seconds >= 60.0) seconds-=minutes*60.0;
	//sprintf(top_line, "%01d:%04.01f %1d %02d %02d", minutes, seconds,
	sprintf(top_line, "%03d:%03d  %3u:%3u",
		(int)inductorL, (int)inductorR,
		(unsigned int)drive_left_speed, (unsigned int)drive_right_speed);
	//LCD_setCursor(0,0);
	//LCD_writeString("                ");
	LCD_setCursor(0,0);
	LCD_writeString(top_line);

	// write battery level and inductor readings
	sprintf(bottom_line,"M%03d   R%1d B%02d S%1d",
		//commented for pid testing
		//(int)error, (int) s_error, (int)d_error);
		//for blip testing
		(int)inductorM, (int)blip_ready, (int) blips, (int) robot_state);
	//LCD_setCursor(0,1);
	//LCD_writeString("                ");
	LCD_setCursor(0,1);
	LCD_writeString(bottom_line);
}

// statemachine
// control the current state of the robot
void StateMachine()
{
	// TODO: get stopping working
	if (!ShouldIStop()) {

		blip_count = BlipCount(instant);
		// go on next
		instant = 0;
		// state transitions
		switch (robot_state) {
			case RStart:
				pid(100);
				//ShouldIStop();
				if (blip_count >= 4) {
					reset_millis();
					robot_state = RStraight;
				}
				break;
			case RStraight:
				pid(100);
				// check if we should get ready to turn
				if (blip_count == 3) robot_state = RRightPrep;
				else if (blip_count == 2) robot_state = RLeftPrep;
				else if (blip_count == 4) robot_state = RFinish;
				break;
			case RRightPrep:
				instant = 1;
				pid(50);
				// turn when intersection detected
				if (blip_count == 1) robot_state = RRight;
				break;
			case RRight:
				// turns right until hits wire 
				if (!turn(1)) robot_state = RStraight;
				break;
			case RLeftPrep:
				instant = 1;
				pid(50);
				//ShouldIStop();
				// turn when intersection detected
				if (blip_count == 1) robot_state = RLeft;
				break;
			case RLeft:
			 	// turns left until hits wire
				if (!turn(0)) robot_state = RStraight;
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
	} else {
		// stop the robot
		drive_left_speed = 0; // speed 10 does not turn wheels
		drive_right_speed = 0;
	}
}
