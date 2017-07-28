/*
 * ImageProcessing.h
 *
 *  Created on: 31/12/2016
 *      Author: marcelo
 */

#ifndef IMAGEPROCESSING_H_
#define IMAGEPROCESSING_H_


#include "PE_Types.h"
#include "CameraController.h"

volatile uint8 referenceImage[128];

void calibration();
void binarization(uint8 binarizedImage[]);
void setBorders(uint8 image[], uint8 *leftBorder, uint8 *rightBorder);

#endif /* IMAGEPROCESSING_H_ */
