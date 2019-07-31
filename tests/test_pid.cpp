#include <PIDController.h>
#include <catch.hpp>

TEST_CASE("Bounding/Clamping Test") 
{
    PIDController pid(0, 1, 0, 0);

    // Set dt = 1 msec
    addArduinoTimeMillis(1.0);

    // Test bounded is default with a max of 1.0 for output
    REQUIRE(pid.update(5.0, 0) == Approx(1.0f));

    // Unbind
    pid.setBounded(false);

    // Set dt = 1 msec
    addArduinoTimeMillis(1.0);

    // Test unbounded produces correct proportional output
    REQUIRE(pid.update(5.0, 0) == Approx(5.0f));

    // Rebind
    pid.setBounded(true);

    // Set dt = 1 msec
    addArduinoTimeMillis(1.0);

    // Test bounded mode produces correct proportional output
    REQUIRE(pid.update(5.0, 0) == Approx(1.0f));
}

TEST_CASE("Proportional Control Test") 
{
    PIDController pid;

    // Set proportional control to 0.5, initial state of 0
    pid.begin(0, 0.5, 0, 0);

    // Default to dt = 1 msec to avoid errors
    addArduinoTimeMillis(1.0);

    // An error of 1 should produce 0.5 as output
    REQUIRE(pid.update(2.0, 1.0) == Approx(0.5f)); 

    // Set dt = 1 msec
    addArduinoTimeMillis(1.0);

    // An error of -1 should produce -0.5 as output
    REQUIRE(pid.update(-2.0, -1.0) == Approx(-0.5f)); 
}

TEST_CASE("Integral Control Test") 
{
    PIDController pid;

    // Set integral control to 1, initial state of 0
    pid.begin(0, 0, 0.5, 0);

    // Default to dt = 1 sec to avoid errors
    addArduinoTimeMillis(1000.0);

    // Last error: 1, current error: 0.5 -> integral += 0.75 -> result = 0.375
    REQUIRE(pid.update(1, 0.5) == Approx(0.375f)); 

    // Set dt = 1 sec to add more cumulative error
    addArduinoTimeMillis(1000.0);

    // Last error: 0.5, current error: 0.25 -> integral += 0.375 -> result += 0.1875
    REQUIRE(pid.update(1, 0.75) == Approx(0.5625f)); 

    // Set dt = 1 sec to add more cumulative error
    addArduinoTimeMillis(1000.0);

    // The integrator function should have the same output as this control
    float result = pid.update(1,1);
    float integrator = pid.getIntegratorValue();
    REQUIRE(integrator == Approx(result));
}

TEST_CASE("Derivative Control Test") 
{
    PIDController pid;

    // Set integral control to 1, initial state of 0
    pid.begin(0, 0, 0, 0.5);

    // Default to dt = 1 sec to avoid errors
    addArduinoTimeMillis(1000.0);

    // Last state: 0, current state: 1 -> slope = 1 -> 0.5
    REQUIRE(pid.update(2, 1) == Approx(0.5f)); 

    // Set dt = 1 sec to add more cumulative error
    addArduinoTimeMillis(1000.0);

    // Last state: 1, current state: 1.5 -> slope = 0.5 -> 0.25
    REQUIRE(pid.update(2, 1.5) == Approx(0.25f)); 
}


TEST_CASE("Reset and Begin Test") 
{
    PIDController pid;

    // Set an initial state
    pid.begin(0, 1, 1, 1);
    pid.setBounded(false);

    // Default to dt = 1 sec to avoid errors
    addArduinoTimeMillis(1000.0);

    // Run an update
    pid.update(2, 1);   // This will produce a results of 1 + 1.5 + 1 = 3.5

    // Reset the controller
    pid.reset();

    // Reinitialize
    pid.begin(0);

    // Set dt = 1 sec
    addArduinoTimeMillis(1000.0);

    // The controller should get the same value as before, since this is the first run
    REQUIRE(pid.update(2, 1) == Approx(3.5f)); 
}

TEST_CASE("Copy-Assign Test")
{
    PIDController pid1, pid2;

    // Set an initial state
    pid1.begin(0, 1, 1, 1);
    pid1.setBounded(false);

    // Default to dt = 1 sec to avoid errors
    addArduinoTimeMillis(1000.0);

    // Run an update
    pid1.update(2, 1);   // This will produce a results of 1 + 1.5 + 1 = 3.5

    // Set pid2 equal to pid1
    pid2 = pid1;

    // Set dt = 1 sec to add more cumulative error
    addArduinoTimeMillis(1000.0);

    // Run another update, but use pid2
    // Result should be 0.5 + 2.25 + 0.5
    REQUIRE(pid2.update(2, 1.5) == Approx(3.25));
}

TEST_CASE("Set Output Range Test")
{
    PIDController pid(0, 5, 0, 0);

    // Set an output range
    pid.setOutputRange(-0.25, 0.25);

    // Set dt = 1 sec to add more cumulative error
    addArduinoTimeMillis(1000.0);

    // Output range should be limited
    REQUIRE(pid.update(4, 1) == Approx(0.25));
}


TEST_CASE("High Frequency Loop Test")
{
    PIDController pid(0, 0.1, 0, 0);

    // Set dt = 1 usec to add more cumulative error
    addArduinoTimeMicros(1);

    // Output range should be a real value despite the short update time
    REQUIRE(pid.update(4, 1) == Approx(0.3));
}