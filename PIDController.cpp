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

PIDController::PIDController(float process_init, Collection<float> K)
{
    this->last_process_var = process_init;
    this->err = 0;
	this->integrator = 0;

	this->kP = K.get(0);
    this->kI = K.get(1);
    this->kD = K.get(2);

    this->low = -1;
    this->high = 1;
}

void PIDController::initialize(float process_init, Collection<float> K)
{
    this->last_process_var = process_init;
	
	this->kP = K.get(0);
    this->kI = K.get(1);
    this->kD = K.get(2);

	Serial.print(kP);
	Serial.print(kI);
	Serial.println(kD);
	
    this->err = 0;
    this->integrator = 0;
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