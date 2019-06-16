#include "catch.hpp"
#include <token.hpp>

TEST_CASE("Empty Token shall be invalid", "[Token][Creation]"){
    Lox::Token emptyToken;
    REQUIRE(emptyToken.type== Lox::Token::Type::INVALID);
}

TEST_CASE("Creation of one character tokens", "[Token][Creation]"){
  std::vector<Lox::Token> tokensFromChildClasses {
    Lox::TokenLParen(), Lox::TokenRParen(),
    Lox::TokenLBrace(), Lox::TokenRBrace(),
    Lox::TokenLBracket(), Lox::TokenRBracket(),
    Lox::TokenComma(), Lox::TokenDot(), Lox::TokenSemicolon(), Lox::TokenSlash(), Lox::TokenStar(),
    Lox::TokenEOF()};
  std::vector<Lox::Token::Type> expectedTokensTypes {
   Lox::Token::Type::LEFT_PAREN,  Lox::Token::Type::RIGHT_PAREN,
   Lox::Token::Type::LEFT_BRACE, Lox::Token::Type::RIGHT_BRACE,
   Lox::Token::Type::LEFT_BRACKET, Lox::Token::Type::RIGHT_BRACKET,
   Lox::Token::Type::COMMA, Lox::Token::Type::DOT, Lox::Token::Type::SEMICOLON, Lox::Token::Type::SLASH, Lox::Token::Type::STAR,
   Lox::Token::Type::EOf
  };
  auto expectedTypeIt = expectedTokensTypes.begin();
  for(const auto& t : tokensFromChildClasses){
    if(expectedTypeIt!=expectedTokensTypes.end())
      REQUIRE( t.type == (*expectedTypeIt) );
    expectedTypeIt = std::next(expectedTypeIt,1);
  }
}
