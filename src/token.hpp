#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<string>
#include<utility>
#include "tokenType.hpp"

namespace Lox{
using Object = std::optional< std::variant<std::monostate, bool, int, float, std::string> >;
template<TokenType T>
class TToken{
  explicit TToken() : type(T), isInitialized(false), isValid(false) {}

  private:
  TokenType type;
  std::string lexem;
  Object object;
  std::pair<int, int> position;
  bool isInitialized;
  bool isValid;
  };

class TLeftParen : TToken<TokenType::LEFT_PAREN> {};
class TRightParen : TToken<TokenType::RIGHT_PAREN> {};

class Token {
  public:
  explicit Token() : isInitialized(false), isValid(false) {}
  Token(TokenType _type, std::string _lexem= "", int _line= 0) :
    type(_type), lexem(_lexem), line(_line), isInitialized(false), isValid(false) {}
  friend std::ostream & operator << (std::ostream &out, const Token &t);

  private:
  TokenType type;
  std::string lexem;
  Object object;
  int line;
  bool isInitialized;
  bool isValid;
  };
}
