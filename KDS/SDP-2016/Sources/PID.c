#include "PID.h"

// the setup routine runs once when you press reset:

void resetPID(SPID *pid)
{
	pid->p_gain = 1.0;
	pid->d_gain = 0.0;
	pid->i_gain = 0;

	pid->i_state = 0;
	pid->i_max = 1;
	pid->i_min = -1;

	pid->last_error = 0;
}

double update_pid (SPID * pid, double error)
{
	double output;

	// Termo proporcionao, integrativo e derivativo.
	double p_term = 0, i_term = 0, d_term = 0;


	//set_integral_state(pid,  error);

	// Proportional term
	p_term = error * pid->p_gain;

	// integral term
	i_term = pid->i_gain * pid->i_state;

	// derivative term
	d_term = get_derivative_state(pid, error);

	pid->last_error = error;

	output = p_term + i_term + d_term;


	if (output < -1)
	{
		output = -1;
	}
	else if (output > 1)
	{
		output = 1;
	}

	return output;
}

double get_derivative_state(SPID *pid, double error)
{
	return (error - pid->last_error) * pid->d_gain;
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

