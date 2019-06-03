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

void pinMode(int pin, int mode);
void digitalWrite(int pin, int value);
int digitalRead(int pin);
void analogWrite(int pin, int value);
float analogRead(int pin);
unsigned long millis();
void delay(unsigned long duration);
void delayMicroseconds(unsigned long duration);
//float abs(float val);

#endif
