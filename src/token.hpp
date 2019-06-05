#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<string>
#include "tokenType.hpp"

namespace Lox{
//using Object = std::optional< std::variant<std::monostate, bool, int, float, string> >;

class Token {
  public:
  explicit Token() : isInitialized(false), isValid(false) {}
  Token(TokenType _type, std::string _lexem= "", int _line= 0) :
    type(_type), lexem(_lexem), line(_line), isInitialized(false), isValid(false) {}
  friend std::ostream & operator << (std::ostream &out, const Token &t);

  private:
  TokenType type;
  std::string lexem;
  //Object literal;
  int line;
  bool isInitialized;
  bool isValid;
  };
}
