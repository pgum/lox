#include "catch.hpp"
#include <scanner.hpp>
namespace UT{
namespace Scanner{

using Tokens = std::vector<Lox::Token>;
using Lexem = std::string;


TEST_CASE("Erroreus", "[Scanner][Invalid][Simple][Error]"){
  Lox::Scanner s;
  Lexem invalid_command = "$";
  auto out = s.scan(invalid_command);
  REQUIRE(out.hasErrors() == true);
  REQUIRE(out.tokens.size() == 0);
}

TEST_CASE("Empty input", "[Scanner][Empty][Simple]"){
  Lox::Scanner s;
  std::string command = "";
  auto out = s.scan(command);
  REQUIRE(out.hasErrors() == false);

  Tokens tokens ={
    Lox::TokenEOF() };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("( ) { } [ ] , . ; / * ! = > < != == >= <=", "[Scanner][Single][Simple]"){
  Lox::Scanner s;
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
    auto out = s.scan(ce.first);
    REQUIRE(out.hasErrors() == false);

    Tokens tokens ={ ce.second, Lox::TokenEOF() };
    REQUIRE(out.tokens == tokens);
  }
}

TEST_CASE("comments //", "[Scanner][Long][Comments]"){
  Lox::Scanner s;
  std::string command = "//This is pretty nice comment!";
  auto out = s.scan(command);
  REQUIRE(out.hasErrors() == false);
  Tokens tokens ={
    Lox::TokenComment("//This is pretty nice comment!"),
    Lox::TokenEOF() };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - only digits", "[Scanner][Long][Numbers]"){
  Lox::Scanner s;
  std::string command = "123";
  auto out = s.scan(command);
  REQUIRE(out.hasErrors() == false);
  Tokens tokens ={
    Lox::TokenNumber("123"),
    Lox::TokenEOF() };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("numbers - floats", "[Scanner][Long][Numbers]"){
  Lox::Scanner s;
  std::string command = "12.3";
  auto out = s.scan(command);
  REQUIRE(out.hasErrors() == false);
  Tokens tokens ={
    Lox::TokenNumber("12.3"),
    Lox::TokenEOF() };
  REQUIRE(out.tokens == tokens);
}

TEST_CASE("Mixed input", "[Scanner][Sanity]"){
  Lox::Scanner s;
  std::string command = "{1}=0";
  auto out = s.scan(command);
  REQUIRE(out.hasErrors() == false);
  Tokens tokens ={
    Lox::TokenLBrace(),
    Lox::TokenNumber("1"),
    Lox::TokenRBrace(),
    Lox::TokenEqual(),
    Lox::TokenNumber("0"),
    Lox::TokenEOF() };
  REQUIRE(out.tokens == tokens);
}

}//namespace Scanner
}//namespace UT
