#include "Motor.h"

/*
	Default constructor for Motor.
*/
Motor::Motor()
{
	this->in1pin = -1;
	this->in2pin = -1;
	this->enpin = -1;
}

/*
	Equal sign allows you to copy over another Motor object's variables.

	@param motor - existing Motor object whose stuff gets copied over
*/
void Motor::operator=(const Motor& motor)
{
	this->in1pin = motor.in1pin;
	this->in2pin = motor.in2pin;
	this->enpin = motor.enpin;
}

/*
	Sets up the thing where you use two pins to tell the motor what to do.

	@param in1pin - first analog output pin

	@param in2pin - second analog output pin
*/
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

/*
	Sets up the thing where you use three pins to tell the motor what to do.

	@param in1pin - first digital output pin

	@param in2pin - second digital output pin
	
	@param enpin - analog output pin

	@return pointer to Motor object that the function is called from
*/
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

/*
	Sets defaultOnZero to high

	@param high - 0 or 1
	
	@return pointer to Motor object
*/
Motor* Motor::setDefaultOnZero(int high) {
 	if (high <= 1 && high >= 0) {
		this->defaultOnZero = high;
	}
	return this;
}

/*
	Outputs values to motor controller if you use three pins.

	@param speed - decimal from -1 to 1
*/

void Motor::output(float speed)
{
	if(disabled){
		return;
	}

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

/*
	Makes the motor stop or coast.

	@param high - value from 0 to 255
*/
void Motor::outputBool(int high) {
	if(disabled){
		return;
	}

	if (enpin == -1) {
		analogWrite(this->in1pin, high);
		analogWrite(this->in2pin, high);
	} else {
		digitalWrite(this->in1pin, high);
		digitalWrite(this->in2pin, high);
		analogWrite(this->enpin, 0);
	}
}

/*
	Outputs values to motor controller if you use 2 pins

	@param out - speed of the motor as a decimal from -1 to 1
*/ 
void Motor::output2(float out)
{
	if(disabled){
		return;
	}

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

void Motor::disableOutput()
{
	disabled = HIGH;

	if (enpin == -1) {
		analogWrite(this->in1pin, defaultOnZero);
		analogWrite(this->in2pin, defaultOnZero);
	} else {
		digitalWrite(this->in1pin, defaultOnZero);
		digitalWrite(this->in2pin, defaultOnZero);
		analogWrite(this->enpin, 0);
	}
}

void Motor::enableOutput()
{
	disabled = LOW;
}
	
/**
 * Private Functions Below
 */

/*
	Returns val on interval [low, high]

	@param val - float that gets changed

	@param low - lower bound

	@param high - higher bound

	@return float between low and high (inclusive)
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
