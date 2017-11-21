#include "MotorController.h"

MotorController::MotorController()
{}

void MotorController::begin(int leftA, int leftB, int rightA, int rightB)
{
	pinMode(leftA, OUTPUT);
	pinMode(leftB, OUTPUT);
	pinMode(rightA, OUTPUT);
	pinMode(rightB, OUTPUT);				
}

void MotorController::outputLeft(float out)
{
	digitalWrite(leftA, LOW);
	analogWrite(leftB, out);
}

void MotorController::outputRight(float out)
{
	digitalWrite(rightA, LOW);
	analogWrite(rightB, out);
}