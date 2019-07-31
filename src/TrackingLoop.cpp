
#include "TrackingLoop.h"


/**
 * @brief Construct a new Tracking Loop object
 * 
 */
TrackingLoop::TrackingLoop()
{
    // initialize the PI controllers
    this->kp = 40.0;
    this->ki = 900.0;
    this->vel_pid.begin(0, this->kp, this->ki, 0);
    this->accel_pid.begin(0, this->kp, this->ki, 0);
    
    // Unbounded output required on the PID
    this->vel_pid.setBounded(false);
    this->accel_pid.setBounded(false);

    // initialize the estimator
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;
    this->accel_estimate = 0.0;
}


/**
 * @brief Construct a new Tracking Loop object with PI gains
 * 
 * @param kp proportional gain
 * @param ki integral gain
 */
TrackingLoop::TrackingLoop(float kp, float ki)
{
    // initialize the PI controller
    this->kp = kp;
    this->ki = ki;
    this->vel_pid.begin(0, this->kp, this->ki, 0);
    this->accel_pid.begin(0, this->kp, this->ki, 0);

    // Unbounded output required on the PID
    this->vel_pid.setBounded(false);
    this->accel_pid.setBounded(false);

    // initialize the estimator
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;
    this->accel_estimate = 0.0;
}


/**
 * @brief Copy assignment operation
 * 
 * @param tracker another tracking loop
 */
void TrackingLoop::operator=(const TrackingLoop& tracker)
{
    // copy values from one object to another
    // PID
    this->accel_pid = tracker.accel_pid;
    this->vel_pid = tracker.vel_pid;
    this->kp = tracker.kp;
    this->ki = tracker.ki;
    
    // Timing
    this->last_time = tracker.last_time;

    // Estimation vars
    this->pos_estimate = tracker.pos_estimate;
    this->vel_estimate = tracker.vel_estimate;
    this->accel_estimate = tracker.accel_estimate;
}


/**
 * @brief Resets the tracking loop
 * 
 */
void TrackingLoop::reset()
{
    // set estimates to 0
    this->pos_estimate = 0.0;
    this->vel_estimate = 0.0;
    this->accel_estimate = 0.0;

    // Reset the PIDs
    this->vel_pid.reset();
    this->vel_pid.begin(0, this->kp, this->ki, 0);
    this->accel_pid.reset();
    this->accel_pid.begin(0, this->kp, this->ki, 0);

    // reset the time tracking
    this->last_time = millis();
}


/**
 * @brief Updates the tracking loop with a position measurement
 * 
 * @param measurement the encoder position
 */
void TrackingLoop::update(float measurement)
{
    // Declare local vars
    float dt;
    float model_vel;

    // Get the elapsed time (sec)
    dt = (float)(millis() - this->last_time) / 1000.0;
    
    // Estimate the position and velocity from the state estimates
    this->pos_estimate += this->vel_estimate * dt;
    model_vel = this->vel_estimate + (this->accel_estimate * dt);

    // Get new velocity estimate from PID controller by comparing position estimate to actual position
    this->vel_estimate = this->vel_pid.update(measurement, this->pos_estimate);

    // From "measured" velocity we can compute an acceleration in a similar way
    this->accel_estimate = this->accel_pid.update(this->vel_estimate, model_vel);

    // Set the last time to now
    this->last_time = millis();
}


/**
 * @brief Get the velocity estimate for this tracker
 * 
 * @return float velocity estimate
 */
float TrackingLoop::getVelocityEstimate()
{
    return this->vel_estimate;
}


/**
 * @brief Get an acceleration estimate from the tracker
 * 
 * @return float acceleration estimate
 */
float TrackingLoop::getAccelEstimate()
{
    return this->accel_estimate;
}