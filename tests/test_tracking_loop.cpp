#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("TrackingLoop: Reset Test")
{
    TrackingLoop tracker;

    // Reset the tracker
    tracker.reset();

    // Estimations should be 0
    REQUIRE(tracker.getPositionEstimate() == Approx(0.0f));
    REQUIRE(tracker.getVelocityEstimate() == Approx(0.0f));
    REQUIRE(tracker.getAccelEstimate() == Approx(0.0f));
}


TEST_CASE("TrackingLoop: Initialize Test")
{
    // Default tracker
    TrackingLoop tracker1;

    // Estimations should be 0
    REQUIRE(tracker1.getPositionEstimate() == Approx(0.0f));
    REQUIRE(tracker1.getVelocityEstimate() == Approx(0.0f));
    REQUIRE(tracker1.getAccelEstimate() == Approx(0.0f));

    // Tracker with PI gains
    TrackingLoop tracker2(100, 500);

    // Estimations should be 0
    REQUIRE(tracker2.getPositionEstimate() == Approx(0.0f));
    REQUIRE(tracker2.getVelocityEstimate() == Approx(0.0f));
    REQUIRE(tracker2.getAccelEstimate() == Approx(0.0f));
}


TEST_CASE("TrackingLoop: Copy-Assign Test")
{
    // Default tracker
    TrackingLoop tracker1, tracker2;
    float pos, vel, accel;

    // Add a short timestep
    addArduinoTimeMillis(1.0);

    // Run a loop and get the estimates
    tracker1.update(5);
    pos = tracker1.getPositionEstimate();
    vel = tracker1.getVelocityEstimate();
    accel = tracker1.getAccelEstimate();

    // Set trackers equal
    tracker2 = tracker1;

    // Tracker 2 estimates should be equal to tracker 1
    REQUIRE(tracker2.getPositionEstimate() == Approx(pos));
    REQUIRE(tracker2.getVelocityEstimate() == Approx(vel));
    REQUIRE(tracker2.getAccelEstimate() == Approx(accel));
}
