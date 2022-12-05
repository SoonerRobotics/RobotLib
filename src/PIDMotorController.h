#ifndef RobotLib_PIDMotorController
#define RobotLib_PIDMotorController

#include "Arduino.h"
#include "PID.h"
#include "MotorController.h"
#include "QuadratureEncoder.h"

namespace RobotLib {

enum class PIDMode {Position, Speed};

class PIDMotorController {
public:
    PIDMotorController(PID pid, MotorController motorController, QuadratureEncoder encoder) : pid(pid), motorController(motorController), encoder(encoder) {}

    void update() {
        if (pidMode == PIDMode::Position) {
            this->motorController.write(this->pid.output(this->encoder.readAndClearPosition()));
        } else if (pidMode == PIDMode::Speed) {
            if (!timeAtLastUpdateValid) {
                this->timeAtLastUpdate = micros();
                timeAtLastUpdateValid = true;
                return;
            }
            float distanceTraveledMeters = this->encoder.readAndClearPosition();
            unsigned long timeElapsedMicroseconds = micros() - this->timeAtLastUpdate;
            float velocityEstimateMetersPerSecond = distanceTraveledMeters / (float)(timeElapsedMicroseconds / 1e6f);

            this->motorController.write(this->pid.output(velocityEstimateMetersPerSecond));

            this->timeAtLastUpdate = micros();
        }
    }

    void writeSpeed(float speedMetersPerSecond) {
        this->targetSpeedMetersPerSecond = speedMetersPerSecond;
        this->pidMode = PIDMode::Speed;
    }

    void writeDistance(float distanceMeters) {
        this->targetDistanceMeters = distanceMeters;
        this->pidMode = PIDMode::Position;

        timeAtLastUpdateValid = false;
    }

private:
    PID &pid;
    MotorController &motorController;
    QuadratureEncoder &encoder;

    PIDMode pidMode;
    float targetSpeedMetersPerSecond;
    float targetDistanceMeters;

    unsigned long timeAtLastUpdate = 0;
    bool timeAtLastUpdateValid = false;
};

} // namespace RobotLib

#endif // RobotLib_PIDMotorController