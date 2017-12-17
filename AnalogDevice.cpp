#include "AnalogDevice.h"

AnalogDevice::AnalogDevice()
{
	this->pin = -1;
	this->type = -1;
}

AnalogDevice::AnalogDevice(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);
}

void AnalogDevice::operator=(const AnalogDevice& analogDevice)
{
	this->pin = analogDevice.pin;
	this->type = analogDevice.type;
}

void AnalogDevice::update(int pin, int type)
{
	this->pin = pin;
	this->type = type;
	
	pinMode(pin, type);	
}

void AnalogDevice::write(int value)
{	
	if(value >= 0 || value <=255)
	{
		analogWrite(pin, value);
	}		
}

int AnalogDevice::read()
{
	int value = analogRead(pin);
	return value;
}