/**
 * @file	test_singleton.cpp
 * @brief	Tests the singleton component.
 * @author	Kacper Kowalski - kacper.s.kowalski@gmail.com
 */
#include <catch2/catch_test_macros.hpp>

#include <functional>

#include "jungles/singleton.hpp"

using namespace jungles;

class SingletonCRTP : public Singleton<SingletonCRTP>
{
};

struct SingletonAsMember
{
    Singleton<SingletonAsMember> singleton;
};

TEST_CASE("Only one CRTP singleton instance can be created at a time", "[singleton]")
{
    SECTION("One singleton instance is alive")
    {
        REQUIRE_NOTHROW(SingletonCRTP{});
    }

    SECTION("Second singleton can't be created")
    {
        SingletonCRTP s{};
        REQUIRE_THROWS(SingletonCRTP{});
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
        SingletonCRTP{};
        REQUIRE_NOTHROW(SingletonCRTP{});
    }
}

TEST_CASE("Only one singleton as member instance can be created at a time", "[singleton]")
{
    SECTION("One singleton instance is alive")
    {
        REQUIRE_NOTHROW(SingletonAsMember{});
    }

    SECTION("Second singleton can't be created")
    {
        SingletonAsMember s{};
        REQUIRE_THROWS(SingletonAsMember{});
    }

    SECTION("Two different singleton types can be used at a time")
    {
        struct OneTypeWithSingletonMember
        {
            Singleton<OneTypeWithSingletonMember> singleton_indicator;
        };

        struct SecondTypeWithSingletonMember
        {
            Singleton<SecondTypeWithSingletonMember> singleton_indicator;
        };

        OneTypeWithSingletonMember one;
        REQUIRE_NOTHROW(SecondTypeWithSingletonMember{});
    }

    SECTION("Two instances can be alive but in non overlapping time")
    {
        SingletonAsMember{};
        REQUIRE_NOTHROW(SingletonAsMember{});
    }
}
