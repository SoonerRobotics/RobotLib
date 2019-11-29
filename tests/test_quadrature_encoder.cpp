#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("QuadratureEncoder: Default Initialize Test")
{
    QuadratureEncoder quad;

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0f));
}

TEST_CASE("QuadratureEncoder: Constructor Arguments Test")
{
    QuadratureEncoder quad(1, 2, 1);

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0f));
    REQUIRE(getModeAtPin(1) == INPUT);
    REQUIRE(getModeAtPin(2) == INPUT);

    QuadratureEncoder quad2(1, 2, 1, true);

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0f));
    REQUIRE(getModeAtPin(1) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(2) == INPUT_PULLUP);
}

TEST_CASE("QuadratureEncoder: Begin Test")
{
    QuadratureEncoder quad;

    quad.begin(1, 2, 1);

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0f));
    REQUIRE(getModeAtPin(1) == INPUT);
    REQUIRE(getModeAtPin(2) == INPUT);

    quad.begin(1, 2, 1, true);

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0f));
    REQUIRE(getModeAtPin(1) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(2) == INPUT_PULLUP);
}

TEST_CASE("QuadratureEncoder: Process Input Test")
{
    QuadratureEncoder quad(1, 2, 3);

    // Simulate forward motion
    setValueAtPin(1, HIGH);
    setValueAtPin(2, HIGH);

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        quad.process();
    }

    REQUIRE(quad.getTicks() == 10);
    REQUIRE(quad.getValue() == Approx(30.0));

    // Simulate backward motion
    setValueAtPin(1, LOW);
    setValueAtPin(2, HIGH);

    // Run 20 ticks backward
    for(int i = 0; i < 20; ++i)
    {
        quad.process();
    }

    REQUIRE(quad.getTicks() == -10);
    REQUIRE(quad.getValue() == Approx(-30.0));
}

TEST_CASE("QuadratureEncoder: Reset Test")
{
    QuadratureEncoder quad(1, 2, 3);

    // Simulate forward motion
    setValueAtPin(1, HIGH);
    setValueAtPin(2, HIGH);

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        quad.process();
    }

    // Reset the encoder
    quad.reset();

    REQUIRE(quad.getTicks() == 0);
    REQUIRE(quad.getValue() == Approx(0.0));
}

TEST_CASE("QuadratureEncoder: Pullup Test")
{
    QuadratureEncoder quad;

    quad.begin(1, 2, 1);

    REQUIRE(getModeAtPin(1) == INPUT);
    REQUIRE(getModeAtPin(2) == INPUT);

    quad.pullup();

    REQUIRE(getModeAtPin(1) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(2) == INPUT_PULLUP);
}

TEST_CASE("QuadratureEncoder: Copy-Assign Test")
{
    QuadratureEncoder quad1(1, 2, 3), quad2;

    // Simulate forward motion
    setValueAtPin(1, HIGH);
    setValueAtPin(2, HIGH);

    // Run 10 ticks forward
    for(int i = 0; i < 10; ++i)
    {
        quad1.process();
    }

    // copy-assign to the new encoder
    quad2 = quad1;

    REQUIRE(quad2.getTicks() == 10);
    REQUIRE(quad2.getValue() == Approx(30.0));
}