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
	Serial.print(kP);
    this->kI = K.get(1);
	Serial.print(kI);
    this->kD = K.get(2);
	Serial.print(kD);

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
	
	lastTime = millis();
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

	/*
	Serial.print("\t");
	Serial.print(kP);
	Serial.print("\t");
	Serial.print(kI);
	Serial.print("\t");
	Serial.print(kD);
	*/
	
    return output;
}

float PIDController::getOutput2(float setpoint, float process)
{
	unsigned long now = millis();
	
		/*Compute all the working error variables*/
		double input = process;
		double error = setpoint - input;
		double dInput = (input - lastInput);
		outputSum+= (kI * error);

		/*Add Proportional on Measurement, if P_ON_M is specified*/
		//if(!pOnE) outputSum-= kP * dInput;

		if(outputSum > 1) outputSum= 1;
		else if(outputSum < -1) outputSum= -1;

		/*Add Proportional on Error, if P_ON_E is specified*/
		double output;
		//if(pOnE)
			output = kP * error;
		//else output = 0;

		/*Compute Rest of PID Output*/
		output += outputSum - kD * dInput;

	    if(output > 1) output = 1;
		else if(output < -1) output = -1;

		/*Remember some variables for next time*/
		lastInput = input;
		lastTime = now;
		
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