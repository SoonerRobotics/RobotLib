#include "Arduino.h"

void pinMode(int pin, int mode) {
	return;
}

void digitalWrite(int pin, int value) {
	return;
}

int digitalRead(int pin) {
	return 0;
}

void analogWrite(int pin, int value) {
	return;
}

float analogRead(int pin) {
	return 0;
}

unsigned long millis() {
	return 0;
}

void delay(unsigned long duration) {
	return;
}

void delayMicroseconds(unsigned long duration) {
	return;
}

float abs(float val) {
	if (val < 0)
		return -val;
	return val;
}