#include "StepperMotor.h"

StepperMotor::StepperMotor()
{
	this->STEP = NULL;
	this->DIR = NULL;
	this->enable = NULL;
}

void StepperMotor::operator=(const StepperMotor& motor)
{
	this->STEP = motor.STEP;
	this->DIR = motor.DIR;
	this->enable = motor.enable;
	
	this->rpm = motor.rpm;
	this->currentSteps = motor.currentSteps;
	this->stepsPerRotation = motor.stepsPerRotation;
}


void StepperMotor::begin(int step, int dir, int enable, int stepsPerRotation)
{
	this->STEP = step;
	this->DIR = dir;
	this->enable = enable;
	this->stepsPerRotation = stepsPerRotation;
	
	pinMode(STEP, OUTPUT);
	pinMode(DIR, OUTPUT);
	
	if(enable != -1)
	{
		pinMode(enable, OUTPUT);
		digitalWrite(enable, LOW);
	}
}

void StepperMotor::setRPM(float speed)
{
	this->rpm = abs(speed);
}

void StepperMotor::step(int steps)
{
	int direction = 0;
	bool millisecond_interval = true;
	
	if(steps < 0)
	{
		digitalWrite(this->DIR, LOW);
		direction = -1;
	}
	else
	{
		digitalWrite(this->DIR, HIGH);
		direction = 1;
	}
	
	//Determine how many microseconds we want to wait, and convert to an integer
	double totalTime = (static_cast<double>(steps) / this->stepsPerRotation) / this->rpm * 60.0 * 1000.0; 	
	double T = (totalTime / steps) / 2;
	
	//Convert to microseconds if delay would be 0.
	if(T < 1)
	{
		T*=1000;
		millisecond_interval = false;
	}
	
	unsigned long stepWait = static_cast<int>(T);
	
	for(int i = 0; i < abs(steps); ++i)
	{
		if(millisecond_interval)
		{
			singleStep(stepWait);
		}
		else
		{
			singleStep_us(stepWait);
		}
		
		this->currentSteps += direction;
	}
}

int StepperMotor::getCurrentSteps()
{
	return this->currentSteps;
}

//Private Functions

void StepperMotor::singleStep(unsigned int stepWait)
{
	digitalWrite(this->STEP, HIGH); // Output high
    delay(stepWait); // Wait
    digitalWrite(this->STEP, LOW); // Output low
    delay(stepWait); // Wait
}

void StepperMotor::singleStep_us(unsigned int stepWait)
{
	digitalWrite(this->STEP, HIGH); // Output high
    delayMicroseconds(stepWait); // Wait
    digitalWrite(this->STEP, LOW); // Output low
    delayMicroseconds(stepWait); // Wait
}