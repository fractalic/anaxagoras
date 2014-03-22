#ifndef PID
#define PID

// access the motor speed settings
// (declared in timer.c)
extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;

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

	int speed_change = 0;
	int direction_change=0;

	//TODO: set thresholds for whether no, left or right bias. 
	// 0 - no bias, 1 - left bias, 2 - right bias

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

char blips = 0;
const char blip_threshold_upward = 100; // threshold to begin checking for blip
const char blip_threshold_downward = 100; // threshold where we assume we've passed the blip
unsigned blip_high_time = 0; // time of most recent blip
unsigned blip_low_time = 0; // time of most recent signal drop
char blip_ready = 0; // ready to detect blip
char blip_length = 10; // minimum length in hundredths of a second for blip confirmation
char blip_pattern_length = 10; // minimum length in hundredths of a second for blip signal drop

// blip detection	
void CheckSensors (void)	
{
	char recent = 0; // was there a blip recently
	unsigned now = millis();

	// check if we are ready to detect a blip
	if (blip_ready) {
		// blip sensor is high and has been that way for a while
		if (inductorM > blip_threshold_upward) {
			if (now - blip_prev_time > blip_length) {
				blip++;
				blip_prev_time = now;
				blip_ready = 0;
			}
		}
	} else {
		// check the length of signal decrease
		if (inductorM < blip_threshold_downward) {
			if (now - blip_prev_time > blip_length_low) {
				blip_ready = 1;
			} else {
				blip_low_time = now;
			}
		}
	}
}
#endif