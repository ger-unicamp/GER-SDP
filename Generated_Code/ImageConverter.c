/* ###################################################################
**     This component module is generated by Processor Expert. Do not modify it.
**     Filename    : ImageConverter.c
**     Project     : SDP_2016
**     Processor   : MKL25Z128VLK4
**     Component   : ADC
**     Version     : Component 01.697, Driver 01.00, CPU db: 3.00.000
**     Repository  : Kinetis
**     Compiler    : GNU C Compiler
**     Date/Time   : 2016-09-21, 22:00, # CodeGen: 51
**     Abstract    :
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
**     Settings    :
**          Component name                                 : ImageConverter
**          A/D converter                                  : ADC0
**          Sharing                                        : Disabled
**          ADC_LDD                                        : ADC_LDD
**          Interrupt service/event                        : Enabled
**            A/D interrupt                                : INT_ADC0
**            A/D interrupt priority                       : medium priority
**          A/D channels                                   : 1
**            Channel0                                     : 
**              A/D channel (pin)                          : ADC0_SE13/TSI0_CH8/PTB3/I2C0_SDA/TPM2_CH1
**              A/D channel (pin) signal                   : 
**              Mode select                                : Single Ended
**          A/D resolution                                 : 8 bits
**          Conversion time                                : 6.538462 µs
**          Low-power mode                                 : Disabled
**          High-speed conversion mode                     : Disabled
**          Asynchro clock output                          : Disabled
**          Sample time                                    : 0 = short
**          Internal trigger                               : Disabled
**          Number of conversions                          : 1
**          Initialization                                 : 
**            Enabled in init. code                        : yes
**            Events enabled in init.                      : yes
**          CPU clock/speed selection                      : 
**            High speed mode                              : This component enabled
**            Low speed mode                               : This component disabled
**            Slow speed mode                              : This component disabled
**     Contents    :
**         Measure      - byte ImageConverter_Measure(bool WaitForResult);
**         MeasureChan  - byte ImageConverter_MeasureChan(bool WaitForResult, byte Channel);
**         GetValue     - byte ImageConverter_GetValue(void* Values);
**         GetChanValue - byte ImageConverter_GetChanValue(byte Channel, void* Value);
**         Calibrate    - byte ImageConverter_Calibrate(bool WaitForResult);
**
**     Copyright : 1997 - 2015 Freescale Semiconductor, Inc. 
**     All Rights Reserved.
**     
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**     
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**     
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**     
**     o Neither the name of Freescale Semiconductor, Inc. nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**     
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**     
**     http: www.freescale.com
**     mail: support@freescale.com
** ###################################################################*/
/*!
** @file ImageConverter.c
** @version 01.00
** @brief
**         This device "ADC" implements an A/D converter,
**         its control methods and interrupt/event handling procedure.
*/         
/*!
**  @addtogroup ImageConverter_module ImageConverter module documentation
**  @{
*/         

/* MODULE ImageConverter. */

#include "Events.h"
#include "ImageConverter.h"

#ifdef __cplusplus
extern "C" {
#endif 
#define STOP            0x00U          /* STOP state           */
#define MEASURE         0x01U          /* MESURE state         */
#define CONTINUOUS      0x02U          /* CONTINUOUS state     */
#define SINGLE          0x03U          /* SINGLE state         */
#define CALIBRATING     0x04U          /* CALIBRATING state    */

static volatile byte ModeFlg;          /* Current state of device */
LDD_TDeviceData *AdcLdd1_DeviceDataPtr; /* Device data pointer */
/* Sample group configuration */
static LDD_ADC_TSample SampleGroup[ImageConverter_SAMPLE_GROUP_SIZE];
/* Temporary buffer for converting results */
volatile byte ImageConverter_OutV;     /* Sum of measured values */
/* Calibration in progress flag */
static volatile bool OutFlg;           /* Measurement finish flag */

/*
** ===================================================================
**     Method      :  ImageConverter_HWEnDi (component ADC)
**
**     Description :
**         Enables or disables the peripheral(s) associated with the 
**         component. The method is called automatically as a part of the 
**         Enable and Disable methods and several internal methods.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ImageConverter_HWEnDi(void)
{
  if (ModeFlg) {                       /* Start or stop measurement? */
    OutFlg = FALSE;                    /* Output value isn't available */
    SampleGroup[0].ChannelIdx = 0U;
    (void)AdcLdd1_CreateSampleGroup(AdcLdd1_DeviceDataPtr, (LDD_ADC_TSample *)SampleGroup, 1U); /* Configure sample group */
    (void)AdcLdd1_StartSingleMeasurement(AdcLdd1_DeviceDataPtr);
  }
}

