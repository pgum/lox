#define CATCH_CONFIG_MAIN
#include <catch.hpp>
#include <lox.hpp>
using Catch::Matchers::EndsWith;

TEST_CASE( "Lox init", "[sanity_check]" ) {
    Lox::Lox lox;
    std::string command("print(\"hello\")");
    std::string expected(command);
    REQUIRE_THAT( lox.run(command) , EndsWith(expected));
}
