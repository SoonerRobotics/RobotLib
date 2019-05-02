#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>


class Encoder
{
	enum direction{
		CW = 1,
		CCW = 2,
	};

	enum mode{
		QUADRATURE = 1,
		HALL = 2,
	};

	public:
		Encoder();
		
		Encoder(int pinA, int pinB);
		
		Encoder(int pinA, int pinB, float K);

		Encoder(int pin, direction w, float K);

		Encoder(int pin, direction w);
		
		void operator=(const Encoder& encoder);
		
		void process();
	
		long getTicks();
		
		float getValue();
		
		void reset();
		
		void setPinA(int pinA);

		void setType(mode e);

		void setDirection(direction w);
		
		void setPinB(int pinB);
		
		void setConstant(float K);
	
	private:
		volatile long ticks;
		
		int A;
		
		int B;
		
		float K;

		mode type;

		direction d;

};

#endif