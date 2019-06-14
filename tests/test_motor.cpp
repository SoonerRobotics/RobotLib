#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("initialize tests") {
    arduinoClearPins();
    Motor motor;
    REQUIRE(getModeAtPin(2) == -1);
    REQUIRE(getModeAtPin(3) == -1);
    motor.begin(2, 3);
    REQUIRE(getModeAtPin(2) == OUTPUT);
    REQUIRE(getModeAtPin(3) == OUTPUT);
    REQUIRE(motor.getNumPins() == 2);

    Motor motor2;
    REQUIRE(getModeAtPin(4) == -1);
    REQUIRE(getModeAtPin(5) == -1);
    REQUIRE(getModeAtPin(6) == -1);
    motor.begin(4, 5, 6);
    REQUIRE(getModeAtPin(4) == OUTPUT);
    REQUIRE(getModeAtPin(5) == OUTPUT);
    REQUIRE(getModeAtPin(6) == OUTPUT);
    REQUIRE(motor.getNumPins() == 3);
}

TEST_CASE("reverse initialize tests") {
    arduinoClearPins();
    Motor motor;
    REQUIRE(getModeAtPin(2) == -1);
    REQUIRE(getModeAtPin(3) == -1);
    motor.begin(2, 3).reverse();
    REQUIRE(getModeAtPin(2) == OUTPUT);
    REQUIRE(getModeAtPin(3) == OUTPUT);
    REQUIRE(motor.getNumPins() == 2);

    Motor motor2;
    REQUIRE(getModeAtPin(4) == -1);
    REQUIRE(getModeAtPin(5) == -1);
    REQUIRE(getModeAtPin(6) == -1);
    motor.begin(4, 5, 6).reverse();
    REQUIRE(getModeAtPin(4) == OUTPUT);
    REQUIRE(getModeAtPin(5) == OUTPUT);
    REQUIRE(getModeAtPin(6) == OUTPUT);
    REQUIRE(motor.getNumPins() == 3);
}


TEST_CASE("2 pin write tests") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3);

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 127);
    REQUIRE(getValueAtPin(3) == 0);

    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 127);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 255);
    REQUIRE(getValueAtPin(3) == 255);
}

TEST_CASE("3 pin write tests") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3,4);

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 127);

    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 0);
    REQUIRE(getValueAtPin(4) == 127);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 255);
}


TEST_CASE("copy and write test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3);

    Motor motor2;
    motor2 = motor;

    motor2.output(0.5);
    REQUIRE(getValueAtPin(2) == 127);
    REQUIRE(getValueAtPin(3) == 0);
}

TEST_CASE("2 pin write reverse tests") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3).reverse();

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 127);

    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 127);
    REQUIRE(getValueAtPin(3) == 0);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 255);
    REQUIRE(getValueAtPin(3) == 255);
}

TEST_CASE("3 pin write reverse tests") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3,4).reverse();

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 0);
    REQUIRE(getValueAtPin(4) == 127);

    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 127);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 255);
}

TEST_CASE("2 pin disable and reenable test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2,3);

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 127);
    REQUIRE(getValueAtPin(3) == 0);

    motor.disableOutput();
    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    motor.outputBool(LOW);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);

    motor.enableOutput();
    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 127);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 255);
    REQUIRE(getValueAtPin(3) == 255);
}

TEST_CASE("3 pin disable and reenable test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2, 3, 4);

    motor.output(0.5);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 127);

    motor.disableOutput();
    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 0);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 0);
    motor.outputBool(LOW);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 0);

    motor.enableOutput();
    motor.output(-0.5);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 0);
    REQUIRE(getValueAtPin(4) == 127);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 255);
}

TEST_CASE("output bool test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2, 3);

    motor.outputBool(HIGH);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);

    motor.outputBool(LOW);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 0);

    Motor motor2;
    motor2.begin(4,5,6);

    motor2.outputBool(HIGH);
    REQUIRE(getValueAtPin(4) == 255);
    REQUIRE(getValueAtPin(5) == 255);
    REQUIRE(getValueAtPin(6) == 0);

    motor2.outputBool(LOW);
    REQUIRE(getValueAtPin(4) == 0);
    REQUIRE(getValueAtPin(5) == 0);
    REQUIRE(getValueAtPin(6) == 0);
}

TEST_CASE("2 pin default on zero test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2, 3).setDefaultOnZero(LOW);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 0);

    motor.setDefaultOnZero(HIGH);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 255);
    REQUIRE(getValueAtPin(3) == 255);
}

TEST_CASE("3 pin default on zero test") {
    arduinoClearPins();
    Motor motor;
    motor.begin(2, 3, 4).setDefaultOnZero(LOW);

    motor.output(0);
    REQUIRE(getValueAtPin(2) == 0);
    REQUIRE(getValueAtPin(3) == 0);
    REQUIRE(getValueAtPin(4) == 255);

    motor.setDefaultOnZero(HIGH);
    motor.output(0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(3) == 1);
    REQUIRE(getValueAtPin(4) == 255);
}