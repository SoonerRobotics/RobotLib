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

    // Tolerance
    this->derivative_tolerance = 0;
    this->setpoint_tolerance = 0;
    this->tolerance_enabled = false;

    // Integrator
    this->integrator_min = 1;
    this->integrator_max = -1;
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

    // Tolerance
    this->derivative_tolerance = 0;
    this->setpoint_tolerance = 0;
    this->tolerance_enabled = false;

    // Integrator
    this->integrator_min = 1;
    this->integrator_max = -1;
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

    // Tolerance
    this->derivative_tolerance = pid.derivative_tolerance;
    this->setpoint_tolerance = pid.setpoint_tolerance;
    this->tolerance_enabled = pid.tolerance_enabled;

    // Integrator
    this->integrator_min = pid.integrator_min;
    this->integrator_max = pid.integrator_max;
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


/**
 * @brief Sets the error tolerances for the setpoint error and the error derivative.
 * Output is cut to 0 if the tolerance is enabled
 *
 * @param setpoint_tol Highest allowed error in the state of the system
 * @param derivative_tol Highest allowed derivative error
 * @param apply_tolerance Enables or disables the tolerances
 */
void PIDController::setTolerance(float setpoint_tol, float derivative_tol, bool apply_tolerance)
{
    this->tolerance_enabled = apply_tolerance;
    this->setpoint_tolerance = setpoint_tol;
    this->derivative_tolerance = derivative_tol;
}


/**
 * @brief Set the maximum and minimum values for the integrator
 * This helps prevent integral windup
 *
 * @param min Minimum value of integrator
 * @param max Maximum value of integrator
 */
void PIDController::setIntegratorBounds(float min, float max)
{
    this->integrator_min = min;
    this->integrator_max = max;
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
    this->derivative = (cur_state - this->last_state) / this->dt;

    // Clamp integrator if the integrator boundaries have been set
    if(this->integrator_max > this->integrator_min)
    {
        this->integrator = RLUtil::clamp(this->integrator, this->integrator_min, this->integrator_max);
    }

    // Apply PID gains
    P = this->kP * this->error;
    I = this->kI * this->integrator;
    D = this->kD * this->derivative;

    // Sum P, I, D to get the result of the equation
    if(tolerance_enabled
    && fabs(this->error) < this->setpoint_tolerance
    && fabs(this->derivative) < this->derivative_tolerance)
    {
        result = 0;
    }
    else
    {
        // Bind the output if needed
        result = this->is_bounded ? RLUtil::clamp(P + I + D, this->low, this->high) : (P + I + D);
    }

    // Update timing and increment to the next state
    this->last_state = cur_state;
    this->last_time = cur_time;

    // Return the PID result
    return result;
}


/**
 * @brief Gets the unfiltered integral part of the PID controller
 *
 * @return float the integrator for the PID
 */
float PIDController::getIntegratorValue()
{
    return this->integrator;
}
