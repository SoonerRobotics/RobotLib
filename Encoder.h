#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
	public:
		Encoder();
		
		Encoder(int pinA, int pinB);
		
		Encoder(int pinA, int pinB, float K);
		
		void operator=(const Encoder& encoder);
		
		void process();
	
		int getTicks();
		
		float getValue();
		
		void reset();
		
		void setPinA(int pinA);
		
		void setPinB(int pinB);
		
		void setConstant(float K);
	
	private:
		volatile int ticks;
		
		int A;
		
		int B;
		
		float K;
		
};

#endif