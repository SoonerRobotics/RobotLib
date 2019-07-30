#include "Arduino.h"

unsigned long GlobalValues::global_time = 0;
int GlobalValues::global_pin_modes[17] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int GlobalValues::global_pin_values[17] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

void pinMode(int pin, int mode) {
	GlobalValues::global_pin_modes[pin] = mode;
}

void digitalWrite(int pin, int value) {
	setValueAtPin(pin, value);
}

int digitalRead(int pin) {
	return getValueAtPin(pin);
}

void analogWrite(int pin, int value) {
	setValueAtPin(pin, value);
}

float analogRead(int pin) {
	return getValueAtPin(pin);
}

unsigned long millis() {
	return GlobalValues::global_time / 1000;
}

unsigned long micros() {
	return GlobalValues::global_time;
}

void delay(unsigned long duration) {
	GlobalValues::global_time += duration * 1000;
}

void delayMicroseconds(unsigned long duration) {
	GlobalValues::global_time += duration;
}

#ifdef __AVR__
float abs(float val) {
	if (val < 0)
		return -val;
	return val;
}
#endif

int getValueAtPin(int pin) {
	if (pin < 0 or pin > 16) {
		return -1;
	}
	return GlobalValues::global_pin_values[pin];
}

void setValueAtPin(int pin, int value) {
	if (pin < 0 or pin > 16) {
		return;
	}
	GlobalValues::global_pin_values[pin] = value;
}

int getModeAtPin(int pin) {
	if (pin < 0 or pin > 16) {
		return -1;
	}
	return GlobalValues::global_pin_modes[pin];
}

void arduinoClearPins() {
 	for (int i=0; i<17; i++) {
		 GlobalValues::global_pin_modes[i] = -1;
		 GlobalValues::global_pin_values[i] = 0;
	 }
}

void setArduinoTimeMicros(unsigned long time) {
	GlobalValues::global_time = time;
}

void addArduinoTimeMicros(unsigned long time) {
	GlobalValues::global_time += time;
}

void setArduinoTimeMillis(unsigned long time) {
	GlobalValues::global_time = time * 1000;
}

void addArduinoTimeMillis(unsigned long time) {
	GlobalValues::global_time += time * 1000;
}