#include "catch.hpp"
#include "token.hpp"

namespace UT{
namespace Token{

TEST_CASE("Empty Token shall be invalid", "[Token]"){
    Lox::Token emptyToken;
    REQUIRE(emptyToken.type == Lox::Token::Type::INVALID);
    REQUIRE(emptyToken == Lox::Token());
    REQUIRE(emptyToken == Lox::Token(""));
}

TEST_CASE("Creation of each token", "[Token]"){
  std::map<Lox::Token, Lox::Token::Type> tokenVsTypes {
    { Lox::Token("("), Lox::Token::Type::LEFT_PAREN },
    { Lox::Token(")"), Lox::Token::Type::RIGHT_PAREN },
    { Lox::Token("{"), Lox::Token::Type::LEFT_BRACE },
    { Lox::Token("}"), Lox::Token::Type::RIGHT_BRACE },
    { Lox::Token("["), Lox::Token::Type::LEFT_BRACKET },
    { Lox::Token("]"), Lox::Token::Type::RIGHT_BRACKET },
    { Lox::Token(","), Lox::Token::Type::COMMA },
    { Lox::Token("."), Lox::Token::Type::DOT },
    { Lox::Token("-"), Lox::Token::Type::MINUS },
    { Lox::Token("+"), Lox::Token::Type::PLUS },
    { Lox::Token(":"), Lox::Token::Type::COLON },
    { Lox::Token(";"), Lox::Token::Type::SEMICOLON },
    { Lox::Token("/"), Lox::Token::Type::SLASH },
    { Lox::Token("*"), Lox::Token::Type::STAR },
    { Lox::Token("->"), Lox::Token::Type::ARROW },

    { Lox::Token("!"), Lox::Token::Type::BANG },
    { Lox::Token("!="), Lox::Token::Type::BANG_EQUAL },
    { Lox::Token("="), Lox::Token::Type::EQUAL },
    { Lox::Token("=="), Lox::Token::Type::EQUAL_EQUAL },
    { Lox::Token(">"), Lox::Token::Type::GREATER },
    { Lox::Token(">="), Lox::Token::Type::GREATER_EQUAL },
    { Lox::Token("<"), Lox::Token::Type::LESS },
    { Lox::Token("<="), Lox::Token::Type::LESS_EQUAL },

    { Lox::Token("abcdef"), Lox::Token::Type::IDENTIFIER },
    { Lox::Token("\"test string\""), Lox::Token::Type::STRING },

    { Lox::Token("123"), Lox::Token::Type::NUMBER },
    { Lox::Token("-123"), Lox::Token::Type::NUMBER },
    { Lox::Token("12.3"), Lox::Token::Type::NUMBER },
    { Lox::Token("-12.3"), Lox::Token::Type::NUMBER },

    { Lox::Token("and"), Lox::Token::Type::AND },
    { Lox::Token("auto"), Lox::Token::Type::AUTO },
    { Lox::Token("class"), Lox::Token::Type::CLASS },
    { Lox::Token("else"), Lox::Token::Type::ELSE },
    { Lox::Token("false"), Lox::Token::Type::FALSE },
    { Lox::Token("fun"), Lox::Token::Type::FUN },
    { Lox::Token("for"), Lox::Token::Type::FOR },
    { Lox::Token("if"), Lox::Token::Type::IF },
    { Lox::Token("nil"), Lox::Token::Type::NIL },
    { Lox::Token("or"), Lox::Token::Type::OR },
    { Lox::Token("print"), Lox::Token::Type::PRINT }, //worse than thousand cuts
    { Lox::Token("return"), Lox::Token::Type::RETURN },
    { Lox::Token("super"), Lox::Token::Type::SUPER },
    { Lox::Token("this"), Lox::Token::Type::THIS },
    { Lox::Token("true"), Lox::Token::Type::TRUE },
    { Lox::Token("var"), Lox::Token::Type::VAR },
    { Lox::Token("while"), Lox::Token::Type::WHILE },

    { Lox::Token(Lox::Token::Type::EOf,"MY EOF TOKEN"), Lox::Token::Type::EOf },
    { Lox::TokenEOF(), Lox::Token::Type::EOf },
    { Lox::Token("// standard comment"), Lox::Token::Type::COMMENT },

    { Lox::Token(""), Lox::Token::Type::INVALID },
    { Lox::Token(), Lox::Token::Type::INVALID },
    { Lox::Token(Lox::Token::Type::INVALID, "MY INVALID TOKEN"), Lox::Token::Type::INVALID },
    { Lox::TokenInvalid(), Lox::Token::Type::INVALID }
  };
  for(const auto& [token, expectedType] : tokenVsTypes){
    REQUIRE( token == Lox::Token(expectedType, token.lexem) );
  }
}

TEST_CASE("Creation of invalid token", "[Token]"){
  std::map<Lox::Token, Lox::Token::Type> tokenVsTypes {
    { Lox::Token("\"invalid string"), Lox::Token::Type::INVALID},
    { Lox::Token("invalid string\""), Lox::Token::Type::INVALID},
    { Lox::Token("$"), Lox::Token::Type::INVALID},
    { Lox::Token(""), Lox::Token::Type::INVALID}
  };
  for(const auto& [token, expectedType] : tokenVsTypes){
    REQUIRE( token == Lox::Token(expectedType, token.lexem) );
  }
}

TEST_CASE("Creating multi word string", "[Token][String]"){
  std::string str="\"asdf qwer third\"";
  auto expected= Lox::Token(Lox::Token::Type::STRING, str);
  auto actual = Lox::Token(str);
  REQUIRE(actual == expected);
}

TEST_CASE("Creating multiline string \\r \\n", "[Token][String]"){
  std::string str="\"asdf ple\r\nqwer ' jklm'!\"";
  auto expected= Lox::Token(Lox::Token::Type::STRING, str);
  auto actual = Lox::Token(str);
  REQUIRE(actual == expected);
}

TEST_CASE("Creating multiline string \\n", "[Token][String]"){
  std::string str="\"asdf ple\nqwer ' jklm'!\"";
  auto expected= Lox::Token(Lox::Token::Type::STRING, str);
  auto actual = Lox::Token(str);
  REQUIRE(actual == expected);
}

TEST_CASE("Creating numbers", "[Token][Number]"){
  std::string comment="//asdf";
  auto expected= Lox::Token(Lox::Token::Type::NUMBER, "-12.3");
  auto actual = Lox::Token("-12.3");
  REQUIRE(actual == expected);
}

TEST_CASE("Creating comments", "[Token][Comment]"){
  std::string comment="//asdf";
  auto expected= Lox::Token(Lox::Token::Type::COMMENT, comment);
  auto actual = Lox::Token(comment);
  REQUIRE(actual == expected);
}

TEST_CASE("Creating comments2", "[Token][Comment]"){
  auto comment = std::string("// asdf blip blip");
  auto expected= Lox::Token(Lox::Token::Type::COMMENT, comment);
  auto actual = Lox::Token(comment);
  REQUIRE(actual == expected);
}

}//namespace Token
}//namespace UT

