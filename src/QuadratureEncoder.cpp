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

    // Configuration
    this->resolution = quad_encoder.resolution;
    
    // Position
    this->K = quad_encoder.K;
    this->ticks = quad_encoder.ticks;
    this->lastState = quad_encoder.lastState;

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
 * @brief Set the encoder resolution. 1x, 2x, or 4x.
 * 
 * For 1x resolution, have an interrupt on the A pin on either rise or fall.
 * For 2x resolution, have an interrupt on the A pin on both rise and fall (change).
 * For 4x resolution, have an interrupt on both the A and B pins on both rise and fall (change).
 * All interrupts should call the process function.
 */
void QuadratureEncoder::setResolution(int resolution) {
    if (resolution == 1 || resolution == 2 || resolution == 4) {
        this->resolution = resolution;
    }
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
    if (this->resolution == 1) {
        // 1x resolution

        // Compare the phase of the two pulses in order to find direction
        if(digitalRead(this->pin_A) == digitalRead(this->pin_B))
        {
            ++ticks;
        }
        else
        {
            --ticks;
        }
    } else if (this -> resolution == 2) {
        // 2x resolution

        int curState = digitalRead(this->pin_A) << 1 | digitalRead(this->pin_B);

        // 00 -> 11 -> 00 -> 11 is one direction
        // 10 -> 01 -> 10 -> 01 is the other direction
        if ((lastState == 0b11 && curState == 0b00) ||
            (lastState == 0b00 && curState == 0b11)) {
                ++ticks;
            }
        else if ((lastState == 0b10 && curState == 0b01) ||
            (lastState == 0b01 && curState == 0b10)) {
                --ticks;
            }

        // Set last state to current state
        lastState = curState;
    } else if (this -> resolution == 4) {
        // 4x resolution 
        int curState = digitalRead(this->pin_A) << 1 | digitalRead(this->pin_B);

        // States will go 00 -> 01 -> 11 -> 10 -> 00 (grey code).
        // Forward through them is one direction, backwards is the other direction.

        // curState ^ lastState is XOR of the states. If they are 0x11, then two bits
        // changed which violates grey code and is invalid. Similarly, if the state
        // doesn't change it is invalid beause at least one bit should change.
        if (((curState ^ lastState) != 0x11) && (curState != lastState)) {
            // 2 bit state. Right hand bit of prev XOR left hand bit of current
            // gives 0 if clockwise rotation and 1 if counter clockwise rotation.
            // From QEI implementation https://os.mbed.com/users/aberk/code/QEI/
            int change = (lastState & 0b01) ^ ((curState & 0b10) >> 1);
 
            if (change == 0) {
                change = -1;
            }
 
            ticks -= change;
        }

        // Set last state to current state
        lastState = curState;
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
