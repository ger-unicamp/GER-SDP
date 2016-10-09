/*
 * SerialCommunication.c
 *
 *  Created on: 04/09/2016
 *      Author: marcelo
 */

#include "SerialCommunication.h"
#include "DebugLED.h"

static Serial_Device deviceData;

static void init_Serial()
{
	deviceData.handle = SerialCom_Init(&deviceData); /* Initialization of serial component */
	deviceData.isSent = FALSE;
}

static int sendChar(unsigned char ch)
{
	deviceData.isSent = FALSE;
	while(SerialCom_SendBlock(deviceData.handle, (LDD_TData*)&ch, 1)!= ERR_OK) {} /* Send char */
	while(!deviceData.isSent) {} /* wait until we get the green flag from the TX interrupt */
}

void itoa_8_bit(uint8_t sample)
{
	unsigned char R1, R2, R3;
	int Q1, Q2;

	if (sample < MIN || sample > MAX)
	{
		sendChar('E');
		return;
	}

	R1 = (unsigned char) (sample % 10) + '0';
	Q1 = sample / 10;

	R2 = (unsigned char) (Q1 % 10) + '0';
	Q2 = Q1 / 10;

	R3 = (unsigned char) (Q2 % 10) + '0';

	sendChar(R3);
	sendChar(R2);
	sendChar(R1);
}

void sendArrayOfPixels(uint8_t array[])
{
	init_Serial();

	for (int pixel = 0; pixel < 128; pixel++)
	{
		itoa_8_bit(array[pixel]);
		sendChar(' ');
	}

	sendChar('\n');
	sendChar('\r');

	serialFinished = TRUE;
}

void runSerialTest()
{
//	serialTest = TRUE;
//
//	while (!serialTestStart) {}
//
//	sendArrayOfPixels(pixelArray[0]);
}
void sendC(char ch)
{
	init_Serial();

	sendChar(ch);
	sendChar('\n');
	sendChar('\r');
}

void sendAChar(char c)
{
	init_Serial();
	sendChar(c);
}
