#ifndef PIDCONTROLLER_H
#define PIDCONTROLLER_H

#include "Collection.h"

class PIDController
{
    public:

		PIDController();
		
        PIDController(float process_init, Collection<float> K);
		
        float getOutput(float setpoint, float process);
		
        void setOutputRange(float upper, float lower);
		
        void initialize(float process_init, Collection<float> K);

    protected:

    private:
        float integrator;
        float err;
        float last_process_var;
        float kP;
        float kI;
        float kD;
        float high
		float low;

        float coerce(float val, float upper, float lower);
};

#endif // PIDCONTROLLER_H
