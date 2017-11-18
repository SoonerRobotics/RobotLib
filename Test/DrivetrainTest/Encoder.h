#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
	public:
		Encoder();
		
		Encoder(int pinA, int pinB);
		
		void operator=(const Encoder& encoder);
		
		void process();
	
		int getTicks();
		
		void reset();
		
		void setPinA(int pinA);
		
		void setPinB(int pinB);
	
	private:
		int ticks;
		
		int A;
		
		int B;
		
};

#endif