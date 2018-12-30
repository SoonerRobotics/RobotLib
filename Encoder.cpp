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
	s = QUADRATURE

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
	s = QUADRATURE;

	pinMode(pinA, INPUT);
	pinMode(pinB, INPUT);
	
	this->A = pinA;
	this->B = pinB;
	this->K = K;
	this->ticks = 0;

}

/*
	Sets up hall effect sensor.
	
	@param pin - pin number

	@param w - direction (cw or ccw)

	@param K - constant
*/
Encoder::Encoder(int pin, direction w, float K)
{
	s = HALL;


	pinMode(pin, INPUT);
	
	this->A = pin;
	this->K = K;
	this->ticks = 0;

	this->d = w;

}

/*
	Sets up Hall effect sensor.

	@param pin - pin number

	@param w - enumerated type for direction of spin
*/
Encoder::Encoder(int pin, direction w)
{
	s = HALL;

	pinMode(pin, INPUT);
	
	this->A = pin;
	this->K = 1;
	this->ticks = 0;

	this->d = w;
}

/*
	Equal sign copies over another Encoder object's variables
	IF YOU MAKE NEW VARIABLES FOR THE HALL EFFECT SENSOR DO YOU HAVE TO INITIALIZE THEM FOR QUADRATURE ENCODERS

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

	this->s = encoder.s;
	this->d = encoder.d;
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
	Counts ticks for hall effect encoder or quadrature encoder. Should be called whenever voltage from A changes?
*/
void Encoder::process()
{
	if (s == HALL){
		if(digitalRead(this->A) == digitalRead(this->B))
  		{
    		++ticks;
  		}
  		else
  		{
    		--ticks;
		}
	}
	else{
		if (d == CW)
		{
			++ticks;
		}
		else
		{
			--ticks;
		}
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

/*
	Sets encoder type.

	@param e - type of encoder 
*/
void Encoder::setType(mode e)
{
	this->s = e
}

/*
	Sets direction for Hall effect sensor.

	@param w - clockwise or counterclockwise
*/
void Encoder::setDirection(direction w)
{
	this->d = w;
}
