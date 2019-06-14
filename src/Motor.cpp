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
Motor& Motor::operator=(const Motor& motor)
{
	this->in1pin = motor.in1pin;
	this->in2pin = motor.in2pin;
	this->enpin = motor.enpin;
    return *this;
}

/*
	Sets up the thing where you use two pins to tell the motor what to do.

	@param in1pin - first analog output pin

	@param in2pin - second analog output pin
*/
Motor& Motor::begin(int in1pin, int in2pin)
{
	this->in1pin = in1pin;
	this->in2pin = in2pin;
	this->enpin = -1;
	
	if(in1pin != -1)
	{
		pinMode(in1pin, OUTPUT);
	}
	
	if(in2pin != -1)
	{
		pinMode(in2pin, OUTPUT);
	}

	return *this;
}

/*
	Sets up the thing where you use three pins to tell the motor what to do.

	@param in1pin - first digital output pin

	@param in2pin - second digital output pin
	
	@param enpin - analog output pin

	@return pointer to Motor object that the function is called from
*/
Motor& Motor::begin(int in1pin, int in2pin, int enpin)
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

	return *this;
}
/*
    Reverses the direction of a motor by swapping it's pins

    @return pointer to Motor object
 */
Motor& Motor::reverse() {
    int temp = this->in1pin;
    this->in1pin = this->in2pin;
    this->in2pin = temp;

    return *this;
}

/*
	Sets defaultOnZero to value

	@param value - 0 or 1
	
	@return pointer to Motor object
*/
Motor& Motor::setDefaultOnZero(int value) {
 	if (value >= 0 && value <= 1) {
		this->defaultOnZero = value;
	}
	return *this;
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

	speed = RLUtil::clamp(speed, -1, 1);

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
			analogWrite(this->in1pin, (int)(speed * 255) );
			analogWrite(this->in2pin, 0);
		}
		else if (speed < 0) 
		{
			analogWrite(this->in1pin, 0);
			analogWrite(this->in2pin, (int)(abs(speed) * 255) );
		}
		else if (speed == 0) {
			analogWrite(this->in1pin, defaultOnZero * 255);
			analogWrite(this->in2pin, defaultOnZero * 255);
		}
	}
}

/*
	Makes the motor stop or coast.

	@param value - value LOW or HIGH
*/
void Motor::outputBool(int value) {
	if(disabled){
		return;
	}

	if (enpin == -1) {
		analogWrite(this->in1pin, value);
		analogWrite(this->in2pin, value);
	} else {
		digitalWrite(this->in1pin, value * 255);
		digitalWrite(this->in2pin, value * 255);
		analogWrite(this->enpin, 0);
	}
}

void Motor::disableOutput()
{
	disabled = HIGH;

	if (this->enpin == -1) {
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

int Motor::getNumPins()
{
	if (this->enpin == -1) {
		return 2;
	} else {
		return 3;
	}
}