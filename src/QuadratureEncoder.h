#ifndef QUADRATURE_ENCODER_H
#define QUADRATURE_ENCODER_H

#include <Encoder.h>

class QuadratureEncoder : public Encoder
{
    public:
        /* Constructors */
        QuadratureEncoder();
        QuadratureEncoder(int A, int B, float K);
        QuadratureEncoder(int A, int B, float K, int pullup);

        /* Operator overrides */
        void operator=(const QuadratureEncoder& quad_encoder);

        /* Configuration */
        void begin(int A, int B, float K);
        void begin(int A, int B, float K, int pullup);
        void setResolution(int resolution);
        void pullup();
        void process();
        void reset();

        /* Getters */
        long getTicks();
        float getValue();

    private:
        // Configuration
        int resolution = 2;

        // Position
        volatile long ticks;
        int lastState = 0;
        float K;

        // Pins
        int pin_A;
        int pin_B;

        // Pinmode for pins
        int pin_mode = INPUT;

};

#endif