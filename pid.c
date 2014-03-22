#ifndef PID
#define PID

extern volatile unsigned char drive_right_speed;
extern volatile unsigned char drive_left_speed;

	short error = 0, d_error = 0, s_error = 0; // error, derivative of error, integral of error 
	short error_last=-1, error_step = 0; // record error at last measurement and error at last change
	int time = 1, time_step=0; // track number of interations since the start of this error
	char sensor_left = 0, sensor_right = 0, sensor_front = 0;
	
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
	drive_left_speed = drive_left_speed + speed_change;
	drive_right_speed = drive_right_speed - speed_change;
}

void turn(char direction)
{
	while(!((inductorL >= 100) && (inductorR >= 100)))
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
	}
}

void ShouldIStop(void)
{
	while((inductorL == 0) && (inductorR == 0))
	{
	// do nothing until signal is detected
	} 
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
#endif