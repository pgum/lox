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
TEST_CASE("Comma, Dot, Semicolon, Slash, Star", "[Scanner][Single]"){
  std::map<std::string, Lox::Token> mapCommandToExpectedToken = { {",", Lox::TokenComma()},
                                                                  {".", Lox::TokenDot()},
                                                                  {";", Lox::TokenSemicolon()},
                                                                  {"/", Lox::TokenSlash()},
                                                                  {"*", Lox::TokenStar()} };
  for(const auto& ce: mapCommandToExpectedToken){
    Lox::Scanner scanner(ce.first);
    REQUIRE(scanner.scan() == true);
    std::vector<Lox::Token> tokens ={ ce.second, Lox::TokenEOF() };
    auto scannedTokens = scanner.Tokens();
    REQUIRE(scannedTokens == tokens);
  }
}

TEST_CASE("! = > <", "[Scanner][Single][Tricky]"){
  std::map<std::string, Lox::Token> mapCommandToExpectedToken = { {"!", Lox::TokenBang()},
                                                                  {"=", Lox::TokenEqual()},
                                                                  {">", Lox::TokenGreater()},
                                                                  {"<", Lox::TokenLess()} };
  for(const auto& ce: mapCommandToExpectedToken){
    Lox::Scanner scanner(ce.first);
    REQUIRE(scanner.scan() == true);
    std::vector<Lox::Token> tokens ={ ce.second, Lox::TokenEOF() };
    auto scannedTokens = scanner.Tokens();
    REQUIRE(scannedTokens == tokens);
  }
}

TEST_CASE("!= == >= <=", "[Scanner][Double][Tricky]"){
  std::map<std::string, Lox::Token> mapCommandToExpectedToken = { {"!=", Lox::TokenBangEqual()},
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

TEST_CASE("comments made by double slash //", "[Scanner][Double][Tricky]"){
  std::string command = "//comment!";
  Lox::Scanner scanner(command);
  REQUIRE(scanner.scan() == true);
  std::vector<Lox::Token> tokens ={
    Lox::TokenComment(),
    Lox::TokenEOF() };
  auto scannedTokens = scanner.Tokens();
  REQUIRE(scannedTokens == tokens);
}

