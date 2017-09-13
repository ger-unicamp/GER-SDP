#include "PID.h"

// the setup routine runs once when you press reset:

void resetPID(SPID *pid, double initial_track_width)
{
	pid->p_gain = 0;
	pid->d_gain = 1;
	pid->i_gain = 0;

	pid->i_state = 0;
	pid->i_max = 1;
	pid->i_min = 0;

	pid->last_error = 0;
	pid->last_track_width = initial_track_width;
}

double update_pid (SPID * pid, double error, double track_width)
{

	// Termo proporcionao, integrativo e derivativo.
	double p_term = 0, i_term = 0, d_term = 0;


	//set_integral_state(pid,  error);

	// Proportional term
	p_term = error * pid->p_gain;

	// integral term
//	i_term = pid->i_gain * pid->i_state;

	// derivative error
	d_term = get_derivative_state(pid, error, track_width) * pid->d_gain;

	pid->last_error = error;


	return p_term + i_term + d_term;

}

double get_derivative_state(SPID *pid, double error, double track_width)
{
	double mean = (pid->last_track_width + track_width) / 2;
	pid->last_track_width = track_width;

	return (error - pid->last_error) / mean;
}

void set_integral_state(SPID * pid, double error)
{
	// calculate the integrator state
	pid->i_state += error;

	// applies anti-windup
	if(pid->i_state > pid->i_max)
	{
		pid->i_state = pid->i_max;
	}

	else if(pid->i_state < pid->i_min)
	{
		pid->i_state = pid->i_min;
	}
}