/*
** ===================================================================
**     Method      :  ImageConverter_Measure (component ADC)
*/
/*!
**     @brief
**         This method performs one measurement on all channels that
**         are set in the component inspector. (Note: If the [number of
**         conversions] is more than one the conversion of A/D channels
**         is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of a
**                           conversion. If [interrupt service] is
**                           disabled, A/D peripheral doesn't support
**                           measuring all channels at once or Autoscan
**                           mode property isn't enabled and at the same
**                           time the [number of channels] is greater
**                           than 1, then the WaitForResult parameter is
**                           ignored and the method waits for each
**                           result every time. If the [interrupt
**                           service] is disabled and a [number of
**                           conversions] is greater than 1, the
**                           parameter is ignored and the method also
**                           waits for each result every time.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
*/
/* ===================================================================*/
byte ImageConverter_Measure(bool WaitForResult)
{
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = MEASURE;                   /* Set state of device to the measure mode */
  ImageConverter_HWEnDi();             /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (ModeFlg == MEASURE) {}      /* If yes then wait for end of measurement */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ImageConverter_MeasureChan (component ADC)
*/
/*!
**     @brief
**         This method performs measurement on one channel. (Note: If
**         the [number of conversions] is more than one the conversion
**         of the A/D channel is performed specified number of times.)
**     @param
**         WaitForResult   - Wait for a result of
**                           conversion. If the [interrupt service] is
**                           disabled and at the same time a [number of
**                           conversions] is greater than 1, the
**                           WaitForResult parameter is ignored and the
**                           method waits for each result every time.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set this
**                           parameter is ignored, because the parameter
**                           is set inside this method.
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_BUSY - A conversion is already running
**                           ERR_RANGE - Parameter "Channel" out of range
*/
/* ===================================================================*/
/*
The definition of method:
byte ImageConverter_MeasureChan(bool WaitForResult, byte Channel)
was optimised based on the current component setting. An appropriate macro has been defined 
in the AD1.h to maintain API compatibility.
*/
byte PE_ImageConverter_MeasureChan(bool WaitForResult)
{
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = SINGLE;                    /* Set state of device to the measure mode */
  ImageConverter_HWEnDi();             /* Enable the device */
  if (WaitForResult) {                 /* Is WaitForResult TRUE? */
    while (ModeFlg == SINGLE) {}       /* If yes then wait for end of measurement */
  }
  return ERR_OK;                       /* OK */
}

/*
** ===================================================================
**     Method      :  ImageConverter_GetValue (component ADC)
*/
/*!
**     @brief
**         Returns the last measured values for all channels. Format
**         and width of the value is a native format of the A/D
**         converter.
**     @param
**         Values          - Pointer to the array that contains
**                           the measured data. Data type is a byte, a
**                           word or an int. It depends on the supported
**                           modes, resolution, etc. of the AD converter.
**                           See the Version specific information for
**                           the current CPU in [General Info].
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
byte ImageConverter_GetValue(void* Values)
{
  if (!OutFlg) {                       /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  /* Copy measured values */
  *(AdcLdd1_TResultData *)Values = ImageConverter_OutV;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  ImageConverter_GetChanValue (component ADC)
*/
/*!
**     @brief
**         Returns the last measured value of the required channel.
**         Format and width of the value is a native format of the A/D
**         converter.
**     @param
**         Channel         - Channel number. If only one
**                           channel in the component is set then this
**                           parameter is ignored.
**     @param
**         Value           - Pointer to the measured value. Data
**                           type is a byte, a word or an int. It
**                           depends on the supported modes, resolution,
**                           etc. of the AD converter. See the Version
**                           specific information for the current CPU in
**                           [General Info].
**     @return
**                         - Error code, possible codes:
**                           ERR_OK - OK
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_NOTAVAIL - Requested value not
**                           available
**                           ERR_RANGE - Parameter "Channel" out of
**                           range
**                           ERR_OVERRUN - External trigger overrun flag
**                           was detected after the last value(s) was
**                           obtained (for example by GetValue). This
**                           error may not be supported on some CPUs
**                           (see generated code).
*/
/* ===================================================================*/
/*
The definition of method:
byte ImageConverter_GetChanValue(byte Channel, void* Value)
was optimised based on the current component setting. An appropriate macro has been defined 
in the AD1.h to maintain API compatibility.
*/
byte PE_ImageConverter_GetChanValue(void* Value)
{
  if (!OutFlg) {                       /* Is output flag set? */
    return ERR_NOTAVAIL;               /* If no then error */
  }
  /* Copy value from temporary buffer */
  *(AdcLdd1_TResultData *)Value = ImageConverter_OutV;
  return ERR_OK;
}

/*
** ===================================================================
**     Method      :  ImageConverter_Calibrate (component ADC)
**     Description :
**         This method starts self calibration process. Calibration is
**         typically used to remove the effects of the gain and offset
**         from a specific reading.
**     Parameters  :
**         NAME            - DESCRIPTION
**         WaitForResult   - Wait for a result of
**                           calibration. If the <interrupt service> is
**                           disabled, the WaitForResult parameter is
**                           ignored and the method waits for
**                           calibration result every time.
**     Returns     :
**         ---             - Error code
**                           ERR_OK - OK
**                           ERR_BUSY - A conversion is already running
**                           ERR_SPEED - This device does not work in
**                           the active speed mode
**                           ERR_DISABLED - Device is disabled
**                           ERR_FAILED - Calibration hasn't been
**                           finished correctly
** ===================================================================
*/
byte ImageConverter_Calibrate(bool WaitForResult)
{
  if (ModeFlg != STOP) {               /* Is the device in different mode than "stop"? */
    return ERR_BUSY;                   /* If yes then error */
  }
  ModeFlg = CALIBRATING;               /* Set state of device to the calibration mode */
  (void)AdcLdd1_GetMeasurementCompleteStatus(AdcLdd1_DeviceDataPtr); /* Clear measurement complete status */
  (void)AdcLdd1_StartCalibration(AdcLdd1_DeviceDataPtr); /* Start calibration */
  if (!WaitForResult) {                /* If doesn't wait for result */
    return ERR_OK;                     /* then return ERR_OK, but user have to check the result of calibration e.g. by GetCalibrationStatus method */
  }
  while (!AdcLdd1_GetMeasurementCompleteStatus(AdcLdd1_DeviceDataPtr)) {}; /* Wait until calibration ends */
  if (AdcLdd1_GetCalibrationResultStatus(AdcLdd1_DeviceDataPtr) != ERR_OK) { /* If calibration failed flag is set */
    ModeFlg = STOP;                    /* Set the device to the stop mode */
    return ERR_FAILED;                 /* Return ERR_FAILED error code */
  }
  return ERR_OK;                       /* ADC device is now calibrated */
}

/*
** ===================================================================
**     Method      :  ImageConverter_OnMeasurementComplete (component ADC)
**
**     Description :
**         The method services the conversion complete interrupt of the 
**         selected peripheral(s) and eventually invokes the beans 
**         event(s).
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void AdcLdd1_OnMeasurementComplete(LDD_TUserData *UserDataPtr)
{
  (void)UserDataPtr;                   /* Parameter is not used, suppress unused argument warning */
  if (ModeFlg == CALIBRATING) {        /* If the driver is in CALIBRATING mode */
    (void)AdcLdd1_GetCalibrationResultStatus(AdcLdd1_DeviceDataPtr);
    ModeFlg = STOP;                    /* Set the device to the stop mode */
    ImageConverter_OnCalibrationEnd(); /* If yes then invoke user event */
    return;                            /* Return from interrupt */
  }
  AdcLdd1_GetMeasuredValues(AdcLdd1_DeviceDataPtr, (LDD_TData *)&ImageConverter_OutV);
  OutFlg = TRUE;                       /* Measured value is available */
  ImageConverter_OnEnd();              /* If yes then invoke user event */
  ModeFlg = STOP;                      /* Set the device to the stop mode */
}

/*
** ===================================================================
**     Method      :  ImageConverter_Init (component ADC)
**
**     Description :
**         Initializes the associated peripheral(s) and the component 
**         internal variables. The method is called automatically as a 
**         part of the application initialization code.
**         This method is internal. It is used by Processor Expert only.
** ===================================================================
*/
void ImageConverter_Init(void)
{
  OutFlg = FALSE;                      /* No measured value */
  ModeFlg = STOP;                      /* Device isn't running */
  AdcLdd1_DeviceDataPtr = AdcLdd1_Init(NULL); /* Calling init method of the inherited component */
}

/* END ImageConverter. */

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
