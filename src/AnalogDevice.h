#ifndef ANALOGDEVICE_H
#define ANALOGDEVICE_H

#include <Arduino.h>

class AnalogDevice
{
	public:
		AnalogDevice();
		
		AnalogDevice(int pin, int type);
		
		void operator=(const AnalogDevice& analogDevice);
		
		void update(int pin, int type);
		
		void write(int value);
		
		int read();
	
	private:
		int pin;
		
		int type;
};

#endif