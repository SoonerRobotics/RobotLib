#include "StepperMotor.h"

StepperMotor::StepperMotor()
{
	// Pins
	this->STEP = -1;
	this->DIR = -1;
	this->enable = -1;

	// Config
	this->rpm = 0;
	this->stepsPerRotation = 200;

	// Position
	this->currentSteps = 0;
}

void StepperMotor::operator=(const StepperMotor& motor)
{
	// Pins
	this->STEP = motor.STEP;
	this->DIR = motor.DIR;
	this->enable = motor.enable;
	
	// Config
	this->rpm = motor.rpm;
	this->stepsPerRotation = motor.stepsPerRotation;

	// Position
	this->currentSteps = motor.currentSteps;
}


void StepperMotor::begin(int step, int dir, int enable, int stepsPerRotation)
{
	// Pins
	this->STEP = step;
	this->DIR = dir;
	this->enable = enable;

	// Config
	this->stepsPerRotation = stepsPerRotation;
	
	// Set pins
	pinMode(STEP, OUTPUT);
	pinMode(DIR, OUTPUT);
	
	// Set enable pin as needed
	if(enable != -1)
	{
		pinMode(enable, OUTPUT);
		digitalWrite(enable, HIGH);
	}
}


/**
 * @brief Set the RPM of the stepper motor
 * 
 * @param speed the RPM of the motor
 */
void StepperMotor::setRPM(float speed)
{
    this->rpm = abs(speed);
}


/**
 * @brief Move a certain number of steps
 * 
 * @param steps how many steps to move
 */
void StepperMotor::step(int steps)
{
	//Enable the motor for movement
	if(this->enable != -1)
	{
		digitalWrite(this->enable, LOW);
	}
	
	// Initialize direction and timing flags
	int direction = 0;
	bool millisecond_interval = false;
	
	// Determine direction
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
	
	// Cast the step wait period to a long
	unsigned long stepWait = static_cast<unsigned long>(T);
	
	// Perform the steps
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


/**
 * @brief Resets the step counter
 * 
 */
void StepperMotor::reset()
{
	this->currentSteps = 0;
}


/**
 * @brief Gets the current amount of steps taken by this motor
 * 
 * @return int step counter
 */
int StepperMotor::getCurrentSteps()
{
    return this->currentSteps;
}




//Private Functions

/**
 * @brief Perform a single step
 * 
 * @param stepWait time to wait between each output
 */
void StepperMotor::singleStep(unsigned int stepWait)
{
    digitalWrite(this->STEP, HIGH); // Output high
    delay(stepWait); // Wait
    digitalWrite(this->STEP, LOW); // Output low
    delay(stepWait); // Wait
}


/**
 * @brief Perform a single step
 * 
 * @param stepWait amount of time to wait in microseconds between each output
 */
void StepperMotor::singleStep_us(unsigned int stepWait)
{
    digitalWrite(this->STEP, HIGH); // Output high
    delayMicroseconds(stepWait); // Wait
    digitalWrite(this->STEP, LOW); // Output low
    delayMicroseconds(stepWait); // Wait
}