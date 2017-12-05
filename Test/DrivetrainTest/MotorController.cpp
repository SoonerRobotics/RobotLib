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
	
	this->leftA = leftA;
	this->leftB = leftB;
	this->leftEnb = leftEnb;
	
	this->rightA = rightA;
	this->rightB = rightB;
	this->rightEnb = rightEnb;
}

void MotorController::outputLeft(float out)
{
	out = coerce(out, 1, -1);
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
		analogWrite(leftEnb, 0);
	}
}

void MotorController::outputRight(float out)
{
	out = coerce(out, 1, -1);
	
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
		digitalWrite(rightB, LOW);
		analogWrite(rightEnb, 0);
	}
}

float MotorController::coerce(float val, float upper, float lower)
{
    if(val > upper)
    {
        return upper;
    }
    else if(val < lower)
    {
        return lower;
    }
    return val;
}
