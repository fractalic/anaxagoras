#ifndef PID
#define PID

// access the motor speed settings
// (declared in timer.c)
/*extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;*/

// blip detection ---------------------
// get time in hundredths
int now;
// store blip properties
char low, recent;
char derivative;
char blips = 0;
char blip_prev_level; // value of previous blip
char blip_ready = 0; // ready to detect blip
int blip_prev_mark = 0; // time of last blip

// pid control --------------------------
char error = 0, d_error = 0, s_error = 0; // error, derivative of error, integral of error 
char error_last=-1, error_step = 0; // record error at last measurement and error at last change
int time = 1, time_step=0; // track number of interations since the start of this error

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
	int kp = 0, ki = 0, kd = 0;
	short speed_change = 0;

	//TODO: set thresholds for whether no, left or right bias. 
	// 0 - no bias, 1 - left bias, 2 - right bias

	/*
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
	*/
	error = inductorR-inductorL;
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
	//drive_left_speed = drive_left_speed + speed_change;
	//drive_right_speed = drive_right_speed - speed_change;
	drive_left_speed = 50;
	drive_right_speed = 20;
}


unsigned char turn(char direction)
{
	if(!((inductorL >= 100) && (inductorR >= 100)))
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
	if((inductorL <= 5) && (inductorR <= 5) && (inductorM <= 5))
	{
	 	return 1;
	} 
	return 0;
}

// blip detection	
void CheckSensors (void)	
{
	// get time
	now = millis()/10.0;

	// check if we're above or below signal
	low = (inductorM <= 100)? 1:0;
	recent = (now - blip_prev_mark < 200)? 1:0;
	derivative = inductorM - blip_prev_level;

	// check if we are ready to detect a blip
	if (blip_ready) {
		// blip sensor is high
		if (!low) {
			blips++;
			blip_prev_mark = now;
			blip_ready = 0;
		}
	} else {
		// check that signal is decreasing
		if (low && derivative < 0) {
			blip_ready = 1;
		}
	}
}

// blipcount()
// determine how many blips have been counted and reset blips to zero
char BlipCount( void )
{
	// only return the blip count when we know the blip sequence is finished
	if (!recent && low) {
		return blips;
	}

	return 0;
}

#endif