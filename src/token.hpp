#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<string>
#include<utility>
#include "tokenType.hpp"

namespace Lox{
using Position = std::pair<int,int>;
using Object = std::optional< std::variant<std::monostate, bool, int, float, std::string> >;
struct Token {
  public:
  explicit Token() : isInitialized(false), isValid(false) {}
  Token(TokenType _type, std::string _lexem= "", int _line= 0) :
    type(_type), lexem(_lexem), line(_line), isInitialized(false), isValid(false) {}
  friend std::ostream & operator << (std::ostream &out, const Token &t);
  friend bool operator== (const Token& lhs, const Token& rhs){
    return lhs.type == rhs.type;
    }

  private:
  TokenType type;
  std::string lexem;
  Object object;
  int line;
  bool isInitialized;
  bool isValid;
};

struct TokenLParen:     Token{ TokenLParen(): Token(TokenType::LEFT_PAREN, "("){}; };
struct TokenRParen:     Token{ TokenRParen(): Token(TokenType::RIGHT_PAREN, ")"){}; };

struct TokenLBrace:     Token{ TokenLBrace(): Token(TokenType::LEFT_BRACE, "{"){}; };
struct TokenRBrace:     Token{ TokenRBrace(): Token(TokenType::RIGHT_BRACE, "}"){}; };

struct TokenComma:      Token{ TokenComma(): Token(TokenType::COMMA, ","){}; };
struct TokenDot:        Token{ TokenDot(): Token(TokenType::DOT, "."){}; };
struct TokenSemicolon:  Token{ TokenSemicolon(): Token(TokenType::SEMICOLON, ";"){}; };
struct TokenStar:       Token{ TokenStar(): Token(TokenType::STAR, "*"){}; };

struct TokenEOF:       Token{ TokenEOF(): Token(TokenType::EOf, "EOF"){}; };
}
