#ifndef MOTOR_H
#define MOTOR_H

#include <Arduino.h>

class Motor
{

	public:
		Motor();
		
		void operator=(const Motor& motor);
		
		/**
		 * Initialize a 2 pin motor.
		 */
		Motor* begin(int in1pin, int in2pin);
		/**
		 * Initialize a 3 pin motor.
		 */
		Motor* begin(int in1pin, int in2pin, int enpin);


		/**
		 * Set the default signal to send to in1pin and in2pin on 0 speed.
		 */
		Motor* setDefaultOnZero(int high);

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

		//For backwards compatibility
		void output2(float out);

		/**
		 * Disables motor output immediately.
		 */
		void disableOutput();

		/**
		 * Enables motor output after it has been disabled.
		 */
		void enableOutput();
		
	private:
		int in1pin;
		int in2pin;
		int enpin;

		int defaultOnZero = HIGH;

		bool disabled = LOW;
		
		float clamp(float val, float low, float high);
};

#endif
