#include "StepperMotor.h"

StepperMotor::StepperMotor()
{
	this->STEP = -1;
	this->DIR = -1;
	this->enable = -1;
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
		digitalWrite(enable, HIGH);
	}
}

void StepperMotor::setRPM(float speed)
{
	this->rpm = abs(speed);
}

void StepperMotor::step(int steps)
{
	//Enable the motor for movement
	if(this->enable != -1)
	{
		digitalWrite(this->enable, LOW);
	}
	
	int direction = 0;
	bool millisecond_interval = false;
	
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
	double totalTime = (static_cast<double>(abs(steps)) / this->stepsPerRotation) / this->rpm * 60.0 * 1000.0 * 1000.0; 	
	double T = (totalTime / abs(steps)) / 2;
	
	//Convert to milliseconds if delay would be too big for us.
	if(T > 5000)
	{
		T/=1000;
		millisecond_interval = true;
	}
	
	unsigned long stepWait = static_cast<unsigned long>(T);
	
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
	
	//Disable the motor to let it cool off
	if(this->enable != -1)
	{
		digitalWrite(this->enable, HIGH);
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