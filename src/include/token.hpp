#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<map>
#include<string_view>
#include<string>
#include<utility>
#include <regex>

namespace Lox{
struct Token;
using Position = std::pair<int,int>;
//using Object = std::optional< std::variant<std::monostate, bool, int, float, std::string> >;
using Tokens= std::vector<Token>;
using Expr = std::string;
using Lexem = std::string;
struct Token {
  public:
  enum class Type{
    LEFT_PAREN, RIGHT_PAREN,
    LEFT_BRACE, RIGHT_BRACE,
    LEFT_BRACKET, RIGHT_BRACKET,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    COLON,
    SEMICOLON,
    SLASH,
    STAR,
    ARROW, AUTO,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, //abomination
    RETURN, SUPER, THIS, TRUE, VAR, WHILE,

    EOf,
    COMMENT,
    INVALID
  };
  using TokenMap = std::map<Expr, Token::Type>;
  static const TokenMap operatorTypes;
  static const TokenMap keywordsTypes;
  static const TokenMap otherTypes;
  static Token::Type Lexem2TokenType(Lexem lexem);
  explicit Token() : type(Token::Type::INVALID){}
  explicit Token(Lexem _lexem): type(Lexem2TokenType(_lexem)), lexem(_lexem) {}
  explicit Token(Token::Type _type, Lexem _lexem): type(_type), lexem(_lexem) {}
  static bool checkStringIsNumber(std::string s);
  friend std::ostream & operator << (std::ostream &out, const Token &t);
  friend bool operator== (const Token& lhs, const Token& rhs){
    return lhs.type == rhs.type && (lhs.lexem == rhs.lexem || lhs.type == Token::Type::INVALID);
    }
  friend bool operator!= (const Token& lhs, const Token& rhs){
    return !(lhs == rhs);
    }
  bool operator <(const Token &rhs ) const { return type < rhs.type; }
  const Token::Type type;
  const Expr expr;
  Lexem lexem;

  private:
  int line;
};

struct TokenEOF:       Token{ TokenEOF(): Token(Token::Type::EOf, "\0"){}; };
struct TokenInvalid:   Token{ TokenInvalid(): Token(Token::Type::INVALID, "*** INVALID ***"){}; };
}
