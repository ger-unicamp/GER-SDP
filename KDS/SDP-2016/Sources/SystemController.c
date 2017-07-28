/*
 * SystemController.c
 *
 *  Created on: 31/12/2016
 *      Author: marcelo
 */

#include "SystemController.h"
#include "GreenLED.h"

void advancedControl(double pid_output)
{

	int servo_parameter = (int) (pid_output * 350.0);
	int left_motor_parameter = 75;
	int right_motor_parameter = 75;

	setServoDirection(servo_parameter);
	setMotorsSpeed(left_motor_parameter, right_motor_parameter);

}
