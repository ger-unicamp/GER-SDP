/*
 * CameraController.c
 *
 *  Created on: 30/07/2016
 *      Author: marcelo
 */


#include "CameraController.h"

/* ===================================================================
 **     Method      :  void cameraStartReading(int serialTest)
 **
 **
 **     @brief
 **			The LitleClock component (TimerInt) starts disabled.
 **			Therefore, it's necessary enable him.
 **
 **     @param
 **			int serialTest:
 **							-> 0: For it starts camera reading.
 **							-> 1: For it starts the serial communication.
 **
 **
 ** ===================================================================*/
void cameraStartReading(int serialTest)
{
	if (serialTest == FALSE)
	{
		// Initialize camera to begin reading.
		initializeCamera();

		// Ativa a câmera.
		ClockInterruption_Enable();
	}

	else if (serialTest == TRUE)
	{
		testMode();
	}

	else
	{
		// Error, do something.
		return;
	}
}
///////////////////VER SE PODE DECLARAR VARIAVEL IM HEADER E COMO FAZER ISSO.
void initializeCamera()
{
	state = HALF_LOW_CLK;
	clockCounter = 0;
	transferTime = 0;
}

void testMode()
{
	initializeCamera();
	//
	//		isReading = TRUE;
	//
	ClockInterruption_Enable();
	//
	//		// Wait the end of reading.
	//		while (isReading == TRUE);
	//
	//		ClockInterruption_Disable();

	while (1)
	{
		// Serial communication.
		send ('a');
		send('\n');
		send('\r');
	}
}
