#include "MotorController.h"

MotorController::MotorController()
{}

void MotorController::begin(int leftA, int leftB, int leftEnb, int rightA, int rightB, int rightEnb)
{
	pinMode(leftA, OUTPUT);
	pinMode(leftB, OUTPUT);
	pinMode(rightA, OUTPUT);
	pinMode(rightB, OUTPUT);	
	pinMode(leftEnb, OUTPUT);
	pinMode(rightEnb, OUTPUT);
}

void MotorController::outputLeft(float out)
{
	out = constrain(out, -1, 1);
	if(out > 0) {
		digitalWrite(leftA, LOW);
		digitalWrite(leftB, HIGH);
		analogWrite(leftEnb, out * 255);
	}
	else if (out < 0) {
		digitalWrite(leftA, HIGH);
		digitalWrite(leftB, LOW);
		analogWrite(leftEnb, abs(out) * 255);
	}
	else if (out == 0) {
		digitalWrite(leftA, LOW);
		digitalWrite(leftB, LOW);
	}
}

void MotorController::outputRight(float out)
{
	out = constrain(out, -1, 1);
	if(out > 0) {
		digitalWrite(rightA, LOW);
		digitalWrite(rightB, HIGH);
		analogWrite(rightEnb, out * 255);
	}
	else if (out < 0) {
		digitalWrite(rightA, HIGH);
		digitalWrite(rightB, LOW);
		analogWrite(rightEnb, abs(out) * 255);
	}
	else if (out == 0) {
		digitalWrite(rightA, LOW);
		digitalWrite(rightA, LOW);
	}
}