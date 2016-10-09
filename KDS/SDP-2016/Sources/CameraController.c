/*
 * CameraController.c
 *
 *  Created on: 30/07/2016
 *      Author: marcelo
 */


#include "CameraController.h"

/* ===================================================================
 **     Method      :  void cameraStartReading(bool serialTest)
 **
 **
 **     @brief
 **			The LitleClock component (TimerInt) starts disabled.
 **			Therefore, it's necessary enable him.
 **
 **     @param
 **			bool serialTest:
 **							-> FALSE: For it starts camera reading.
 **							-> TRUE: For it starts the serial communication.
 **
 **
 ** ===================================================================*/
void cameraStartReading(bool serialTest)
{
	if (serialTest == TRUE)
	{
		testMode();
	}

	else
	{
		// Initializes the camera
		initializeCamera();

		// Camera activation
		ClockInterruption_Enable();
	}

}

void initializeCamera()
{
	// Inicial state
	state = HALF_LOW_CLK;

	clockCounter = 0;

	transferTime = 0;
	// Number of samples
	measuringCounter = 0;
}

// Serial Communication Mode.
void testMode()
{
	while(TRUE)
	{
		// Initializes the camera
		initializeCamera();

		// Camera activation
		ClockInterruption_Enable();

		// Expects the camera to finish N readings
		while (measuringCounter != 10);

		// disable the camera
		ClockInterruption_Disable();

		// send array by serial communication
		sendArrayOfPixels(pixelArray[0]);
	}

}
