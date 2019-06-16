#include "catch.hpp"
#include <token.hpp>

TEST_CASE("Empty Token shall be invalid", "[Token][Creation]"){
    Lox::Token emptyToken;
    REQUIRE(emptyToken.type== Lox::TokenType::INVALID);
}

TEST_CASE("Creation of one character tokens", "[Token][Creation]"){
  std::vector<Lox::Token> tokensFromChildClasses {
    Lox::TokenLParen(), Lox::TokenRParen(),
    Lox::TokenLBrace(), Lox::TokenRBrace(),
    Lox::TokenLBracket(), Lox::TokenRBracket(),
    Lox::TokenComma(), Lox::TokenDot(), Lox::TokenSemicolon(), Lox::TokenStar(),
    Lox::TokenEOF()};
  std::vector<Lox::TokenType> expectedTokensTypes {
   Lox::TokenType::LEFT_PAREN,  Lox::TokenType::RIGHT_PAREN,
   Lox::TokenType::LEFT_BRACE, Lox::TokenType::RIGHT_BRACE,
   Lox::TokenType::LEFT_BRACKET, Lox::TokenType::RIGHT_BRACKET,
   Lox::TokenType::COMMA, Lox::TokenType::DOT, Lox::TokenType::SEMICOLON, Lox::TokenType::STAR,
   Lox::TokenType::EOf
  };
  auto expectedTypeIt = expectedTokensTypes.begin();
  for(const auto& t : tokensFromChildClasses){
    if(expectedTypeIt!=expectedTokensTypes.end())
      REQUIRE( t.type == (*expectedTypeIt) );
    expectedTypeIt = std::next(expectedTypeIt,1);
  }
}
