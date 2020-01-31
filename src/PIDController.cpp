#include "PIDController.h"


/********************************************/
//          CONSTRUCTORS
/********************************************/

/**
 * @brief Construct a new PIDController object
 *
 */
PIDController::PIDController()
{
    // PID values
    this->integrator = 0.0;
    this->error = 0.0;

    // States
    this->prev_error = 0.0;
    this->last_state = 0.0;

    // Equation constants
    this->kP = 0.0;
    this->kI = 0.0;
    this->kD = 0.0;

    // Boundary control
    this->high = 1.0;
    this->low = -1.0;
    this->is_bounded = true;

    // Timing
    this->last_time = micros();
    this->dt = 0.0;
}


/**
 * @brief Construct a new PIDController object
 *
 * @param init_state starting state of the system
 * @param kp proportional coefficient
 * @param ki integral coefficient
 * @param kd derivative coefficient
 */
PIDController::PIDController(float init_state, float kp, float ki, float kd)
{
    // PID values
    this->integrator = 0.0;
    this->error = 0.0;

    // States
    this->prev_error = 0.0;
    this->last_state = init_state;

    // Equation constants
    this->kP = kp;
    this->kI = ki;
    this->kD = kd;

    // Boundary control
    this->high = 1.0;
    this->low = -1.0;
    this->is_bounded = true;

    // Timing
    this->last_time = micros();
    this->dt = 0.0;
}


/**
 * @brief Copy and assign a PIDController into another one
 *
 * @param pid a PID controller to copy and assign
 */
void PIDController::operator=(const PIDController& pid)
{
    // PID values
    this->integrator = pid.integrator;
    this->error = pid.error;

    // States
    this->prev_error = pid.prev_error;
    this->last_state = pid.last_state;

    // Equation constants
    this->kP = pid.kP;
    this->kI = pid.kI;
    this->kD = pid.kD;

    // Boundary control
    this->high = pid.high;
    this->low = pid.low;
    this->is_bounded = pid.is_bounded;

    // Timing
    this->last_time = pid.last_time;
    this->dt = pid.dt;
}


/********************************************/
//          SETTERS
/********************************************/

/**
 * @brief Initializes the PID controller
 *
 * @param init_state starting state of the system
 */
void PIDController::begin(float init_state)
{
    // PID values
    this->integrator = 0.0;
    this->error = 0.0;

    // States
    this->prev_error = 0.0;
    this->last_state = init_state;

    // Timing
    this->last_time = micros();
    this->dt = 0.0;
}


/**
 * @brief Initializes a PIDController
 *
 * @param init_state starting state of the system
 * @param kp proportional coefficient
 * @param ki integral coefficient
 * @param kd derivative coefficient
 */
void PIDController::begin(float init_state, float kp, float ki, float kd)
{
    // PID values
    this->integrator = 0.0;
    this->error = 0.0;

    // States
    this->prev_error = 0.0;
    this->last_state = init_state;

    // Equation constants
    this->kP = kp;
    this->kI = ki;
    this->kD = kd;

    // Timing
    this->last_time = micros();
    this->dt = 0.0;
}


/**
 * @brief Resets the PID controller's state.
 * Note: you must reinitialize the PID with begin() before running it again.
 *
 */
void PIDController::reset()
{
    // PID values
    this->integrator = 0.0;
    this->error = 0.0;

    // States
    this->prev_error = 0.0;
    this->last_state = 0.0;
}


/**
 * @brief Sets if the output/result is bounded by a clamp
 *
 * @param is_bounded
 */
void PIDController::setBounded(bool is_bounded)
{
    this->is_bounded = is_bounded;
}


/**
 * @brief Sets the clamping boundaries on the output/result
 *
 * @param lower Lowest allowable output/result
 * @param upper Highest allowable output/result
 */
void PIDController::setOutputRange(float lower, float upper)
{
    this->low = lower;
    this->high = upper;
}


/********************************************/
//          GETTERS
/********************************************/

/**
 * @brief Updates the PID equation and returns the result
 *
 * @param target_state the goal state of the system
 * @param cur_state the current state of the system
 * @return float the output/result/control signal needed to optimize the state
 */
float PIDController::update(float target_state, float cur_state)
{
    // Declare local variables
    float P, I, D;
    float result;
    float slope;
    unsigned long cur_time;

    // Get the time step
    cur_time = micros();
    this->dt = (float)(cur_time - this->last_time) / MICROS_IN_A_SECOND;

    // Calculate error
    this->error = target_state - cur_state;

    // Integrate error using trapezoidal Riemann sums
    this->prev_error = target_state - this->last_state;
    this->integrator += 0.5 * (this->error + this->prev_error) * this->dt;

    // Find the slope of the error curve using secant approximation
    slope = (this->error - this->prev_error) / this->dt;

    // Apply PID gains
    P = this->kP * this->error;
    I = this->kI * this->integrator;
    D = this->kD * slope;

    // Sum P, I, D to get the result of the equation
    // Bind the output if needed
    result = this->is_bounded ? RLUtil::clamp(P + I + D, this->low, this->high) : (P + I + D);

    // Update timing and increment to the next state
    this->last_state = cur_state;
    this->last_time = cur_time;

    // Return the PID result
    return result;
}


/**
 * @brief Gets the integral part of the PID controller
 *
 * @return float the integral component of the PID
 */
float PIDController::getIntegratorValue()
{
    return this->kI * this->integrator;
}
