#ifndef RobotLib_MotorController
#define RobotLib_MotorController

namespace RobotLib {

enum class MotorDirection {Forwards, Backwards};

class MotorController {
public:
    virtual void write(const float signedPower);
    virtual void write(const float power, const MotorDirection direction);
    virtual void writePower(const float power);
    virtual void writeDirection(const MotorDirection direction);
};

} // namespace RobotLib

#endif // RobotLib_MotorController