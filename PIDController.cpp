#include "PIDController.h"

PIDController::PIDController(float process_init, float *k)
{
    last_process_var = process_init;
    err = 0;
    integrator = 0;

    kP = k[0];
    kI = k[1];
    kD = k[2];

    low = -1;
    high = 1;
}

void PIDController::reinitialize(float process_init)
{
    last_process_var = process_init;

    err = 0;
    integrator = 0;
}

float PIDController::GetOutput(float setpoint, float process)
{
    err = setpoint - process;
    float P = kP * err;

    integrator += err;
    integrator = coerce(integrator, high, low);
    float I = kI * integrator;

    float delta = process - last_process_var;
    float D = kD * delta;

    float output = coerce(P + I + D, high, low);

    last_process_var = process;

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

void PIDController::SetOutputRange(float upper, float lower)
{
	high = upper;
	low = lower;
}

PIDController::~PIDController()
{
    //dtor
}
