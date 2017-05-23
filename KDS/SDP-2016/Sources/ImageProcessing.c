/*
 * ImageProcessing.c
 *
 *  Created on: 31/12/2016
 *      Author: marcelo
 */


#include "ImageProcessing.h"

void calibration()
{
	for (int pixel = 0; pixel < 128; pixel++)
	{
		referenceImage[pixel] = rawImage[pixel];
	}
}

void binarization(uint8 binarizedImage[])
{
	float light;

	for (int pixel = 0; pixel < 128; pixel++)
	{
		light = (float) rawImage[pixel] / (float) referenceImage[pixel];
		if (light < 0.6)
		{
			binarizedImage[pixel] = 0;
		}
		else
		{
			binarizedImage[pixel] = 255;
		}
	}
}
