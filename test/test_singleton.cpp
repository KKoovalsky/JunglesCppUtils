/**
 * @file	test_singleton.cpp
 * @brief	Tests the singleton component.
 * @author	Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#include <catch2/catch_test_macros.hpp>

#include <functional>

#include "jungles/singleton.hpp"

using namespace jungles;

class SingletonUnderTest : public Singleton<SingletonUnderTest>
{
};

TEST_CASE("Only one singleton instance can be created at a time", "[singleton]")
{
    SECTION("One singleton instance is alive")
    {
        REQUIRE_NOTHROW(SingletonUnderTest{});
    }

    SECTION("Second singleton can't be created")
    {
        SingletonUnderTest s{};
        REQUIRE_THROWS(SingletonUnderTest{});
    }

    SECTION("Two different singleton types can be used at a time")
    {
        struct OneType : public Singleton<OneType>
        {
        };

        struct SecondType : public Singleton<SecondType>
        {
        };

        OneType one;
        REQUIRE_NOTHROW(SecondType{});
    }

    SECTION("Two instances can be alive but in non overlapping time")
    {
        SingletonUnderTest{};
        REQUIRE_NOTHROW(SingletonUnderTest{});
    }
}
