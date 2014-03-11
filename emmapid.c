/* this is a digital pid algorithm,
obtained from analog inputs with a threshold */

//time counting
int time_init=0;
int time_abs=0;
int wait=1; //while wait is 1 we need to wait for signal

//sensor states
int sensor_left = 0, sensor_right = 0, sensor_front = 0; //this will be a count of how many perpendicular wires have been observed

// threshold of signal 
double threshold_left = 0, threshold_right = 0, threshold_front = 0;

// proportional, integral, derivative gains
float kp=0, ki=0, kd=0;

float error=0, d_error=0, s_error=0; // error, derivative of error, integral of error
int error_last=-1, error_step=0; // record error at last measurement and error at last change
int time = 1, time_step=0; // track number of interations since the start of this error
// repetive running actions
// checking sensors, etc.
void run_rep() {
	//float fudge = 10;
	int speed_change=0;
	int direction_change=0;

	//change the read in functions
	if (inductor_left > wire_left) {
		sensor_left = 1;
	}
	else {
		sensor_left = 0;
	}
	if (inductor_right > wire_right) {
		sensor_right = 1;
	}
	else {
		sensor_right = 0;
	}

	// set artificial error
	if (sensor_left && sensor_right) error = 0;
	else if (sensor_left && !sensor_right) error = -1;//right is the negative direction
	else if (!sensor_left && sensor_right) error = 1;//left is the positive direction
	else {
		if (error_last > 0) error = 5;
		else error = -5;
	}

	if (error != error_last) {
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}

	// find the derivative of the error
	//d_error = (float) fudge*(float) (error - error_step) / (float) (time + time_step);
	d_error = (float) (error - error_step) / (float) (time + time_step);



	// set PID coefficients
	// using gains
	
	//speed_change = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;//i dont think that we have integral error
	speed_change = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;


//time counting
int time_init=0;
int time=0;
int wait=1; //while wait is 1 we need to wait for signal

//sensor states
int sensor_left = 0, sensor_right = 0, sensor_front = 0; //this will be a count of how many perpendicular wires have been observed

// threshold of signal 
double threshold_left = 0, threshold_right = 0, threshold_front = 0;

// proportional, integral, derivative gains
float kp=0, ki=0, kd=0;

float error=0, d_error=0, s_error=0; // error, derivative of error, integral of error
int error_last=-1, error_step=0; // record error at last measurement and error at last change
int time = 1, time_step=0; // track number of interations since the start of this error
// repetive running actions
// checking sensors, etc.
void run_rep() {
	//float fudge = 10;
	int speed_change=0;
	int direction_change=0;

	//change the read in functions
	if (inductor_left > wire_left) {
		sensor_left = 1;
	}
	else {
		sensor_left = 0;
	}
	if (inductor_right > wire_right) {
		sensor_right = 1;
	}
	else {
		sensor_right = 0;
	}

	// set artificial error
	if (sensor_left && sensor_right) error = 0;
	else if (sensor_left && !sensor_right) error = -1;//right is the negative direction
	else if (!sensor_left && sensor_right) error = 1;//left is the positive direction
	else {
		if (error_last > 0) error = 5;
		else error = -5;
	}

	if the error has changed, start measuring the time the error persists
	if (error != error_last) {
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}

	// find the derivative of the error
	//d_error = (float) fudge*(float) (error - error_step) / (float) (time + time_step);
	d_error = (float) (error - error_step) / (float) (time + time_step);



	// set PID coefficients
	// using gains
	speed_change = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;

	//increase the time
	time++;

	// record the error at previous measurement
	error_last = error;

	left_wheel=speed+speed_change;
	right_wheel=speed-speed_change;
//***********************

	//check state of the front inductor to store which way to turn if we enter an intersection

	if (inductor_front>threshold_front)
	{	
		wait=1;
		sensor_front=1;
		time_init=time;

		while(wait==1)//check the clock speed
		{

			if (time-time_init>500)//check clock speed
			{
				wait=0;
			}

			if(inductor_front>threshold_front)
			{
				sensor_front++;
				time_init=time;
			}
			
		}
		
		
	}

	if (sensor_front==4) //we are at a start or stop
	{
		if(time==0)//start clock
		{
			
		}else //stop clock
		{

		}
	}else
	{	
		if (sensor_front==3) //turn right weeeee!
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
			
		}else
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







//***************************
	
}
	//increase the time
	time++;

	// record the error at previous measurement
	error_last = error;

	left_wheel=speed+speed_change;
	right_wheel=speed-speed_change;
//***********************

	//check state of the front inductor to store which way to turn if we enter an intersection

	if (inductor_front>threshold_front)
	{	
		wait=1;
		sensor_front=1;
		time_init=time_abs;

		while(wait==1)//check the clock speed
		{

			if (time_abs-time_init>500)//check clock speed
			{
				wait=0;
			}

			if(inductor_front>threshold_front)
			{
				sensor_front++;
				time_init=time_abs;
			}
			
		}
		
		
	}

	if (sensor_front==4) //we are at a start or stop
	{
		if(time_abs==0)//start clock
		{
			
		}else //stop clock
		{

		}
	}else
	{	
		if (sensor_front==3) //turn right weeeee!
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
			
		}else
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

//***************************
	
}