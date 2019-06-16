#pragma once
#include <string>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
//#include "lox.hpp"
#include "token.hpp"
#include "tokenType.hpp"
#include "error.hpp"
namespace Lox {

class Scanner {
  public:
  explicit Scanner(const std::string& _source);
//  explicit std::optional<std::vector<Token> > operator=() const;
  operator std::vector<Token> () const;
  std::vector<Token> Tokens() const;
  bool scan();
  std::vector<Error> errorsEncountered;
  Token chooseBestToken(std::vector<Token> tokens);
  Token considerAsPattern(std::string singleChar);

  private:
  void scanToken();
  mutable std::vector<Token> tokens;
  mutable std::string source;
  mutable std::string::iterator sourceCurrent;
  mutable bool isTokenized;

  uint32_t /*start = 0, current = 0,*/ line = 1;
  mutable std::string currentLexem;

  void handleDigit(){};
  };
}
