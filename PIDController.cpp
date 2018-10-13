#include "PIDController.h"

PIDController::PIDController()
{
    this->last_process_var = 0;
    this->err = 0;
	this->integrator = 0;

    this->kP = 0;
    this->kI = 0;
    this->kD = 0;

    this->low = -1;
    this->high = 1;	
}

PIDController::PIDController(float process_init, float kp, float ki, float kd)
{
    this->last_process_var = process_init;
    this->err = 0;
	this->integrator = 0;

	this->kP = kp;
    this->kI = ki;
    this->kD = kd;

    this->low = -1;
    this->high = 1;
}

void PIDController::operator=(const PIDController& pidController)
{
	this->last_process_var = pidController.last_process_var;
	this->kP = pidController.kP;
	this->kI = pidController.kI;
	this->kD = pidController.kD;
	this->err = pidController.err;
	this->integrator = pidController.integrator;
	this->low = pidController.low;
	this->high = pidController.high;
}

void PIDController::initialize(float process_init, float kp, float ki, float kd)
{
    this->last_process_var = process_init;
	
	this->kP = kp;
    this->kI = ki;
    this->kD = kd;

    this->err = 0;
    this->integrator = 0;
	
	//lastTime = millis();
}

float PIDController::getOutput(float setpoint, float process)
{
    this->err = setpoint - process;
    float P = kP * err;

    this->integrator += err;
    this->integrator = coerce(integrator, high, low); //Should it be like this?
    float I = this->kI * this->integrator;

    float delta = process - this->last_process_var;
    float D = this->kD * delta;

    float output = coerce(P + I + D, this->high, this->low);

    this->last_process_var = process;

    return output;
}

float PIDController::coerce(float val, float upper, float lower)
{
    if(val > upper)
    {
        return upper;
    }
    else if(val < lower)
    {
        return lower;
    }
    return val;
}

void PIDController::setOutputRange(float upper, float lower)
{
	this->high = upper;
	this->low = lower;
}