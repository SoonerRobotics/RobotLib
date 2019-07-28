#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("StepperMotor: Default Constructor Test")
{
    StepperMotor stepper;

    REQUIRE(stepper.getCurrentSteps() == 0);
}

TEST_CASE("StepperMotor: Begin Test")
{
    StepperMotor stepper1, stepper2;

    // Init stepper motor 1 (no enable pin)
    stepper1.begin(1, 2, -1);

    REQUIRE(getModeAtPin(1) == OUTPUT);
    REQUIRE(getModeAtPin(2) == OUTPUT);

    // Init stepper motor 2 (with an enable pin)
    stepper2.begin(1, 2, 3);

    REQUIRE(getModeAtPin(1) == OUTPUT);
    REQUIRE(getModeAtPin(2) == OUTPUT);
    REQUIRE(getModeAtPin(3) == OUTPUT);
    REQUIRE(getValueAtPin(3) == HIGH);
}

/**
 * @brief This test is mainly just to get coverage because 
 * these functions are a black box
 * 
 */
TEST_CASE("StepperMotor: RPM and Step Test")
{
    StepperMotor stepper;

    // Init stepper motor (with an enable pin)
    stepper.begin(1, 2, 3);

    // Set the RPM to 50
    stepper.setRPM(50);

    // Make 10 steps forward
    stepper.step(10);

    // Confirm 10 steps were made and the enable pin is HIGH
    REQUIRE(stepper.getCurrentSteps() == 10);
    REQUIRE(getValueAtPin(3) == HIGH);

    // Confirm pin output values
    REQUIRE(getValueAtPin(1) == LOW);
    REQUIRE(getValueAtPin(2) == HIGH);

    // Move 20 steps backwards
    stepper.step(-20);

    // Confirm 10 steps were made and the enable pin is HIGH
    REQUIRE(stepper.getCurrentSteps() == -10);
    REQUIRE(getValueAtPin(3) == HIGH);

    // Confirm pin output values
    REQUIRE(getValueAtPin(1) == LOW);
    REQUIRE(getValueAtPin(2) == LOW);
}


TEST_CASE("StepperMotor: Reset Test")
{
    StepperMotor stepper;

    // Init stepper motor (with an enable pin)
    stepper.begin(1, 2, 3);

    // Set the RPM to 5
    stepper.setRPM(5);

    // Make 10 steps forward
    stepper.step(10);

    // Reset the motor's step counter
    stepper.reset();

    // the step counter should be 0
    REQUIRE(stepper.getCurrentSteps() == 0);
}

TEST_CASE("StepperMotor: Copy-Assign Test")
{
    StepperMotor stepper1, stepper2;

    // Init stepper motor (with an enable pin)
    stepper1.begin(1, 2, 3);

    // Set the RPM to 50
    stepper1.setRPM(50);

    // Make 10 steps forward
    stepper1.step(10);

    // copy assign the stepper motors
    stepper2 = stepper1;

    // the step counter should be 10 in the new motor
    REQUIRE(stepper2.getCurrentSteps() == 10);
}

/**
 * @brief The main purpose of this test is to run the singleStep_us function
 * by making the RPM really high
 * 
 */
TEST_CASE("StepperMotor: High Frequency Step Test")
{
    StepperMotor stepper;

    // Init stepper motor (with an enable pin)
    stepper.begin(1, 2, 3);

    // Set the RPM to 1000
    stepper.setRPM(1000);

    // Make 10 steps forward
    stepper.step(10);

    // Confirm 10 steps were made and the enable pin is HIGH
    REQUIRE(stepper.getCurrentSteps() == 10);
    REQUIRE(getValueAtPin(3) == HIGH);

    // Confirm pin output values
    REQUIRE(getValueAtPin(1) == LOW);
    REQUIRE(getValueAtPin(2) == HIGH);

    // Move 20 steps backwards
    stepper.step(-20);

    // Confirm 10 steps were made and the enable pin is HIGH
    REQUIRE(stepper.getCurrentSteps() == -10);
    REQUIRE(getValueAtPin(3) == HIGH);

    // Confirm pin output values
    REQUIRE(getValueAtPin(1) == LOW);
    REQUIRE(getValueAtPin(2) == LOW);
}