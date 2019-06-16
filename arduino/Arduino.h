#ifndef ARDUINO_H
#define ARDUINO_H

#include <cmath>

using namespace std;
        
#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1

#define true 0x1
#define false 0x0

class GlobalValues{
    public:
        static int global_pin_modes[17];
        static int global_pin_values[17];
};

//////// Arduino Fake Methods ////////
void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void analogWrite(int pin, int value);
float analogRead(int pin);
unsigned long millis();
void delay(unsigned long duration);
void delayMicroseconds(unsigned long duration);
//float abs(float val);


//////// Unit Testing Utilities ////////
int getValueAtPin(int pin);
void setValueAtPin(int pin, int value);
int getModeAtPin(int pin);
void arduinoClearPins();

#endif
