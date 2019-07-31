#ifndef HallEffect_ENCODER_H
#define HallEffect_ENCODER_H

#include <Encoder.h>

//TODO: find a better way to do this?
#define CLOCKWISE 0
#define COUNTERCLOCKWISE 1

class HallEffectEncoder : public Encoder
{
    public:
        /* Constructors */
        HallEffectEncoder();
        HallEffectEncoder(int pin, int direction, float K);

        /* Operator overrides */
        void operator=(const HallEffectEncoder& hall_encoder);

        /* Configuration */
        void begin(int pin, int direction, float K);
        void setDirection(int direction);
        void process();
        void reset();

        /* Getters */
        long getTicks();
        float getValue();

    private:
        // Position
        long ticks;
        float K;

        // Configuration
        int pin;
        int direction;
};


#endif