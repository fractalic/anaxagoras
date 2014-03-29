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
int error = 0, d_error = 0, s_error = 0;

int error_delta_start = 0; // record error at last measurement
int time_delta_start = 0; // track time since derivative update

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

	// compute errors
	error = (inductorL-inductorR);

	// update derivative error and integral error
	// no more frequently than known delta time
	if (now - time_delta_start > 5.0) {
		// compute the errors over the delta time
		d_error = error_delta_start-error;
		s_error += error;

		if (s_error < 0) s_error -= 3;
		else s_error += 3;

		// we've started the next interval,
		// record starting parameters
		error_delta_start = error;
		time_delta_start = now;
	}

	// dead zone to prevent the errors from changing sign rapidly
	// when the signal from the two inductors is nearly the same
	if (error > -2 && error < 2) {
		// probably off wire, boost integral error
		//s_error = error*100;
		error = 0;
	}

	// reset integral error when we cross the wire
	if ((float)error * (float)error_delta_start < 0) {
		// reset integral error counter
		s_error = 0;
	}

	// determine the differential power to apply
	pid_differential = 0.30 * error + 0.3 * s_error + 1 * d_error;

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
	// TODO: fix this logic
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
	recent = (now - blip_prev_mark < 90.0)? 1:0;

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
	if (inductorLpin * 1.2 <= 255) inductorL = inductorLpin * 1.2;
	inductorR = inductorRpin;
}

#endif