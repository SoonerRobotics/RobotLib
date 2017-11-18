#ifndef BASICDRIVE_H
#define BASICDRIVE_H

#include <Arduino.h>
#include "Encoder.h"
#include "Collection.h"

class BasicDrive
{
	public:
		BasicDrive();
		BasicDrive(Collection<int> leftMotorPins, Collection<int> leftEncoderPins, Collection<int> rightMotorPins, Collection<int> rightEncoderPins);
		
		void setOutput(float left, float right);
		
		Encoder& getLeftEncoder();
		
		Encoder& getRightEncoder();
		
	private:
		Encoder leftEncoder;
		
		Encoder rightEncoder;
		
		//MotorController motorControl;
};

#endif