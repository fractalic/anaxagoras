#ifndef PID
#define PID

#include "pins.c"
#include <p89lpc9351.h>

// access the motor speed settings
// (declared in timer.c)
extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;

// (from main.c)
//Inductor names
extern unsigned char inductorL;
extern unsigned char inductorR;

//BlipCountTester
 char BlipCountTester;

// blip detection ---------------------
// get time in hundredths
unsigned int now;
// store blip properties
char low, recent, high;
char blips = 0;
char blip_ready = 0; // ready to detect blip
unsigned int blip_prev_mark = 0; // time of last blip

//  output to motors using pid with lc sensor inputs
void pid(unsigned char, unsigned char); 

// turn robot until line is reached  0 - turn left, 1 - turn right
unsigned char turn(char);

// stop if no signal is detected
char ShouldIStop(void);

// blip detection	
unsigned char CheckSensors (void);

// blipcount()
// determine how many blips have been counted and reset blips to zero
char BlipCount( int );

// readinductors()
// correct for different signal strengths from inductors
void ReadInductors(void);

//Run pid for states
//sensor states
char sensor_left = 0, sensor_right = 0;

// keep track of time
unsigned int time_mark;

// proportional, integral, derivative gains
float kp = 20, ki = 0, kd = 10;

float error = 0, d_error = 0, s_error = 0; // error, derivative of error, integral of error
int error_last, error_step; // record error at last measurement and error at last change
float time = 1, time_step; // track number of interations since the start of this error
// repetive running actions
// checking sensors, etc.



void pid(unsigned char pid_left_setting, unsigned char pid_right_setting) {
	int pid_differential;

	sensor_left = (inductorL > 130) ? 1 : 0;
	sensor_right = (inductorR > 130) ? 1 : 0;

	// set artificial error
	if (sensor_left && sensor_right) error = 0;
	else if (sensor_left && !sensor_right) error = 4; // error = (const) * (inductorL - inductorR)
	else if (!sensor_left && sensor_right) error = -4; // error = (const) * (inductorL - inductorR)
	else {
		if (error_last < 0) error = -5;
		else error = 5;
	}

	// if the error has changed, start measuring the time the error persists
	if (error != error_last) {
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}

	// get current time
	now = millis() / 10.0;

	// run things infrequently
	if (now - time_mark > 50.0) {
		time += 1;
		time_mark = now;
	}

	// find the derivative of the error
	d_error = (float) (error - error_step) / (float) (time + time_step);

	// set PID coefficients
	// using gains
	pid_differential = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;

	// record the error at previous measurement
	error_last = error;

	// TODO: ensure powers are separated by differential, even when one is at full power
	// TODO: make this cleaner
	//set wheel speeds, capping between 0 and 100
	if ( (int) pid_left_setting + (int) pid_differential > 100) {
		drive_left_speed = 100;
	} else if ( (int) pid_left_setting + (int) pid_differential < 0 ) {
		drive_left_speed = 0;
	} else {
		drive_left_speed = pid_left_setting + pid_differential;
	}
	if ( (int) pid_right_setting - (int) pid_differential > 100) {
		drive_right_speed = 100;
	} else if ( (int) pid_right_setting - (int) pid_differential < 0 ) {
		drive_right_speed = 0;
	} else {
		drive_right_speed = pid_right_setting - pid_differential;
	}
}


unsigned char turn(char direction)
{
	/*if (direction = '0') {
		drive_left_speed = 0;
		drive_right_speed = 100;
	} else if (direction = '1') {
		drive_left_speed = 100;
		drive_right_speed = 0;
	}*/

	if(!((inductorL >= 30) && (inductorR >= 30)))
	{
		if(direction = '0')
		{
			drive_left_speed = 0;
			drive_right_speed = 100;
		}
		if(direction = '1')
		{
			drive_left_speed = 100;
			drive_right_speed = 0;
		}	
		return 1;	
	} else {
		return 0;
	}
}

char ShouldIStop(void)
{
	// check for low readings from sensors (track lost)
	if((inductorL <= 5) && (inductorR <= 5) && (inductorM <= 5))
	{
	 	return 1;
	} 
	return 0;
}

// blip detection	
unsigned char CheckSensors (void)	
{
	//TODO: check the thresholds again
	// get time
	now = millis()/10.0;

	// check if we're above or below signal
	// ensure the low and high thresholds are separated (hysteresis)
	low = (inductorM <= 80.0)? 1:0;
	high = (inductorM >= 130.0)? 1:0;
	recent = (now - blip_prev_mark < 55.0)? 1:0;

	// check if we are ready to detect a blip
	if (blip_ready) {
		// blip sensor is high
		if (high) {
			blips++;
			blip_prev_mark = now;
			blip_ready = 0;
			return 9;
		}
	} else {
		// check that signal is decreasing
		if (low) {
			blip_ready = 1;
		}
	}

	return recent;
}

// blipcount()
// determine how many blips have been counted and reset blips to zero
char BlipCount( int instant )
{
	char temp = blips;
	// only return the blip count when we know the blip sequence is finished
	if (low && (!recent || instant)) {
		blips = 0;
		BlipCountTester = temp;
		return temp;
	}

	return 0;
}

// readinductors()
// correct for different signal strengths from inductors
void ReadInductors(void)
{	
	if (inductorLpin * 1.2 <= 255) inductorL = inductorLpin * 1.2;
	inductorR = inductorRpin;
}

#endif