#include <BusInOut.h>
#include <catch.hpp>

TEST_CASE("Constructor and mode") 
{
    BusInOut test(1,2,4)
    test.mode(INPUT_PULLUP);

    REQUIRE(getModeAtPin(1) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(2) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(4) == INPUT_PULLUP);
}