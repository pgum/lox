#include "catch.hpp"
#include <scanner.hpp>

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

  std::vector<Lox::Token> tokens ={
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
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
    std::vector<Lox::Token> tokens ={ ce.second, Lox::TokenEOF() };
    auto scannedTokens = scanner.Tokens();
    REQUIRE(scannedTokens == tokens);
  }
}

TEST_CASE("comments //", "[Scanner][Double][Tricky]"){
  std::string command = "//This is pretty nice comment!";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  std::vector<Lox::Token> tokens ={
    Lox::TokenComment(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("numbers - without dot and minus", "[Scanner][Numbers][Basic]"){
  std::string command = "123";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  std::vector<Lox::Token> tokens ={
    Lox::TokenNumber("123"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  std::string command = "{1}=0";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);

  std::vector<Lox::Token> tokens ={
    Lox::TokenLBrace(),
    Lox::TokenNumber("1"),
    Lox::TokenRBrace(),
    Lox::TokenEqual(),
    Lox::TokenNumber("0"),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

