#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor
{
	public:
		StepperMotor();
		
		void operator=(const StepperMotor& motor);
		
		// Setters
		void begin(int step, int dir, int enable = -1, int stepsPerRotation = 200);
		void step(int steps);
		void setRPM(float speed);
		void reset();
		
		// Getters
		int getCurrentSteps();
		
	private:
		// Pins
		int STEP;
		int DIR;
		int enable;
		
		// Config
		float rpm;
		int stepsPerRotation;

		// Position
		int currentSteps;
		
		// Helper Functions
		void singleStep(unsigned int stepWait);
		void singleStep_us(unsigned int stepWait);
};

#endif