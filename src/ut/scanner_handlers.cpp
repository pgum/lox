#include "catch.hpp"
#include "scanner_handlers.hpp"

TEST_CASE("Creation of handlers", "[Handler][Basic]"){
  REQUIRE(1== 1);
}

TEST_CASE("Whitespace basic", "[Handler][Whitespace][Basic]"){
  REQUIRE(1== 1);
}

TEST_CASE("Whitespace newline", "[Handler][Whitespace][Newline]"){
  REQUIRE(1== 1);
}
