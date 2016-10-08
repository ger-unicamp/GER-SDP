/* ###################################################################
 **     Filename    : Events.c
 **     Project     : SDP_2016
 **     Processor   : MKL25Z128VLK4
 **     Component   : Events
 **     Version     : Driver 01.00
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-07-30, 17:07, # CodeGen: 0
 **     Abstract    :
 **         This is user's event module.
 **         Put your event handler code here.
 **     Contents    :
 **         Cpu_OnNMIINT - void Cpu_OnNMIINT(void);
 **
 ** ###################################################################*/
/*!
 ** @file Events.c
 ** @version 01.00
 ** @brief
 **         This is user's event module.
 **         Put your event handler code here.
 */
/*!
 **  @addtogroup Events_module Events module documentation
 **  @{
 */
/* MODULE Events */

#include "Cpu.h"
#include "Events.h"

#ifdef __cplusplus
extern "C" {
#endif 


/* User includes (#include below this line is not maintained by Processor Expert) */

/*
 ** ===================================================================
 **     Event       :  Cpu_OnNMIINT (module Events)
 **
 **     Component   :  Cpu [MKL25Z128LK4]
 */
/*!
 **     @brief
 **         This event is called when the Non maskable interrupt had
 **         occurred. This event is automatically enabled when the [NMI
 **         interrupt] property is set to 'Enabled'.
 */
/* ===================================================================*/
void Cpu_OnNMIINT(void)
{
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  ClockInterruption_OnInterrupt (module Events)
 **
 **     Component   :  ClockInterruption [TimerInt]
 **     Description :
 **         When a timer interrupt occurs this event is called (only
 **         when the component is enabled - <Enable> and the events are
 **         enabled - <EnableEvent>). This event is enabled only if a
 **         <interrupt service/event> is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void ClockInterruption_OnInterrupt(void)
{
	switch (state)
	{

	case HALF_LOW_CLK:
	{

		// next state
		state = HIGH_CLK;

		if (clockCounter == 0)
		{
			// SI High.
			SI_SetVal();
			while (!SI_GetVal());
		}

		// Fim de um ciclo.
		// A camera precisa de um clock a mais para enviar o ultimo pixel.
		else if (clockCounter == 129)
		{
			clockCounter = 0;
			// E 20 microssegundos para se preparar para o proximo ciclo.
			state = WAIT_TRANSFER_CHARGE;

			// Updates the control samples
			if (measuringCounter < 0)
			{
				// In this case happened overflow.
				measuringCounter = 0;
			}
			else
			{
				measuringCounter++;
			}
		}

		break;
	}
	case HIGH_CLK:
	{
		// Clock High.
		CLK_SetVal();

		clockCounter++;

		state = HALF_HIGH_CLK;

		break;
	}
	case HALF_HIGH_CLK:
	{
		if (clockCounter == 1)
		{
			// SI Low.
			SI_ClrVal();
			while (SI_GetVal());
		}

		// Starts the AD convertion
		ImageConverter_Measure(FALSE);

		state = LOW_CLK;
		break;
	}
	case LOW_CLK:
	{
		// Clock Low.
		CLK_ClrVal();

		state = HALF_LOW_CLK;

		break;
	}

	// Pixel charge transfer time
	case WAIT_TRANSFER_CHARGE:
	{
		if (transferTime)
		{
			transferTime++;
		}
		else
		{
			transferTime = 0;
			state = HALF_LOW_CLK;
		}

		break;
	}
	}
}

/*
 ** ===================================================================
 **     Event       :  ImageConverter_OnEnd (module Events)
 **
 **     Component   :  ImageConverter [ImageConverter]
 **     Description :
 **         This event is called after the measurement (which consists
 **         of <1 or more conversions>) is/are finished.
 **         The event is available only when the <Interrupt
 **         service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void ImageConverter_OnEnd(void)
{

	ImageConverter_GetChanValue(0, &pixelArray[0][clockCounter]);
}

/*
 ** ===================================================================
 **     Event       :  ImageConverter_OnCalibrationEnd (module Events)
 **
 **     Component   :  ImageConverter [ImageConverter]
 **     Description :
 **         This event is called when the calibration has been finished.
 **         User should check if the calibration pass or fail by
 **         Calibration status method./nThis event is enabled only if
 **         the <Interrupt service/event> property is enabled.
 **     Parameters  : None
 **     Returns     : Nothing
 ** ===================================================================
 */
void ImageConverter_OnCalibrationEnd(void)
{
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  SerialCom_OnBlockReceived (module Events)
 **
 **     Component   :  SerialCom [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called when the requested number of data is
 **         moved to the input buffer.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void SerialCom_OnBlockReceived(LDD_TUserData *UserDataPtr)
{
	/* Write your code here ... */
}

/*
 ** ===================================================================
 **     Event       :  SerialCom_OnBlockSent (module Events)
 **
 **     Component   :  SerialCom [Serial_LDD]
 */
/*!
 **     @brief
 **         This event is called after the last character from the
 **         output buffer is moved to the transmitter.
 **     @param
 **         UserDataPtr     - Pointer to the user or
 **                           RTOS specific data. This pointer is passed
 **                           as the parameter of Init method.
 */
/* ===================================================================*/
void SerialCom_OnBlockSent(LDD_TUserData *UserDataPtr)
{
	Serial_Device *ptr = (Serial_Device*)UserDataPtr;

	ptr->isSent = TRUE; /* set flag so sender knows we have finished */

}

/* END Events */

#ifdef __cplusplus
}  /* extern "C" */
#endif 

/*!
 ** @}
 */
/*
 ** ###################################################################
 **
 **     This file was created by Processor Expert 10.5 [05.21]
 **     for the Freescale Kinetis series of microcontrollers.
 **
 ** ###################################################################
 */
