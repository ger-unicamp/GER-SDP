/*
 * SerialCommunication.h
 *
 *  Created on: 04/09/2016
 *      Author: marcelo
 */

#ifndef SOURCES_SERIALCOMMUNICATION_H_
#define SOURCES_SERIALCOMMUNICATION_H_

#include "SerialCom.h"
#include "PE_Types.h"

#define MAX 255
#define MIN 0

extern uint8_t pixelArray[2][128];

extern volatile bool serialTest;
extern volatile bool serialFinished;
extern volatile bool serialTestStart;

typedef struct
{
	LDD_TDeviceData *handle; /* LDD device handle. */
	volatile bool isSent; // Flag to send data. Must be volatile.
} Serial_Device;

void runSerialTest();
void sendArrayOfPixels(uint8_t array[]);
void itoa_8_bit(uint8_t sample);
void sendC(char ch);

#endif /* SOURCES_SERIALCOMMUNICATION_H_ */
