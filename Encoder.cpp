#include "Encoder.h"

Encoder::Encoder()
{
	this->A = -1;
	this->B = -1;
	this->K = 1;
	this->ticks = 0;
}

Encoder::Encoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
	this->K = 1;
	this->ticks = 0;
}

Encoder::Encoder(int pinA, int pinB, float K)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
	this->K = K;
	this->ticks = 0;
}

void Encoder::operator=(const Encoder& encoder)
{
	pinMode(encoder.A, INPUT);
	pinMode(encoder.B, INPUT);
	
	this->A = encoder.A;
	this->B = encoder.B;
	this->ticks = encoder.ticks;
	this->K = encoder.K;
}

long Encoder::getTicks()
{
	return this->ticks;
}

float Encoder::getValue()
{
	return (K * this->ticks);
}

void Encoder::process()
{
	if(digitalRead(this->A) == digitalRead(this->B))
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

void Encoder::setConstant(float K)
{
	this->K = K;
}