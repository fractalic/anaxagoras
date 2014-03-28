#ifndef PID
#define PID

#include "pins.c"
#include <p89lpc9351.h>

// access the motor speed settings
// (declared in timer.c)
extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;

// blip detection ---------------------
// get time in hundredths
unsigned int now;
// store blip properties
char low, recent, high;
char derivative;
char blips = 0;
char blip_prev_level; // value of previous blip
char blip_ready = 0; // ready to detect blip
unsigned int blip_prev_mark = 0; // time of last blip

// pid control --------------------------
char error = 0;//, d_error = 0, s_error = 0; // error, derivative of error, integral of error 
char error_last=-1, error_step = 0; // record error at last measurement and error at last change
int time = 1, time_step=0; // track number of interations since the start of this error
char drive_left_setting = 0, drive_right_setting = 0;

//  output to motors using pid with lc sensor inputs
void pid(void); 

// turn robot until line is reached  0 - turn left, 1 - turn right
unsigned char turn(char);

// stop if no signal is detected
char ShouldIStop(void);

//Run pid for states
void pid(void)
{	
	// threshold of signal 
	int threshold_left = 100, threshold_right = 100, threshold_front = 0; //TODO: Test that these value work

	// proportional, integral, derivative gains
	float kp = 0.3, ki = 0, kd = 0.0; //TEST this
	short speed_change = 0;

	//TODO: set thresholds for whether no, left or right bias. 
	// 0 - no bias, 1 - left bias, 2 - right bias

	error = inductorR-inductorL;
	if (error != error_last)
	{
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}
	 
	// find the derivative of the error
	//d_error = (float) (error - error_step) / (float) (time + time_step);

	// set PID coefficients
	speed_change = (float) kp*(float) error;// + (float) ki*(float) s_error + (float) kd*(float) d_error;

	//increase the time
	time++;

	// record the error at previous measurement
	error_last = error; 
	
	//set wheel speeds
	drive_left_speed = drive_left_setting + speed_change;
	drive_right_speed = drive_right_setting - speed_change;
	drive_right_setting = 50;
	drive_left_setting = 50;
}


unsigned char turn(char direction)
{
	if(!((inductorL >= 30) || (inductorR >= 30)))
	{
		if(direction = '0')
		{
			drive_left_speed = 100;
			drive_right_speed = 0;
		}
		if(direction = '1')
		{
			drive_left_speed = 0;
			drive_right_speed = 100;
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
	// get time
	now = millis()/10.0;

	// check if we're above or below signal
	// ensure the low and high thresholds are separated (hysteresis)
	low = (inductorM <= 80.0)? 1:0;
	high = (inductorM >= 130.0)? 1:0;
	recent = (now - blip_prev_mark < 90.0)? 1:0;
	//derivative = inductorM - blip_prev_level;
	blip_prev_level = inductorM;

	// check if we are ready to detect a blip
	if (blip_ready) {
		// blip sensor is high
		if (high) {
			blips++;
			blip_prev_mark = millis()/10;
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
char BlipCount( void )
{
	char temp = blips;
	// only return the blip count when we know the blip sequence is finished
	if (low && !recent) {
		blips = 0;
		return temp;
	}

	return 0;
}

#endif