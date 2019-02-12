#include <RobotLib.h> 

/*
 * Motor Basic
 * 
 * Creates a Motor object on pins 4,5, and 6.
 * The motor will turn on for one second at half power, then turn off for one second, repeatedly.
 * 
 * created 11 Feb 2019
 * by Noah Zemlin
 */

//Create a Motor object and call it motorA
Motor motorA;

//Setup happens only once, when the Arduino is first powered on or reset.
void setup() {
  //Initialize motorA on pins 4,5, and 6.
  //The third pin must be a PWM pin. Refer to your Arduino's pinout sheet fon pins that are PWM.
  motorA.begin(4,5,6);

  //If your motor is spinning the wrong way, you can reverse it by adding true as the fourth parameter.
  //motorA.begin(4,5,6, true);
}

//The loop function runs over and over again.
void loop() {
  //Tell the motor to spin forwards at half power.
  motorA.output(0.5);

  //Wait for 1000 milliseconds, or 1 second.
  delay(1000);

  //Tell the motor to stop.
  motorA.output(0);

  //Wait for 1000 milliseconds, or 1 second.
  delay(1000);
}
