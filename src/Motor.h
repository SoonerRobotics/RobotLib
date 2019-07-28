#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>
#include "RobotLibUtil.h"

class Motor
{

    public:
        Motor();
        
        Motor& operator=(const Motor& motor);
        
        /**
         * Initialize a 2 pin motor.
         */
        Motor& begin(int in1pin, int in2pin);

        /**
         * Initialize a 3 pin motor.
         */
        Motor& begin(int in1pin, int in2pin, int enpin);

        /**
         * Reverses the direction of a motor
         */
        Motor& reverse();

        /**
         * Set the default signal to send to in1pin and in2pin on 0 speed.
         */
        Motor& setDefaultOnZero(int high);

        /**
         * Output a speed to the motor, between -1 and 1.
         * Speed of 0 outputs LOW or HIGH to both in1pin and in2pin based
         * on setDefaultOnZero(). The default is HIGH.
         */
        void output(float speed);
        
        /**
         * Sends LOW or HIGH to both in1pin and in2pin.
         */
        void outputBool(int high);

        /**
         * Disables motor output immediately.
         */
        void disableOutput();

        /**
         * Enables motor output after it has been disabled.
         */
        void enableOutput();

        /**
         * Gets the number of pins the motor runs on (2 vs 3)
         */
        int getNumPins();
        
    private:
        int in1pin;
        int in2pin;
        int enpin;

        int defaultOnZero = HIGH;

        bool disabled = LOW;
};

#endif
