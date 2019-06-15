#define CATCH_CONFIG_MAIN
#include <scanner.hpp>
#include <lox.hpp>
#include "catch.hpp"
using Catch::Matchers::EndsWith;

//Lox::Lox lox;
std::string command, expected;
TEST_CASE("Empty input", "Scanner"){
  command = "";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("Parens", "Scanner"){
  command = "()";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenLParen(),
    Lox::TokenRParen(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("Braces", "Scanner"){
  command = "{}";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenLBrace(),
    Lox::TokenRBrace(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("Comma, Dot, Semicolon, Star", "Scanner"){
  command = ",.;*";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenComma(),
    Lox::TokenDot(),
    Lox::TokenSemicolon(),
    Lox::TokenStar(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("Erroreus", "Scanner"){
  invalid_command = "x";
  Lox::Scanner scanner(invalid_command);
  REQUIRE(scanner.scan() == false);
//  REQUIRE(scanner.hasErrors() == true);
  REQUIRE(scanner.errorsEncountered.size() > 0);
}

/*
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
*/
