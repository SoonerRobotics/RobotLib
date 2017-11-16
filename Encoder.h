#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
	public:
		Encoder(int pinA, int pinB);
		
		void process();
	
		int getTicks();
		
		void reset();
	
	private:
		int ticks;
		
		int A;
		
		int B;
		
};

#endif