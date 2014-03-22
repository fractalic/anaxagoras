/* this is a digital pid algorithm,
obtained from analog inputs with a threshold */

//sensor states
int sensor_left = 0;
int sensor_right = 0;

// thresholds
double tape_left = 0, tape_right = 0;

// proportional, integral, derivative gains
float kp, ki, kd;

int analogs[2];
float error, d_error, s_error; // error, derivative of error, integral of error
int error_last, error_step; // record error at last measurement and error at last change
int time = 1, time_step; // track number of interations since the start of this error
// repetive running actions
// checking sensors, etc.
void run_rep() {
	float fudge = 10;
	int speed_change;
	
	// read qrd sensors
	//analogs[0] = analogRead(left);
	//analogs[1] = analogRead(right);

	if (analogs[0] > tape_left) {
		sensor_left = 1;
	}
	else {
		sensor_left = 0;
	}
	if (analogs[1] > tape_right) {
		sensor_right = 1;
	}
	else {
		sensor_right = 0;
	}

	// set artificial error
	if (sensor_left && sensor_right) error = 0;
	else if (sensor_left && !sensor_right) error = -1;
	else if (!sensor_left && sensor_right) error = 1;
	else {
		if (error_last > 0) error = 5;
		else error = -5;
	}

	// if the error has changed, start measuring the time the error persists
	if (error != error_last) {
		error_step = error_last; // record the error value
		time_step = time;
		time = 1;
	}

	// find the derivative of the error
	d_error = (float) fudge*(float) (error - error_step) / (float) (time + time_step);

	// set PID coefficients
	// using gains
	speed_change = (float) kp*(float) error + (float) ki*(float) s_error + (float) kd*(float) d_error;

	//increase the time
	time++;

	// record the error at previous measurement
	error_last = error;

	//motor.speed(motor_left, speedScale(0, speed + speed_change));
	//motor.speed(motor_right, speedScale(1, speed - speed_change));
}