#include "HallEffectEncoder.h"


/**
 * @brief Construct a new empty Hall Effect Encoder object
 * 
 */
HallEffectEncoder::HallEffectEncoder()
{
    // Position
    this->ticks = 0;
    this->K = 1;

    // Configuration
    this->pin = -1;
    this->direction = 0;
}


/**
 * @brief Construct a new Hall Effect Encoder object fully
 * 
 * @param pin The pin the sensor is connected to
 * @param direction The direction the shaft is spinning
 * @param K The tick constant for distance calculations
 */
HallEffectEncoder::HallEffectEncoder(int pin, int direction, float K)
{
	pinMode(pin, INPUT);
	
	// Position
    this->ticks = 0;
    this->K = K;

    // Configuration
    this->pin = pin;
    this->direction = direction;
}


/**
 * @brief Copy a hall effect encoder to this object
 * 
 * @param hall_encoder Another hall effect encoder object
 */
void HallEffectEncoder::operator=(const HallEffectEncoder& hall_encoder)
{
    pinMode(hall_encoder.pin, INPUT);

	// Position
	this->ticks = hall_encoder.ticks;
	this->K = hall_encoder.K;

	// Configuration
	this->pin = hall_encoder.pin;
	this->direction = hall_encoder.direction;
}


/**
 * @brief Set up a hall effect encoder outside the constructor
 * 
 * @param pin The pin the sensor is connected to
 * @param direction The direction the shaft is spinning
 * @param K The tick constant for distance calculations
 */
void HallEffectEncoder::begin(int pin, int direction, float K)
{
	pinMode(pin, INPUT);

	// Position
    this->ticks = 0;
    this->K = K;

    // Configuration
    this->pin = pin;
    this->direction = direction;
}


/**
 * @brief Set the direction the shaft is spinning so the ticks are counted correctly
 * 
 * @param direction CLOCKWISE or COUNTERCLOCKWISE (0 or 1 respectively)
 */
void HallEffectEncoder::setDirection(int direction)
{
    this->direction = direction;
}


/**
 * @brief Process the ticks as they come in from an interrupt handler or from polling
 * 
 */
void HallEffectEncoder::process()
{
    if (this->direction == CLOCKWISE)
    {
        ++this->ticks;
    }
    else
    {
        --this->ticks;
    }
}


/**
 * @brief Reset the ticks to zero
 * 
 */
void HallEffectEncoder::reset()
{
    this->ticks = 0;
}


/**
 * @brief Get the number of ticks tracked by the encoder
 * 
 * @return long The number of ticks 
 */
long HallEffectEncoder::getTicks()
{
    return this->ticks;
}


/**
 * @brief Get the value measured by the encoder
 * 
 * @return float The ticks converted into real life units
 */
float HallEffectEncoder::getValue()
{
    return (this->K * (float)this->ticks);
}
