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


//////////////////////////////////
int error_delta_start;
int time_delta_start;

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