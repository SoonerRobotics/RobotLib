#include "Motor.h"

Motor::Motor()
{
	this->A = NULL;
	this->B = NULL;
	this->enable = NULL;
}

void Motor::operator=(const Motor& motor)
{
	this->A = motor.A;
	this->B = motor.B;
	this->enable = motor.enable;
}


void Motor::begin(int A, int B, int enable)
{
	this->A = A;
	this->B = B;
	this->enable = enable;
	
	if(A != NULL)
	{
		pinMode(A, OUTPUT);
	}
	
	if(B != NULL)
	{
		pinMode(B, OUTPUT);
	}
	
	if(enable != NULL)
	{
		pinMode(enable, OUTPUT);
	}
}

void Motor::output(float out)
{
	out = coerce(out, 1, -1);
	
	if(out > 0) {
		digitalWrite(this->A, LOW);
		digitalWrite(this->B, HIGH);
		analogWrite(this->enable, out * 255);
	}
	else if (out < 0) {
		digitalWrite(this->A, HIGH);
		digitalWrite(this->B, LOW);
		analogWrite(this->enable, abs(out) * 255);
	}
	else if (out == 0) {
		digitalWrite(this->A, HIGH);
		digitalWrite(this->B, HIGH);
		analogWrite(this->enable, 255);
	}
}



/**
 * Private Functions Below
 */

float Motor::coerce(float val, float upper, float lower)
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
