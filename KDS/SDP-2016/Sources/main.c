/* ###################################################################
 **     Filename    : main.c
 **     Project     : SDP_2016
 **     Processor   : MKL25Z128VLK4
 **     Version     : Driver 01.01
 **     Compiler    : GNU C Compiler
 **     Date/Time   : 2016-07-30, 17:07, # CodeGen: 0
 **     Abstract    :
 **         Main module.
 **         This module contains user's application code.
 **     Settings    :
 **     Contents    :
 **         No public methods
 **
 ** ###################################################################*/
/*!
 ** @file main.c
 ** @version 01.01
 ** @brief
 **         Main module.
 **         This module contains user's application code.
 */
/*!
 **  @addtogroup main_module main module documentation
 **  @{
 */
/* MODULE main */


/* Including needed modules to compile this module/procedure */
#include "Cpu.h"
#include "Events.h"
#include "SI.h"
#include "BitIoLdd1.h"
#include "CLK.h"
#include "BitIoLdd2.h"
#include "ClockInterruption.h"
#include "TimerIntLdd1.h"
#include "TU1.h"
#include "ImageConverter.h"
#include "AdcLdd1.h"
#include "SerialCom.h"
#include "Enable_Motors.h"
#include "BitIoLdd4.h"
#include "Motor_A_In_1.h"
#include "PwmLdd1.h"
#include "TU2.h"
#include "Motor_A_In_2.h"
#include "PwmLdd2.h"
#include "Motor_B_In1.h"
#include "PwmLdd3.h"
#include "Motor_B_In2.h"
#include "PwmLdd4.h"
#include "Servomotor.h"
#include "PwmLdd5.h"
#include "TU3.h"
/* Including shared modules, which are used for whole project */
#include "PE_Types.h"
#include "PE_Error.h"
#include "PE_Const.h"
#include "IO_Map.h"
/* User includes (#include below this line is not maintained by Processor Expert) */
#include "CameraController.h"
#include "SerialCommunication.h"
#include "GlobalVariables.h"


#define MAX_DIR 18900
#define CEN_DIR 18550
#define MIN_DIR 18200


/*lint -save  -e970 Disable MISRA rule (6.3) checking. */
int main(void)
/*lint -restore Enable_Motors MISRA rule (6.3) checking. */
{
	/* Write your local variable definition here */

	/*** Processor Expert internal initialization. DON'T REMOVE THIS CODE!!! ***/
	PE_low_level_init();
	/*** End of Processor Expert internal initialization.                    ***/

	/* Write your code here */
//	while (1)
//	{
//		Servomotor_SetDutyUS(MAX_DIR);
//		for (int i = 0; i < 10000000; i++);
//		Servomotor_SetDutyUS(MIN_DIR);
//		for (int i = 0; i < 10000000; i++);
//	}
//
//	Enable_Motors_SetVal();
	cameraStartReading(TRUE);

	/*** Don't write any code pass this line, or it will be deleted during code generation. ***/
  /*** RTOS startup code. Macro PEX_RTOS_START is defined by the RTOS component. DON'T MODIFY THIS CODE!!! ***/
  #ifdef PEX_RTOS_START
    PEX_RTOS_START();                  /* Startup of the selected RTOS. Macro is defined by the RTOS component. */
  #endif
  /*** End of RTOS startup code.  ***/
  /*** Processor Expert end of main routine. DON'T MODIFY THIS CODE!!! ***/
  for(;;){}
  /*** Processor Expert end of main routine. DON'T WRITE CODE BELOW!!! ***/
} /*** End of main routine. DO NOT MODIFY THIS TEXT!!! ***/

/* END main */
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
