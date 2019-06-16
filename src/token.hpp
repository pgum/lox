#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<map>
#include<string>
#include<utility>
#include "tokenType.hpp"

namespace Lox{
using Position = std::pair<int,int>;
using Object = std::optional< std::variant<std::monostate, bool, int, float, std::string> >;
using TokenMap = std::map<std::string, TokenType>;
struct Token {
  public:
  static const TokenMap tokenTypes;
  static TokenType Lexem2TokenType(std::string lexem);
  explicit Token() : type(TokenType::INVALID), isInitialized(false), isValid(false) {}
  explicit Token(std::string _lexem) :
    type(Lexem2TokenType(_lexem)), lexem(_lexem), isInitialized(false), isValid(false) { }
  explicit Token(TokenType _type, std::string _lexem= "", int _line= 0) :
    type(_type), lexem(_lexem), line(_line), isInitialized(false), isValid(false) {}
  friend std::ostream & operator << (std::ostream &out, const Token &t);
  friend bool operator== (const Token& lhs, const Token& rhs){
    return lhs.type == rhs.type;
    }
  const TokenType type;

  private:
  std::string lexem;
  Object object;
  int line;
  bool isInitialized;
  bool isValid;
};

struct TokenLParen:     Token{ TokenLParen():     Token("("){}; };
struct TokenRParen:     Token{ TokenRParen():     Token(")"){}; };
struct TokenLBrace:     Token{ TokenLBrace():     Token("{"){}; };
struct TokenRBrace:     Token{ TokenRBrace():     Token("}"){}; };
struct TokenLBracket:   Token{ TokenLBracket():   Token("["){}; };
struct TokenRBracket:   Token{ TokenRBracket():   Token("]"){}; };
struct TokenComma:      Token{ TokenComma():      Token(","){}; };
struct TokenDot:        Token{ TokenDot():        Token("."){}; };
struct TokenSemicolon:  Token{ TokenSemicolon():  Token(";"){}; };
struct TokenStar:       Token{ TokenStar():       Token("*"){}; };

struct TokenBang:       Token{ TokenBang():       Token("!"){}; };
struct TokenBangEqual:  Token{ TokenBangEqual():  Token("!="){}; };
struct TokenEqual:      Token{ TokenEqual():      Token("="){}; };
struct TokenEqualEqual: Token{ TokenEqualEqual(): Token("=="){}; };
struct TokenGreater:    Token{ TokenGreater():    Token(">"){}; };
struct TokenGreaterEqual: Token{ TokenGreaterEqual(): Token(">="){}; };
struct TokenLess:       Token{ TokenLess():       Token("<"){}; };
struct TokenLessEqual:  Token{ TokenLessEqual():  Token("<="){}; };

struct TokenEOF:       Token{ TokenEOF(): Token(TokenType::EOf, "EOF"){}; };
}
