#ifndef RobotLib_Talon
#define RobotLib_Talon

#include "Arduino.h"
#include "MotorController.h"
#include "Servo.h"
#include <cstdint>

namespace RobotLib {

class Talon : public MotorController {
public:
    /*
    Attaches a pin to be controlled by this Talon controller.

    @param pwmPin The pin number the Talon is connected to. Must have PWM control.
    */
    uint8_t attach(int pwmPin) {
        return this->Servo.attach(pwmPin);
    }

    /*
    Writes a signed power to the Talon, with negative values indicating reverse direction.

    @param signedPower Motor control from -1.0 to 1.0.
    */
    void write(const float signedPower) {
        if (signedPower >= 0.0f) {
            this->power = clampPower(power);
            this->direction = MotorDirection::Forwards;
        } else {
            this->power = clampPower(-power);
            this->direction = MotorDirection::Backwards;
        }

        this->updatePWM();
    }

    /*
    Writes a power and a direction to the Talon.

    @param power Motor control from 0.0 to 1.0
    @param direction Motor direction
    */
    void write(const float power, const MotorDirection direction) {
        this->power = clampPower(power);
        this->direction = direction;

        this->updatePWM();
    }

    /*
    Writes a power to the Talon. Maintains previously commanded direction.

    @param power Motor control from 0.0 to 1.0
    */
    void writePower(const float power) {
        this->power = clampPower(power);

        this->updatePWM();
    }

    /*
    Writes a direction to the Talon. Maintains previously commanded power.

    @param direction Motor direction
    */
    void writeDirection(const MotorDirection direction) {
        this->direction = direction;

        this->updatePWM();
    }
private:
    const Servo pwmController;
    float power;
    MotorDirection direction;

    static const int minPulseWidthMilliseconds = 997;
    static const int centerPulseWidthMilliseconds = 1500;
    static const int maxPulseWidthMilliseconds = 2004;
    static const int deadbandMilliseconds = 2;

    void updatePWM() {
        int pulseWidthMilliseconds = centerPulseWidthMilliseconds;
        if (this->direction == MotorDirection::Forwards) {
            pulseWidthMilliseconds += (int)((maxPulseWidthMilliseconds - (centerPulseWidthMilliseconds + deadbandMilliseconds)) * power);
        } else {
            pulseWidthMilliseconds -= (int)(((centerPulseWidthMilliseconds - deadbandMilliseconds) - minPulseWidthMilliseconds) * power);
        }

        self->Servo.writeMicroseconds(pulseWidthMilliseconds * 1000);
    }

    float clampPower(float power) {
        if (power > 1.0f) {
            power = 1.0f;
        }
        else if (power < 0.0f) {
            power = 0.0f;
        }
    }
};

} // namespace RobotLib

#endif // RobotLib_Talon