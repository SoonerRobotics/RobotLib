#ifndef ENCODER_H
#define ENCODER_H

#include <Arduino.h>

class Encoder
{
    public:

        virtual void process() = 0;
        virtual void reset() = 0;
    
        virtual long getTicks() = 0;
        virtual float getValue() = 0;
        

};

#endif