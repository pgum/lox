#include "catch.hpp"
#include <scanner.hpp>
TEST_CASE("Empty input", "[Scanner][Single]"){
  std::string command = "";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}
TEST_CASE("ParensBracesBrackets", "[Scanner][Single]"){
  std::string command = "(){}[]";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenLParen(),
    Lox::TokenRParen(),
    Lox::TokenLBrace(),
    Lox::TokenRBrace(),
    Lox::TokenLBracket(),
    Lox::TokenRBracket(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}
TEST_CASE("Comma, Dot, Semicolon, Star", "[Scanner][Single]"){
  std::string command = ",.;*";
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
TEST_CASE("Erroreus", "[Scanner][Single]"){
  std::string invalid_command = "x";
  Lox::Scanner scanner(invalid_command);
  REQUIRE(scanner.scan() == false);
//  REQUIRE(scanner.hasErrors() == true);
  REQUIRE(scanner.errorsEncountered.size() > 0);
}
