#include "BasicDrive.h"

BasicDrive::BasicDrive(Collection<int> leftMotorPins, Collection<int> leftEncoderPins, Collection<int> rightMotorPins, Collection<int> rightEncoderPins)
{
	int leftEncA = leftEncoderPins.get(0);
	int leftEncB = leftEncoderPins.get(1);
	
	int rightEncA = rightEncoderPins.get(0);
	int rightEncB = rightEncoderPins.get(1);
}

void BasicDrive::setOutput(float left, float right)
{
	
}

Encoder& BasicDrive::getLeftEncoder()
{
	return this->leftEncoder;
}

Encoder& BasicDrive::getRightEncoder()
{
	return this->rightEncoder;
}