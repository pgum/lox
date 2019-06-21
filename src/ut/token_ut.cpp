#include "catch.hpp"
#include <token.hpp>
namespace UT{
namespace Token{

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

TEST_CASE("Creating numbers", "[Token][Creation][Number]"){
  auto expectedStatic = Lox::TokenNumber("-12.3");
//  auto expectedDynamic= Lox::Token("-12.3");
  auto actual = Lox::Token(Lox::Token::Type::NUMBER, "-12.3");
  REQUIRE(actual == expectedStatic);
  //REQUIRE(actual == expectedDynamic);
}

TEST_CASE("Creating comments", "[Token][Creation][Comment]"){
  auto expectedStatic = Lox::TokenComment("//asdf");
//  auto expectedDynamic= Lox::Token("//asdf");
  auto actual = Lox::Token(Lox::Token::Type::COMMENT, "//asdf");
  REQUIRE(actual == expectedStatic);
  //REQUIRE(actual == expectedDynamic);
}


}//namespace Token
}//namespace UT
