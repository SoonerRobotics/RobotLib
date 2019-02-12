#include "AnalogDevice.h"

/*
	Default constructor for AnalogDevice.
*/
AnalogDevice::AnalogDevice()
{
	this->pin = -1;
	this->type = -1;
}

/*
	Constructor for AnalogDevice object. Used for reading/writing from/to analog devices.

	@param pin - pin used for reads and writes. Must be analog pin.
	@param type - Determines the mode of the pin and function of device. INPUT or OUTPUT
*/
AnalogDevice::AnalogDevice(int pin, int type)
{
	//Set the class varaibles
	this->pin = pin;
	this->type = type;
	
	//Set-up the Arduino with the information provided
	pinMode(pin, type);
}

/*
	Equals operator for AnalogDevice.

	@param analogDevice - an existing AnalogDevice that we want a copy of (essentailly).
*/
void AnalogDevice::operator=(const AnalogDevice& analogDevice)
{
	//Set the varaibles to match
	this->pin = analogDevice.pin;
	this->type = analogDevice.type;

	//Presumably pinMode() has already been updated
}

/*
	Updates the class variables and the Arduino configuration

	@param pin - pin used for reads and writes. Must be analog pin.
	@param type - Determines the mode of the pin and function of device. INPUT or OUTPUT
*/
void AnalogDevice::update(int pin, int type)
{
	//Change class varaibles
	this->pin = pin;
	this->type = type;
	
	//Update Arduino's pinMode
	pinMode(pin, type);	
}

/*
	Writes a value to the AnalogDevices analog pin.

	@param value - value written to the analog pin.
*/
void AnalogDevice::write(int value)
{	
	//Check that the value makes sense
	if(value >= 0 || value <=255)
	{
		analogWrite(pin, value);
	}	
}

/*
	Reads the value on the AnalogDevices analog pin.

	@return value on the AnalogDevice's pin
*/
int AnalogDevice::read()
{
	int value = analogRead(pin);
	return value;
}