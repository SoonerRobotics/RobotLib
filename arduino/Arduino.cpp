#include "Arduino.h"

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
	return 0;
}

void delay(unsigned long duration) {
	(void)duration; //removes 'unused parameter' warning
	return;
}

void delayMicroseconds(unsigned long duration) {
	(void)duration; //removes 'unused parameter' warning
}

// float abs(float val) {
// 	if (val < 0)
// 		return -val;
// 	return val;
// }

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