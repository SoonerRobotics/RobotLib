#include <QuadratureEncoder.h>


/**
 * @brief Construct a new Quadrature Encoder object
 * 
 */
QuadratureEncoder::QuadratureEncoder()
{
    // Position
    this->K = 1;
    this->ticks = 0;

    // Pins
    this->pin_A = -1;
    this->pin_B = -1;
}


/**
 * @brief Sets up encoder with pin numbers.
 * 
 * @param A channel A encoder pin
 * @param B channel B encoder pin
 * @param K constant for converting ticks to real life units
 */
QuadratureEncoder::QuadratureEncoder(int A, int B, float K)
{
    pinMode(A, this->pin_mode);
    pinMode(B, this->pin_mode);
    
    // Position
    this->K = K;
    this->ticks = 0;

    // Pins
    this->pin_A = A;
    this->pin_B = B;
}

/**
 * @brief Sets up encoder with pin numbers.
 * 
 * @param A channel A encoder pin
 * @param B channel B encoder pin
 * @param K constant for converting ticks to real life units
 * @param pullup set true to enable pullup input mode
 */
QuadratureEncoder::QuadratureEncoder(int A, int B, float K, int pullup)
{
    if (pullup) {
        this->pin_mode = INPUT_PULLUP;
    }

    pinMode(A, this->pin_mode);
    pinMode(B, this->pin_mode);
    
    // Position
    this->K = K;
    this->ticks = 0;

    // Pins
    this->pin_A = A;
    this->pin_B = B;
}


/**
 * @brief Copy a quadrature encoder to this object
 * 
 * @param quad_encoder Quadrature encoder to copy
 */
void QuadratureEncoder::operator=(const QuadratureEncoder &quad_encoder)
{
    pinMode(quad_encoder.pin_A, quad_encoder.pin_mode);
    pinMode(quad_encoder.pin_B, quad_encoder.pin_mode);
    
    // Position
    this->K = quad_encoder.K;
    this->ticks = quad_encoder.ticks;

    // Pins
    this->pin_A = quad_encoder.pin_A;
    this->pin_B = quad_encoder.pin_B;	
}


/**
 * @brief Sets up encoder with pin numbers outside the constructor.
 * 
 * @param A channel A encoder pin
 * @param B channel B encoder pin
 * @param K constant for converting ticks to real life units
 */
void QuadratureEncoder::begin(int A, int B, float K)
{
    pinMode(A, this->pin_mode);
    pinMode(B, this->pin_mode);
    
    // Position
    this->K = K;
    this->ticks = 0;

    // Pins
    this->pin_A = A;
    this->pin_B = B;
}

/**
 * @brief Sets up encoder with pin numbers outside the constructor.
 * 
 * @param A channel A encoder pin
 * @param B channel B encoder pin
 * @param K constant for converting ticks to real life units
 * @param pullup set true to enable pullup input mode
 */
void QuadratureEncoder::begin(int A, int B, float K, int pullup)
{
    if (pullup) {
        this->pin_mode = INPUT_PULLUP;
    }
    
    pinMode(A, this->pin_mode);
    pinMode(B, this->pin_mode);
    
    // Position
    this->K = K;
    this->ticks = 0;

    // Pins
    this->pin_A = A;
    this->pin_B = B;
}

/**
 * @brief Set the pinMode for both pins to pull up inputs
 * 
 */
void QuadratureEncoder::pullup()
{
    this->pin_mode = INPUT_PULLUP;
    pinMode(this->pin_A, this->pin_mode);
    pinMode(this->pin_B, this->pin_mode);
}

/**
 * @brief Process the ticks as they come in from an interrupt handler or from polling
 * 
 */
void QuadratureEncoder::process()
{
    // Compare the phase of the two pulses in order to find direction
    if(digitalRead(this->pin_A) == digitalRead(this->pin_B))
      {
        ++ticks;
      }
      else
      {
        --ticks;
    }
}


/**
 * @brief Reset the ticks to zero
 * 
 */
void QuadratureEncoder::reset()
{
    this->ticks = 0;
}


/**
 * @brief Get the number of ticks tracked by the encoder
 * 
 * @return long The number of ticks 
 */
long QuadratureEncoder::getTicks()
{
    return this->ticks;
}


/**
 * @brief Get the value measured by the encoder
 * 
 * @return float The ticks converted into real life units
 */
float QuadratureEncoder::getValue()
{
    return (this->K * (float)this->ticks);
}
