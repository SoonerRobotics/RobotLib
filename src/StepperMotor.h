#ifndef STEPPERMOTOR_H
#define STEPPERMOTOR_H

#include <Arduino.h>

class StepperMotor
{
    public:
        StepperMotor();
        
        void operator=(const StepperMotor& motor);
        
        void begin(int step, int dir, int enable = -1, int stepsPerRotation = 200);
        
        void step(int steps);
        
        void setRPM(float speed);
        
        int getCurrentSteps();
        
    private:
        int STEP;
        int DIR;
        int enable;
        
        float rpm;
        int stepsPerRotation;
        int currentSteps;
        
        void singleStep(unsigned int stepWait);
        void singleStep_us(unsigned int stepWait);
};

#endif