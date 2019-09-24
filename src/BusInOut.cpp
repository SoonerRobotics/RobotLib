#include "BusInOut.h"

BusInOut::BusInOut(int p0, int p1, int p2, int p3,
                int p4, int p5, int p6, int p7,
                int p8, int p9, int p10, int p11,
                int p12, int p13, int p14, int p15) {
    
    int pins[] = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};
    for (int i=0; i<16; i++) {
        _pin[i] = pins[i];
    }
}

BusInOut::BusInOut(int  pins[]) {
    for (int i=0; i<16; i++) {
        _pin[i] = pins[i];
    }
}

void BusInOut::mode(int mode) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1)
            pinMode(_pin[i], mode);
    }
}

void BusInOut::write(int value) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1) {
            digitalWrite(_pin[i], (value >> i) & 1);
        }
    }
}

int BusInOut::read() {
    int value = 0;
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1)
            value |= digitalRead(_pin[i]) << i;
    }
    return value;
}