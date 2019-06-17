#include "catch.hpp"
#include <scanner.hpp>
namespace UT{
namespace Scanner{

using Tokens = std::vector<Lox::Token>;

void RequireNoErrors(const Lox::Scanner& s){
  REQUIRE(s.errorsEncountered.size() == 0);
}

TEST_CASE("Erroreus", "[Scanner][Single]"){
  std::string invalid_command = "$";
  Lox::Scanner scanner(invalid_command);
  REQUIRE(scanner.scan() == false);
  REQUIRE(scanner.errorsEncountered.size() > 0);
}

TEST_CASE("Empty input", "[Scanner][Single]"){
  std::string command = "";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  Tokens tokens ={
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
  RequireNoErrors(scanner);
}

TEST_CASE("( ) { } [ ] , . ; / * ! = > < != == >= <=", "[Scanner][Single]"){
  std::map<std::string, Lox::Token> mapCommandToExpectedToken = {
    {"(", Lox::TokenLParen()},
    {")", Lox::TokenRParen()},
    {"{", Lox::TokenLBrace()},
    {"}", Lox::TokenRBrace()},
    {"[", Lox::TokenLBracket()},
    {"]", Lox::TokenRBracket()},
    {",", Lox::TokenComma()},
    {".", Lox::TokenDot()},
    {";", Lox::TokenSemicolon()},
    {"/", Lox::TokenSlash()},
    {"*", Lox::TokenStar()},
    {"!", Lox::TokenBang()},
    {"=", Lox::TokenEqual()},
    {">", Lox::TokenGreater()},
    {"<", Lox::TokenLess()},
    {"!=", Lox::TokenBangEqual()},
    {"==", Lox::TokenEqualEqual()},
    {">=", Lox::TokenGreaterEqual()},
    {"<=", Lox::TokenLessEqual()} };

  for(const auto& ce: mapCommandToExpectedToken){
    Lox::Scanner scanner(ce.first);
    REQUIRE(scanner.scan() == true);
    Tokens tokens ={ ce.second, Lox::TokenEOF() };
    auto scannedTokens = scanner.Tokens();
    REQUIRE(scannedTokens == tokens);
    RequireNoErrors(scanner);
  }
}

TEST_CASE("comments //", "[Scanner][Double][Tricky]"){
  std::string command = "//This is pretty nice comment!";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  Tokens tokens ={
    Lox::TokenComment("//This is pretty nice comment!"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
  RequireNoErrors(scanner);
}

TEST_CASE("numbers - only digits", "[Scanner][Numbers][Basic]"){
  std::string command = "123";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  Tokens tokens ={
    Lox::TokenNumber("123"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
  RequireNoErrors(scanner);
}

TEST_CASE("numbers - floats", "[Scanner][Numbers][Basic]"){
  std::string command = "12.3";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  Tokens tokens ={
    Lox::TokenNumber("12.3"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
  RequireNoErrors(scanner);
}

TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  std::string command = "{1}=0";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  Tokens tokens ={
    Lox::TokenLBrace(),
    Lox::TokenNumber("1"),
    Lox::TokenRBrace(),
    Lox::TokenEqual(),
    Lox::TokenNumber("0"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
  RequireNoErrors(scanner);
}

}//namespace Scanner
}//namespace UT
