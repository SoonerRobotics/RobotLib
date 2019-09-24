#include "BusInOut.h"

BusInOut::BusInOut(int p0, int p1 = -1, int p2 = -1, int p3 = -1,
                int p4 = -1, int p5 = -1, int p6 = -1, int p7 = -1,
                int p8 = -1, int p9 = -1, int p10 = -1, int p11 = -1,
                int p12 = -1, int p13 = -1, int p14 = -1, int p15 = -1) {
    
    _pin = {p0, p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15};
}

BusInOut::BusInOut(int[]  pins[16]) {
    _pin = pins;
}

BusInOut::mode(int mode) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1)
            pinMode(_pin[i], mode);
    }
}

BusInOut::write(int value) {
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1)
            digitalWrite(_pin[i], (value >> i) && 1);
    }
}

int BusInOut::read() {
    int value = 0;
    for (int i=0; i<16; i++) {
        if (_pin[i] != -1)
            value = (value << 1) + digitalRead(_pin[i]);
    }
}