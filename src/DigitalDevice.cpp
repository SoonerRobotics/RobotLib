#include "DigitalDevice.h"

/*
	Constructor
*/
DigitalDevice::DigitalDevice()
{
	this->pin = -1;
	this->type = -1;
}

/*
	Gives the digital device a pin and makes it input or output

	@param pin - pin number

	@param type - says whether the pin is input or output
*/
DigitalDevice::DigitalDevice(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);
}

/*
	Makes equal sign copy another digitalDevice

	@param digitalDevice - DigitalDevice object
*/
void DigitalDevice::operator=(const DigitalDevice& digitalDevice)
{
	this->pin = digitalDevice.pin;
	this->type = digitalDevice.type;
}

/*
	You can change the pin number and what it does!

	@param pin - pin number

	@param type - int that says whether it's input or output
*/
void DigitalDevice::update(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);	
}

/*
	
*/
void DigitalDevice::write(int value)
{
	if(value == HIGH || value == LOW || value == 1 || value == 0)
	{
		digitalWrite(pin, value);
	}
}

void DigitalDevice::pullUp()
{
	digitalWrite(pin, HIGH);
}

void DigitalDevice::pullDown()
{
	digitalWrite(pin, LOW);
}

int DigitalDevice::read()
{
	int value = digitalRead(pin);
	return value;
}