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

#define inductor_threshold 40

//  output to motors using pid with lc sensor inputs
void pid(unsigned char); 

// turn robot until line is reached  0 - turn left, 1 - turn right
unsigned char turn(char);

// stop if no signal is detected
char ShouldIStop(void);

// blip detection	
void CheckSensors();

// blipcount()
// determine how many blips have been counted and reset blips to zero
char BlipCount( int );

// BLIP DETECTION VARS ---------------------
// get time in hundredths
unsigned int now;
// store blip properties
char low, recent, high;
char blips = 0;
char blip_ready = 0; // ready to detect blip
unsigned int blip_prev_mark = 0; // time of last blip

// PID VARS ----------------------
//Run pid for states
//sensor states
char sensor_left = 0, sensor_right = 0;

// keep track of time
unsigned int time_mark;

// proportional, integral, derivative gains
float kp = 25, kd = 20;

float error = 0, d_error = 0; // error, derivative of error, integral of error
int error_last, error_step; // record error at last measurement and error at last change
float time = 1, time_step; // track number of interations since the start of this error
// repetive running actions
// checking sensors, etc.

// TURN VARS ----------------------
char turn_low_point = 0;

//ShouldIStop Variables
unsigned int LastStopTime = 0;


void pid(unsigned char pid_setting) {
	int pid_differential;

	// do not set blip reject flag
	// by default
	//*reject = 0;

	sensor_left = (inductorL > inductor_threshold) ? 1 : 0;
	sensor_right = (inductorR > inductor_threshold) ? 1 : 0;

	// set artificial error
	if (sensor_left && sensor_right) error = (0.05) * ((float)inductorR - (float)inductorL);
	else if (sensor_left && !sensor_right) {
		error = (0.30) * ((float)inductorR - (float)inductorL);

		// set blip rejection on sharp turns
		//*reject = 1;
	} else if (!sensor_left && sensor_right) {
		error = (0.30) * ((float)inductorR - (float)inductorL);

		// set blip rejection on sharp turns
		//*reject = 1;
	} else {
		if (error_last > 0) error = 5;
		else error = -5;

		// set blip rejection on sharp turns
		//*reject = 1;
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
	d_error = (float) -(error - error_step) / (float) (time + time_step);

	// set PID coefficients
	// using gains
	pid_differential = (float) kp*(float) error + (float) kd*(float) d_error;

	// record the error at previous measurement
	error_last = error;

	// TODO: ensure powers are separated by differential, even when one is at full power
	// TODO: make this cleaner
	//set wheel speeds, capping between 0 and 100
	if ( (int) pid_setting + (int) pid_differential > 100) {
		drive_left_speed = 100;
	} else if ( (int) pid_setting + (int) pid_differential < 0 ) {
		drive_left_speed = 0;
	} else {
		drive_left_speed = pid_setting + pid_differential;
	}
	if ( (int) pid_setting - (int) pid_differential > 100) {
		drive_right_speed = 100;
	} else if ( (int) pid_setting - (int) pid_differential < 0 ) {
		drive_right_speed = 0;
	} else {
		drive_right_speed = pid_setting - pid_differential;
	}
}

// turn (direction)
// turn until find a new wire
unsigned char turn(char direction)
{
	// power the appropriate wheel
	if (direction == 0) {
		drive_left_speed = 0;
		drive_right_speed = 100;
	} else if (direction == 1) {
		drive_left_speed = 100;
		drive_right_speed = 0;
	}

	// check that we've come away from the first wire
	if (inductorL < 60 || inductorR < 60) {
		turn_low_point = 1;
	}

	// check if back on wire
	if (turn_low_point &&
		(inductorL > 75 && inductorR > 75)) {
		// end turn
		turn_low_point = 0;
		return 0;
	}

	// not finished turning
	return 1;
}

char ShouldIStop(void)
{
	// check for low readings from sensors (track lost)
	now = millis()/10.0;
	if((inductorL <= 5) && (inductorR <= 5) && (inductorM <= 5))
	{
		if((now - LastStopTime)> 200)	
		{
	 		return 1;
	 	}
	 	return 0;
	}
	// reset timer
	LastStopTime = now;
	return 0;
}

// blip detection	
void CheckSensors ()	
{
	//TODO: check the thresholds again
	// get time
	now = millis()/10.0;

	// check if we're above or below signal
	// ensure the low and high thresholds are separated (hysteresis)
	low = (inductorM <= 70.0)? 1:0;
	high = (inductorM >= 190.0)? 1:0;
	recent = (now - blip_prev_mark < 60.0)? 1:0;

	// check if we are ready to detect a blip
	if (blip_ready) {
		// blip sensor is high
		if (high && inductorL > 50 && inductorR > 50) {
			// do not associate distant blips
			blips++;
			blip_prev_mark = now;
			blip_ready = 0;
		}
	} else {
		// check that signal is decreasing
		if (low && recent) {
			blip_ready = 1;
		}
	}

	// calibrate readings from L, R inductors
	if (inductorLpin * 1.2 <= 255) inductorL = inductorLpin * 1.2;
	inductorR = inductorRpin;
}

// blipcount()
// determine how many blips have been counted and reset blips to zero
char BlipCount( int instant )
{
	char temp;

	temp = blips;
	
	// only return the blip count when we know the blip sequence is finished
	if ((low && !recent) || instant || blips >= 4) {
		blips = 0;
		blip_ready = 1;
		return temp;
	}

	return 0;
}

#endif