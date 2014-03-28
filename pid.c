#ifndef PID
#define PID

#include "pins.c"
#include <p89lpc9351.h>

// access the motor speed settings
// (declared in timer.c)
extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;

//Inductor names
char inductorL;
char inductorR;

// blip detection ---------------------
// get time in hundredths
unsigned int now;
// store blip properties
char low, recent, high;
char blips = 0;
char blip_ready = 0; // ready to detect blip
unsigned int blip_prev_mark = 0; // time of last blip

// pid control --------------------------
// error, derivative of error, integral of error 
int error = 0, d_error = 0;//, s_error = 0;

int error_last = 0; // record error at last measurement
unsigned short time_diff = 1; // track number of interations since the start of this error

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
char BlipCount( void );

// readinductors()
// correct for different signal strengths from inductors
void ReadInductors(void);

//Run pid for states
void pid(unsigned char pid_left_setting, unsigned char pid_right_setting)
{
	// differential power application
	short pid_differential = 0;

	// get current time
	now = millis() / 10.0;

	// left high is positive
	error = inductorL-inductorR;

	// count time since last change in error state
	if ((error > 0 && error_last <= 0) || (error < 0 && error_last >= 0)) {
		time_diff = 1;
	} else {
		time_diff++;
	}

	//d_error = (error-error_last) / (float) (now - time_last);
	d_error = (error-error_last) / (float) (time_diff);

	// set PID coefficients
	pid_differential = 0.3 * (float) error + 0.1 * (float) d_error;

	// record current error and timestamp for next time
	error_last = error;
	//time_last = now;

	//set wheel speeds
	drive_left_speed = pid_left_setting + pid_differential;
	drive_right_speed = pid_right_setting - pid_differential;

	// cap speeds
	if (drive_left_speed > 100) drive_left_speed = 100;
	if (drive_right_speed > 100) drive_right_speed = 100;
}


unsigned char turn(char direction)
{
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
	// get time
	now = millis()/10.0;

	// check if we're above or below signal
	// ensure the low and high thresholds are separated (hysteresis)
	low = (inductorM <= 80.0)? 1:0;
	high = (inductorM >= 130.0)? 1:0;
	recent = (now - blip_prev_mark < 60.0)? 1:0;

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

// readinductors()
// correct for different signal strengths from inductors
void ReadInductors(void)
{	
	if (inductorLpin * 1.35 <= 255) inductorL = inductorLpin * 1.35;
	inductorR = inductorRpin;
}

#endif