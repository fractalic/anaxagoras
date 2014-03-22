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

// determine the motor outputs using pid
// 0 - no bias, 1 - left bias, 2 - right bias
void pid(int); 

// determine change state options
void ChangeState(void);

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
			pid(0); //TODO: fix up pid
			ChangeState(); //TODO: write change state thinking maybe something where we pass in number of Xings passed
			//TODO: transition: 4blips -> RStraight
			break;
		case RStraight:
			pid(0);
			// TODO: output: pid
			// TODO: transition: 2?blips -> RRightPrep, 3?blips -> RLeftPrep, 4blips -> RFinish
			break;
		case RRightPrep:
			pid(0);
			// TODO: output: pid
			// TODO: transition: 1blip -> RRight
			break;
		case RRight:
			pid(2);
			// TODO: output: right-biased pid for time or turn right for time
			// TODO: transition: time? -> RStraight
			break;
		case RLeftPrep:
			// TODO: output: pid
			// TODO: transition: 1blip -> RLeft
			break;
		case RLeft:
			pid(2);
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

//Run pid for states
void pid(int bias)
{
	
	//time counting
	int time_init = 0;
	int time_abs = 0;
	int wait = 1; //while wait is 1 we need to wait for signal

	//sensor states
	int sensor_left = 0, sensor_right = 0, sensor_front = 0; //this will be a count of how many perpendicular wires have been observed

	// threshold of signal 
	double threshold_left = 0, threshold_right = 0, threshold_front = 0;

	// proportional, integral, derivative gains
	float kp=0, ki=0, kd=0;

	float error=0, d_error=0, s_error=0; // error, derivative of error, integral of error
	int error_last=-1, error_step=0; // record error at last measurement and error at last change
	int time = 1, time_step=0; // track number of interations since the start of this error

	//float fudge = 10;
	int speed_change = 0;
	int direction_change=0;

	//TODO: set thresholds for whether no, left or right bias. 
	// 0 - no bias, 1 - left bias, 2 - right bias

	// Inputs AD1DAT0, AD1DAT1, AD1DAT2
	//read in from sensors 	
	
	// sppeds for each motor
	drive_right_speed = 0; //set right motor speed (between 0 and 100)
	drive_left_speed = 0; // set left motor speed (between 0 and 100)

	//change the read in functions
	if (inductorL > threshold_left)	sensor_left = 1;
	else sensor_left = 0;
	if (inductorR > threshold_right)sensor_right = 1;
	else sensor_right = 0;

	// set artificial error
	if (sensor_left && sensor_right) error = 0;
	else if (sensor_left && !sensor_right) error = -1; //right is the negative direction
	else if (!sensor_left && sensor_right) error = 1; //left is the positive direction
	else 
	{
		if (error_last > 0) error = 5;
		else error = -5;
	}
	if (error != error_last)
	{
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}

	// find the derivative of the error
	d_error = (float) (error - error_step) / (float) (time + time_step);

	// set PID coefficients
	speed_change = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;

	//increase the time
	time++;

	// record the error at previous measurement
	error_last = error;
	
	//set wheel speeds
	drive_left_speed = drive_left_speed + speed_change;
	drive_right_speed = drive_right_speed - speed_change;
	
}
		
//TODO: write this	
void ChangeState (void)	

{	
/*
	//sensor states
		int sensor_left = 0, sensor_right = 0, sensor_front = 0; //this will be a count of how many perpendicular wires have been observed

		// threshold of signal 
		double threshold_left = 0, threshold_right = 0, threshold_front = 0;
				
		int direction_change=0;
		int time_init = 0;
		int time_abs = 0;
		int wait = 1; //while wait is 1 we need to wait for signal
int time = 1, time_step=0; // track number of interations since the start of this error
		
	

	//check state of the front inductor to store which way to turn if we enter an intersection
	if (inductorM > threshold_front)
	{	
		wait = 1;
		sensor_front = 1;
		time_init = time;
		while(wait == 1)//TODO: Make it so that this counts actual crossings
		{
			if (time-time_init > 500)wait = 0;
			if(inductor_M > threshold_front)
			{
				sensor_front++;
				time_init = time;
			}
		}	
	}
	if (sensor_front == 4) //we are at a start or stop
	{
		if(time == 0)
		{
			reset_millis();	
		}else //TODO: stop clock
		{
			
		}
	}
	else
	{	
		if (sensor_front==3) //turn right
		{	
			wait=1;
			while(wait==1)
			{
				if(sensor_front>threshold_front)
				{
					wait=0;
				}
			}
				direction_change=100;//wait until the next perpendicular line (ie wait till the intersection)	
		}
	    else
		{
			if (sensor_front==2) // turn left!
			{
			wait=1;
			while(wait==1)
			{
				if(sensor_front>threshold_front)
				{
					wait=0;
				}
			}
				direction_change=-100;//wait until the next perpendicular line (ie wait till the intersection)
			}else //lets go straight!
			{
				direction_change=0; //don't change the speed of the wheels
			}
		}
	}
	*/
}


