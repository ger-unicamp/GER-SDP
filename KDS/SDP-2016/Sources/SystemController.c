/*
 * SystemController.c
 *
 *  Created on: 31/12/2016
 *      Author: marcelo
 */

#include "SystemController.h"
#include "GreenLED.h"

void basicControll(uint8 image[])
{
	bool found = FALSE;
	int speed = 64;
	int delta = 63;
	int rightRate, leftRate;

	// Find the border on the right
	found = FALSE;

	for (int pixel = 64; pixel < 128 && !found; pixel++)
	{
		if (image[pixel] == 0)
		{
			rightRate = pixel - 64;
			found = TRUE;
		}
	}

	// Find the border on the left
	found = FALSE;

	for (int pixel = 63; pixel >= 0 && !found; pixel--)
	{
		if (image[pixel] == 0)
		{
			leftRate = -(pixel - 63);
			found = TRUE;
		}
	}

	// Turn to the correct side
	if (leftRate == 0 && rightRate == 0)
	{
		setMotorsSpeed(speed, speed);
		setServoDirection(0);
	}
	// If de left is the correct side
	else if (leftRate < rightRate)
	{
		setServoDirection(((float)(delta - leftRate)/delta)*350);
		setMotorsSpeed((int)speed*((float)leftRate/delta), (int)speed*((float)leftRate/delta));
	}
	// If de right is the correct side
	else
	{
		setServoDirection(-((float)(delta - rightRate)/delta)*350);
		setMotorsSpeed((int)speed*((float)rightRate/delta), (int)speed*((float)rightRate/delta));
	}
}
