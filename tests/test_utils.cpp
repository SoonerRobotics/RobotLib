#include <RobotLib.h>
#include <catch.hpp>

TEST_CASE("clamp tests") {
    REQUIRE(RLUtil::clamp(0.5, 0, 1) == Approx(0.5));
    REQUIRE(RLUtil::clamp(-0.5, 0, 1) == Approx(0));
    REQUIRE(RLUtil::clamp(1.5, 0, 1) == Approx(1));
}

TEST_CASE("lerp tests") {
    REQUIRE(RLUtil::lerp(0.0f, 1.0f, 0.3f) == Approx(0.3f));
    REQUIRE(RLUtil::lerp(0.0f, 1.0f, 0.0f) == Approx(0.0f));
    REQUIRE(RLUtil::lerp(0.0f, 1.0f, 1.0f) == Approx(1.0f));
    REQUIRE(RLUtil::lerp(2.0f, 7.0f, 0.5) == Approx(4.5f));
}

TEST_CASE("slerp tests") {
    REQUIRE(RLUtil::slerp(0.0f, 1.0f, 0.3f) == Approx(0.216f));
    REQUIRE(RLUtil::slerp(0.0f, 1.0f, 0.0f) == Approx(0.0f));
    REQUIRE(RLUtil::slerp(0.0f, 1.0f, 1.0f) == Approx(1.0f));
    REQUIRE(RLUtil::slerp(2.0f, 7.0f, 0.5) ==Approx(4.5f));
}