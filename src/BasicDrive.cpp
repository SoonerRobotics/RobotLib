#include "BasicDrive.h"

BasicDrive::BasicDrive()
{}

/*
	@param leftMotorPins - Collection with 2 pin numbers for left motor

	@param leftEncoderPins - Collection with 3 pin numbers for left motor encoder

	@param rightMotorPins - Collection with 2 pin numbers for right motor

	@param rightMotorEncoder - Collection with 3 pin numbers for right motor encoder

*/
void BasicDrive::begin(Collection<int> leftMotorPins, Collection<int> leftEncoderPins, Collection<int> rightMotorPins, Collection<int> rightEncoderPins)
{
	int leftEncA = leftEncoderPins.get(0);
	int leftEncB = leftEncoderPins.get(1);
	
	int rightEncA = rightEncoderPins.get(0);
	int rightEncB = rightEncoderPins.get(1);
	
	int leftMotA = leftMotorPins.get(0);
	int leftMotB = leftMotorPins.get(1);
	int leftMotEnb = leftMotorPins.get(2);
	
	int rightMotA = rightMotorPins.get(0);
	int rightMotB = rightMotorPins.get(1);
	int rightMotEnb = rightMotorPins.get(2);
	
	Motor left;
	left.begin(leftMotA, leftMotB, leftMotEnb);
	
	Motor right;
	right.begin(rightMotA, rightMotB, rightMotEnb);
	
	Encoder rightEnc(rightEncA, rightEncB);
	this->rightEncoder = rightEnc;
	
	Encoder leftEnc(leftEncA, leftEncB);
	this->leftEncoder = leftEnc;
	
	//Left = A 
	//Right = B
	MotorController controller;
	controller.begin(left, right);
	this->motorController = controller;
}

/*
	Creates a motor controller object and gives it two motors and assigns two encoders

	@param leftMot - Motor object

	@param rightMot - Motor object

	@param leftEnc - Encoder object

	@param rightEnc - Encoder object
*/
void BasicDrive::begin(Motor& leftMot, Motor& rightMot, Encoder& leftEnc, Encoder& rightEnc)
{
	MotorController controller;
	controller.begin(leftMot, rightMot);

	this->motorController = controller;
	
	this->leftEncoder = leftEnc;
	
	this->rightEncoder = rightEnc;
}

/*
	Makes the motors run

	@param leftOut - float on [-1, 1] for left motor speed

	@param rightOut - float on [-1, 1] for right motor speed
*/
void BasicDrive::setOutput(float leftOut, float rightOut)
{
	motorController.outputMotorA(leftOut);
	
	motorController.outputMotorB(rightOut);
}

/*
	Returns your left Encoder object

	@return - Encoder object
*/
Encoder& BasicDrive::getLeftEncoder()
{
	return this->leftEncoder;
}

/*
	Returns your right Encoder object

	@return - Encoder
*/
Encoder& BasicDrive::getRightEncoder()
{
	return this->rightEncoder;
}

/*
	Resets the tick count for both encoders.
*/
void BasicDrive::resetEncoders()
{
	leftEncoder.reset();
	rightEncoder.reset();
}