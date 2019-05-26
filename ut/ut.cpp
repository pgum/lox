#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <lox.hpp>
using Catch::Matchers::EndsWith;

Lox::Lox lox;
std::string command, expected;

TEST_CASE("Booleans", "[basic_types]" ){
    command ="true;";
    expected="true";
    REQUIRE(lox.run(command) == expected);
    command ="false;";
    expected="false";
    REQUIRE(lox.run(command) == expected);
}

TEST_CASE("Numbers", "[basic_types]" ){
    command ="123;";
    expected="123";
    REQUIRE(lox.run(command) == expected);
    command ="3.14;";
    expected="3.14";
    REQUIRE(lox.run(command) == expected);
}

TEST_CASE("Strings", "[basic_types]" ){
    command ="\"hello!\";";
    expected="\"hello!\"";
    REQUIRE(lox.run(command) == expected);
}

TEST_CASE("Null value", "[basic_types]" ){
    command ="nil;";
    expected="nil";
    REQUIRE(lox.run(command) == expected);
}
