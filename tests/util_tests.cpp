#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("util tests") {
    SECTION("clamp tests") {
        REQUIRE(RLUtil::clamp(0.5, 0, 1) == 0.5);
        REQUIRE(RLUtil::clamp(-0.5, 0, 1) == 0);
        REQUIRE(RLUtil::clamp(1.5, 0, 1) == 1);
    }
    SECTION("lerp tests") {
        REQUIRE(RLUtil::lerp(0.0f, 1.0f, 0.3f) == 0.3f);
        REQUIRE(RLUtil::lerp(0.0f, 1.0f, 0.0f) == 0.0f);
        REQUIRE(RLUtil::lerp(0.0f, 1.0f, 1.0f) == 1.0f);
        REQUIRE(RLUtil::lerp(2.0f, 7.0f, 0.5) == 4.5f);
    }
}