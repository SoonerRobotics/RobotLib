#ifndef QUADRATURE_ENCODER_H
#define QUADRATURE_ENCODER_H

#include <Encoder.h>

class QuadratureEncoder : public Encoder
{
    public:
        /* Constructors */
        QuadratureEncoder();
        QuadratureEncoder(int A, int B, float K);

        /* Operator overrides */
        void operator=(const QuadratureEncoder& quad_encoder);

        /* Configuration */
        void begin(int A, int B, float K);
        void process();
        void reset();

        /* Getters */
		long getTicks();
		float getValue();

    private:
        // Position
        long ticks;
        float K;

        // Pins
        int pin_A;
        int pin_B;

};

#endif