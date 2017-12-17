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

void DigitalDevice::setPin(int pinA)
{
	
}

void DigitalDevice::setType(int type)
{
	
}

void DigitalDevice::write(int value)
{
	
}

int DigitalDevice::read()
{
	
}