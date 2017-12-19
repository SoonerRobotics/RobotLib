#include "MotorController.h"

MotorController::MotorController()
{}

void MotorController::begin(Motor motorA, Motor motorB)
{
	this->motorA = motorA;
	this->motorB = motorB;
}

void MotorController::outputMotorA(float out)
{
	this->motorA.output(out);
}

void MotorController::outputMotorB(float out)
{
	this->motorB.output(out);
}

