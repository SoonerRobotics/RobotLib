#include "MotorController.h"

//why do we need this class
MotorController::MotorController()
{}

/*
	Ses up motor controller with motors.

	@param motorA - Motor object

	@param motorB - Motor object
*/
void MotorController::begin(Motor motorA, Motor motorB)
{
	this->motorA = motorA;
	this->motorB = motorB;
}

/*
	Makes motor A spin at the speed you want.

	@out - float on the range [-1, 1]
*/
void MotorController::outputMotorA(float out)
{
	this->motorA.output(out);
}

/*
	Makes motor B spin at the speed you want.

	@out - float representing motor speed
*/
void MotorController::outputMotorB(float out)
{
	this->motorB.output(out);
}

