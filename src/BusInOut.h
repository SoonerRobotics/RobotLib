#ifndef BusInOut_H
#define BusInOut_H

#include <Arduino.h>

class BusInOut
{

    public:
        BusInOut(int p0, int p1 = -1, int p2 = -1, int p3 = -1,
             int p4 = -1, int p5 = -1, int p6 = -1, int p7 = -1,
             int p8 = -1, int p9 = -1, int p10 = -1, int p11 = -1,
             int p12 = -1, int p13 = -1, int p14 = -1, int p15 = -1);

        BusInOut(int pins[16]);

        void mode(int mode);

        void write(int value);
        int read();

    private:
        int _pin[16];
};

#endif
