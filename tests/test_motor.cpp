#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("motor tests") {
    SECTION("initialize tests") {
        Motor motor;
        REQUIRE(getModeAtPin(2) == -1);
        REQUIRE(getModeAtPin(3) == -1);
        motor.begin(2,3);
        REQUIRE(getModeAtPin(2) == OUTPUT);
        REQUIRE(getModeAtPin(3) == OUTPUT);

        Motor motor2;
        REQUIRE(getModeAtPin(4) == -1);
        REQUIRE(getModeAtPin(5) == -1);
        REQUIRE(getModeAtPin(6) == -1);
        motor.begin(4, 5, 6);
        REQUIRE(getModeAtPin(4) == OUTPUT);
        REQUIRE(getModeAtPin(5) == OUTPUT);
        REQUIRE(getModeAtPin(6) == OUTPUT);
    }
    SECTION("write tests") {
        Motor motor;
        motor.begin(2,3);

        motor.output(0.5);
        REQUIRE(getValueAtPin(2) == 127);
        REQUIRE(getValueAtPin(3) == 0);

        motor.output(-0.5);
        REQUIRE(getValueAtPin(2) == 0);
        REQUIRE(getValueAtPin(3) == 127);
    }
}