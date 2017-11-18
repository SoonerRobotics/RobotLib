#include "Encoder.h"

Encoder::Encoder()
{
	this->A = -1;
	this->B = -1;
}

Encoder::Encoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
}

void Encoder::operator=(const Encoder& encoder)
{
	pinMode(encoder.A, INPUT);
	pinMode(encoder.B, INPUT);
	
	this->A = encoder.A;
	this->B = encoder.B;
	this->ticks = encoder.ticks;
}

int Encoder::getTicks()
{
	return this->ticks;
}

void Encoder::process()
{
	if(digitalRead(A) == digitalRead(B))
  	{
    	++ticks;
  	}
  	else
  	{
    	--ticks;
	}
}

void Encoder::reset()
{
	this->ticks = 0;	
}

void Encoder::setPinA(int pinA)
{
	this->A = pinA;
}

void Encoder::setPinB(int pinB)
{
	this->B = pinB;
}