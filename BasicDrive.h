#ifndef BASICDRIVE_H
#define BASICDRIVE_H

#include <Arduino.h>
#include "Encoder.h"
#include "MotorController.h"
#include "Collection.h"

class BasicDrive
{
	public:
		BasicDrive();
		
		void begin(Collection<int> leftMotorPins, Collection<int> leftEncoderPins, Collection<int> rightMotorPins, Collection<int> rightEncoderPins);
		
		void begin(Motor leftMot, Motor rightMot, Encoder leftEnc, Encoder rightEnc);
		
		void setOutput(float left, float right);
		
		Encoder& getLeftEncoder();
		
		Encoder& getRightEncoder();
		
	private:
		Encoder leftEncoder;
		
		Encoder rightEncoder;
		
		MotorController motorController;
};

#endif