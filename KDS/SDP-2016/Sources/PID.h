/*
 * PID.h
 *
 *  Created on: 27/07/2017
 *      Author: marcelo
 */

#ifndef SOURCES_PID_H_
#define SOURCES_PID_H_

struct SPID
{
  // PID gains
  double p_gain;
  double d_gain;
  double i_gain;

  double i_state;
  int i_max;
  int i_min;

  double last_error;
  double last_track_width;
} typedef SPID;


double update_pid (SPID * pid, double error);
double get_derivative_state(SPID *pid, double error);
void set_integral_state(SPID * pid, double error);
void resetPID(SPID *pid);


#endif /* SOURCES_PID_H_ */
