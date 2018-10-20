#include "Motor.h"

Motor::Motor()
{
	this->in1pin = -1;
	this->in2pin = -1;
	this->enpin = -1;
}

void Motor::operator=(const Motor& motor)
{
	this->in1pin = motor.in1pin;
	this->in2pin = motor.in2pin;
	this->enpin = motor.enpin;
}

Motor* Motor::begin(int in1pin, int in2pin)
{
	this->in1pin = in1pin;
	this->in2pin = in2pin;
	this->enpin = enpin;
	
	if(in1pin != -1)
	{
		pinMode(in1pin, OUTPUT);
	}
	
	if(in2pin != -1)
	{
		pinMode(in2pin, OUTPUT);
	}

	return this;
}


Motor* Motor::begin(int in1pin, int in2pin, int enpin)
{
	this->in1pin = in1pin;
	this->in2pin = in2pin;
	this->enpin = enpin;
	
	if(in1pin != -1)
	{
		pinMode(in1pin, OUTPUT);
	}
	
	if(in2pin != -1)
	{
		pinMode(in2pin, OUTPUT);
	}
	
	if(enpin != -1)
	{
		pinMode(enpin, OUTPUT);
	}

	return this;
}

Motor* Motor::setDefaultOnZero(int high) {
 	if (high <= 1 && high >= 0) {
		this->defaultOnZero = high;
	}
	return this;
}

void Motor::output(float speed)
{
	speed = clamp(speed, -1, 1);

	if (enpin != -1) {
		if(speed > 0) {
			digitalWrite(this->in1pin, LOW);
			digitalWrite(this->in2pin, HIGH);
			analogWrite(this->enpin, speed * 255);
		}
		else if (speed < 0) {
			digitalWrite(this->in1pin, HIGH);
			digitalWrite(this->in2pin, LOW);
			analogWrite(this->enpin, abs(speed) * 255);
		}
		else if (speed == 0) {
			digitalWrite(this->in1pin, defaultOnZero);
			digitalWrite(this->in2pin, defaultOnZero);
			analogWrite(this->enpin, 255);
		}
	} else {
		if(speed > 0) 
		{
			analogWrite(this->in1pin, (int)(abs(speed) * 255) );
			analogWrite(this->in2pin, 0);
		}
		else if (speed < 0) 
		{
			analogWrite(this->in1pin, 0);
			analogWrite(this->in2pin, (int)(abs(speed) * 255) );
		}
		else if (speed == 0) {
			analogWrite(this->in1pin, defaultOnZero);
			analogWrite(this->in2pin, defaultOnZero);
		}
	}
}

void Motor::outputBool(int high) {
	if (enpin == -1) {
		analogWrite(this->in1pin, high);
		analogWrite(this->in2pin, high);
	} else {
		digitalWrite(this->in1pin, high);
		digitalWrite(this->in2pin, high);
	}
}

void Motor::output2(float out)
{
	out = clamp(out, -1, 1);
	
	if(out > 0) 
	{
		analogWrite(this->in1pin, (int)(abs(out) * 255) );
		analogWrite(this->in2pin, 0);
	}
	else if (out < 0) 
	{
		analogWrite(this->in1pin, 0);
		analogWrite(this->in2pin, (int)(abs(out) * 255) );
	}
	else if (out == 0) {
		analogWrite(this->in1pin, 0);
		analogWrite(this->in2pin, 0);
	}
}

/**
 * Private Functions Below
 */

float Motor::clamp(float val, float low, float high)
{
    if(val > high)
    {
        return high;
    }
    else if(val < low)
    {
        return low;
    }
    return val;
}
