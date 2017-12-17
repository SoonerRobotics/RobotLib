#include "DigitalDevice.h"

DigitalDevice::DigitalDevice()
{
	this->pin = -1;
	this->type = -1;
}

DigitalDevice::DigitalDevice(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);
}

void DigitalDevice::operator=(const DigitalDevice& digitalDevice)
{
	this->pin = digitalDevice.pin;
	this->type = digitalDevice.type;
}

void DigitalDevice::update(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);	
}

void DigitalDevice::write(int value)
{
	if(value == HIGH || value == LOW || value == 1 || value == 0)
	{
		digitalWrite(pin, value);
	}
}

int DigitalDevice::read()
{
	int value = digitalRead(pin);
	return value;
}