#include <RobotLib.h> 

/*
 * Quadrature (Rotary) Encoder Basic
 * 
 * Creates a Encoder object on pins 1 and 2 with K-value 3.5.
 * The program then reads the value of the encoder every half-second
 * and prints it to Serial.
 * 
 * created 29 November 2019
 * by Noah Zemlin
 */

// Create a Quadrature Encoder object and call it encoder
QuadratureEncoder encoder;

// This function is called every time pin 1 has a rising edge pulse.
void pinAInterrupt() {
  encoder.process();
}

// Setup happens only once, when the Arduino is first powered on or reset.
void setup() {
  // Initialize encoder on pins 1 and 2 with K-value 3.5.
  // Default encoder resolution is 2x.
  encoder.begin(1, 2, 3.5);

  // Attach an interrupt to pin 1 to call pinAInterrupt.
  attachInterrupt(digitalPinToInterrupt(1), pinAInterrupt, CHANGE);

  // Begin serial so we can communicate with PC
  Serial.begin(9600);
}

// The loop function runs over and over again.
void loop() {
  // Print the current change in value since setup.
  // Value is the number of ticks measured by the encoder times the K-value.
  Serial.println(encoder.getValue());
  
  // If you only want to see the value traveled in the last
  // half-second, you can call reset to zero the ticks.
  //encoder.reset();

  // Wait 500 milliseconds or half a second.
  delay(500);
}
