#include <BusInOut.h>
#include <catch.hpp>

TEST_CASE("Constructors and mode") 
{
    BusInOut test(1,2,4);
    test.mode(INPUT_PULLUP);

    REQUIRE(getModeAtPin(1) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(2) == INPUT_PULLUP);
    REQUIRE(getModeAtPin(4) == INPUT_PULLUP);

    int pins[] = {5,6,7};
    BusInOut test2(pins);
    test2.mode(OUTPUT);

    REQUIRE(getModeAtPin(5) == OUTPUT);
    REQUIRE(getModeAtPin(6) == OUTPUT);
    REQUIRE(getModeAtPin(7) == OUTPUT);
}

TEST_CASE("Write test") 
{
    BusInOut test(1,2,4,6,8);
    test.mode(OUTPUT);
    test.write(0b10110);

    REQUIRE(getValueAtPin(1) == 0);
    REQUIRE(getValueAtPin(2) == 1);
    REQUIRE(getValueAtPin(4) == 1);
    REQUIRE(getValueAtPin(6) == 0);
    REQUIRE(getValueAtPin(8) == 1);
}

TEST_CASE("Read test") 
{
    BusInOut test(1,2,4,6,8);
    test.mode(INPUT);
    
    setValueAtPin(1, 0);
    setValueAtPin(2, 1);
    setValueAtPin(4, 1);
    setValueAtPin(6, 0);
    setValueAtPin(8, 1);

    REQUIRE(test.read() == 0b10110);
}