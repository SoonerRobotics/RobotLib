#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("HallEffectEncoder: Default Initialize Test")
{
    HallEffectEncoder hall;

    REQUIRE(hall.getTicks() == 0);
    REQUIRE(hall.getValue() == Approx(0.0f));
}

TEST_CASE("HallEffectEncoder: Configuration Initialize Test")
{
    HallEffectEncoder hall(1, 1, 1);

    REQUIRE(getModeAtPin(1) == INPUT);
    REQUIRE(hall.getTicks() == 0);
    REQUIRE(hall.getValue() == Approx(0.0f));
}

TEST_CASE("HallEffectEncoder: Begin Test")
{
    HallEffectEncoder hall;
    
    hall.begin(1, 1, 1);

    REQUIRE(getModeAtPin(1) == INPUT);
    REQUIRE(hall.getTicks() == 0);
    REQUIRE(hall.getValue() == Approx(0.0f));
}

TEST_CASE("HallEffectEncoder: Process Input Test")
{
    HallEffectEncoder hall(1, 0, 2);

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        hall.process();
    }

    REQUIRE(hall.getTicks() == 10);
    REQUIRE(hall.getValue() == Approx(20.0f));

    // Reverse direction
    hall.setDirection(1); // CCW

    // Run 20 ticks backwards
    for(int i = 0; i < 20; ++i)
    {
        hall.process();
    }

    REQUIRE(hall.getTicks() == -10);
    REQUIRE(hall.getValue() == Approx(-20.0f));
}


TEST_CASE("HallEffectEncoder: Copy-Assign Test")
{
    HallEffectEncoder hall1(1, 0, 2), hall2;

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        hall1.process();
    }

    hall2 = hall1;

    REQUIRE(hall2.getTicks() == 10);
    REQUIRE(hall2.getValue() == Approx(20.0f));
}

TEST_CASE("HallEffectEncoder: Reset Test")
{
    HallEffectEncoder hall(1, 0, 2);

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        hall.process();
    }

    hall.reset();

    REQUIRE(hall.getTicks() == 0);
    REQUIRE(hall.getValue() == Approx(0.0f));
}