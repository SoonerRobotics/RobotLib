#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include <Arduino.h>
#include "Motor.h"

class MotorController
{
	public:
		MotorController();
		
		void begin(Motor motorA, Motor motorB);
		
		void outputMotorA(float out);
		
		void outputMotorB(float out);
		
	private:
		Motor motorA;
		
		Motor motorB;
		
};

#endif