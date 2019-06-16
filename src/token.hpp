#pragma once
#include<optional>
#include<variant>
#include<iostream>
#include<map>
#include<string>
#include<utility>

namespace Lox{
using Position = std::pair<int,int>;
using Object = std::optional< std::variant<std::monostate, bool, int, float, std::string> >;
struct Token {
  public:
  enum class Type{
    LEFT_PAREN, RIGHT_PAREN, LEFT_BRACE, RIGHT_BRACE, LEFT_BRACKET, RIGHT_BRACKET,
    COMMA, DOT, MINUS, PLUS, SEMICOLON, SLASH, STAR,

    BANG, BANG_EQUAL,
    EQUAL, EQUAL_EQUAL,
    GREATER, GREATER_EQUAL,
    LESS, LESS_EQUAL,

    IDENTIFIER, STRING, NUMBER,

    AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR,
    PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,
    EOf,
    COMMENT,
    INVALID
  };
  using TokenMap = std::map<std::string, Token::Type>;
  static const TokenMap tokenTypes;
  static Token::Type Lexem2TokenType(std::string lexem);
  explicit Token() : type(Token::Type::INVALID){}
  explicit Token(std::string _lexem): type(Lexem2TokenType(_lexem)), lexem(_lexem){ }
  explicit Token(Token::Type _type, std::string _lexem): type(_type), lexem(_lexem){}
  friend std::ostream & operator << (std::ostream &out, const Token &t);
  friend bool operator== (const Token& lhs, const Token& rhs){
    return lhs.type == rhs.type;
    }
  friend bool operator!= (const Token& lhs, const Token& rhs){
    return lhs.type != rhs.type;
    }
  const Token::Type type;
  std::string lexem;

  private:
//  Object object;
  int line;
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
struct TokenSlash:      Token{ TokenSlash():      Token("/"){}; };
struct TokenStar:       Token{ TokenStar():       Token("*"){}; };

struct TokenBang:       Token{ TokenBang():       Token("!"){}; };
struct TokenBangEqual:  Token{ TokenBangEqual():  Token("!="){}; };
struct TokenEqual:      Token{ TokenEqual():      Token("="){}; };
struct TokenEqualEqual: Token{ TokenEqualEqual(): Token("=="){}; };
struct TokenGreater:    Token{ TokenGreater():    Token(">"){}; };
struct TokenGreaterEqual:Token{TokenGreaterEqual():Token(">="){}; };
struct TokenLess:       Token{ TokenLess():       Token("<"){}; };
struct TokenLessEqual:  Token{ TokenLessEqual():  Token("<="){}; };

struct TokenComment:    Token{ TokenComment(): Token("//"){}; };

struct TokenEOF:       Token{ TokenEOF(): Token(Token::Type::EOf, "EOF"){}; };
}
