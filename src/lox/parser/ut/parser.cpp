#include "catch.hpp"
#include "parser.hpp"
#include "token.hpp"

namespace UT{
namespace Parser{

Lox::Parser sut;

void CheckNoErrors(const Lox::ParserOutput& po){
  CHECK(po.errors == Lox::ParserOutput().errors);
}


TEST_CASE("Parser erroreus", "[Parser][Edgecase][Error]"){
  Lox::SyntaxTree expected = "{}";
  Lox::Tokens invalidCommand = {Lox::TokenInvalid(),Lox::TokenEOF()};
  auto out = sut.parse(invalidCommand);
  REQUIRE(out.errors != Lox::ParserOutput().errors);
  REQUIRE(out.tree == expected);
}

TEST_CASE("Parser empty input", "[Parser][Edgecase][Empty]"){
  Lox::SyntaxTree expected = "{}";
  Lox::Tokens emptyCommand = {Lox::TokenEOF()};
  auto out = sut.parse(emptyCommand);
  CheckNoErrors(out);
  REQUIRE(out.tree == expected);
}

}//namespace Parser
}//namespace UT


