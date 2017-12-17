#ifndef DIGITALDEVICE_H
#define DIGITALDEVICE_H

#include <Arduino.h>

class DigitalDevice
{
	public:
		DigitalDevice();
		
		DigitalDevice(int pin, int type);
		
		void operator=(const DigitalDevice& digitalDevice);
		
		void setPin(int pinA);
		
		void setType(int type);
		
		void write(int value);
		
		int read();
	
	private:
		int pin;
		
		int type;
};

#endif