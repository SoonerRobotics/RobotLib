#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include <Arduino.h>
#include "RobotLibUtil.h"

class PIDController
{
    public:
        // Constructors
	PIDController();
        PIDController(float init_state, float kp, float ki, float kd);
	
        // Copy assignment
	void operator=(const PIDController& pid);
	
        // Setters
        void begin(float init_state);
        void begin(float init_state, float kp, float ki, float kd);
        void reset();
        void set_bounded(bool bounded);
        void set_output_range(float upper, float lower);
        
        // Getters
        float update(float target_state, float cur_state);
        float get_integrator_value();

    private:
        // PID values
        float integrator;
        float error;

        // States
        float prev_error;
        float last_state;

        // Equation coefficients
        float kP;
        float kI;
        float kD;

        // Boundary control
        float high;
	float low;
        bool is_bounded;

        // Timing
        float last_time;
        float dt;
};

#endif // PIDCONTROLLER_H
