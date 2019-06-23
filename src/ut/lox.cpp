/*#include "catch.hpp"
#include <lox.hpp>

TEST_CASE("Booleans", "[basic_types]" ){
  Lox::Lox lox;
  std::string command ="true";
  std::string expected="true";
  REQUIRE(lox.run(command) == expected);
  command ="false";
  expected="false";
  REQUIRE(lox.run(command) == expected);
}
TEST_CASE("Numbers", "[basic_types]" ){
  Lox::Lox lox;
  std::string command ="123";
  std::string expected="123";
  REQUIRE(lox.run(command) == expected);
  command ="3.14;";
  expected="3.14";
  REQUIRE(lox.run(command) == expected);
}
TEST_CASE("Strings", "[basic_types]" ){
  Lox::Lox lox;
  std::string command ="\"hello!\"";
  std::string expected="\"hello!\"";
  REQUIRE(lox.run(command) == expected);
}
TEST_CASE("Null value", "[basic_types]" ){
  Lox::Lox lox;
  std::string command ="nil";
  std::string expected="nil";
  REQUIRE(lox.run(command) == expected);
}*/
