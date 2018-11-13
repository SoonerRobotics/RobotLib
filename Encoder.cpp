#include "Encoder.h"

/*
	Constructor
*/
Encoder::Encoder()
{
	this->A = -1;
	this->B = -1;
	this->K = 1;
	this->ticks = 0;
}

/*
	Sets up encoder with pin numbers.

	@param pinA - pin for first sensor
	@param pinB - pin for second sensor

*/
Encoder::Encoder(int pinA, int pinB)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
	this->K = 1;
	this->ticks = 0;
}

/*
	Sets up encoder.

	@param pinA - pin for first sensor

	@param pinB - pin for second sensor

	@param K - 1/number of ticks per rotation?
*/

Encoder::Encoder(int pinA, int pinB, float K)
{
	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
	this->K = K;
	this->ticks = 0;
}

/*
	Equal sign copies over another Encoder object's variables

	@param encoder - existing Encoder object to be copied
*/
void Encoder::operator=(const Encoder& encoder)
{
	pinMode(encoder.A, INPUT);
	pinMode(encoder.B, INPUT);
	
	this->A = encoder.A;
	this->B = encoder.B;
	this->ticks = encoder.ticks;
	this->K = encoder.K;
}

/*
	Returns the number of ticks the wheel has rotated

	@return - number of ticks
*/
long Encoder::getTicks()
{
	return this->ticks;
}

/*
	Returns number of rotations

	@return - number of rotations
*/
float Encoder::getValue()
{
	return (K * this->ticks);
}

/*
	not sure what this does because don't they end up balancing out?
*/
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

/*
	Starts over counting rotations.
*/
void Encoder::reset()
{
	this->ticks = 0;	
}

/*
	Sets pin for second sensor

	@param pinB - pin number for second sensor
*/
void Encoder::setPinA(int pinA)
{
	this->A = pinA;
}

/*
	Sets pin for second sensor

	@param pinB - pin number for second sensor
*/
void Encoder::setPinB(int pinB)
{
	this->B = pinB;
}

/*
	Sets constant k for encoder.

	@param K - 1/number of ticks per rotation
*/
void Encoder::setConstant(float K)
{
	this->K = K;
}