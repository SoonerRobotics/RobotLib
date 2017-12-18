#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{
	public:
		Motor();
		
		void operator=(const Motor& motor);
		
		void begin(int A, int B, int Enb);
		
		void output(float out);
		
	private:
		int A;
		int B;
		int enable;
		
		float coerce(float val, float upper, float lower);
};

#endif