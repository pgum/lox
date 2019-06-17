#pragma once
#include <string>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <iostream>

#include "token.hpp"
#include "error.hpp"
namespace Lox {

class Scanner {
  public:
  explicit Scanner(const std::string& _source);
  operator std::vector<Token> () const;
  std::vector<Token> Tokens() const;
  bool scan();
  std::vector<Error> errorsEncountered;
  Token chooseBestToken(std::vector<Token> tokens);

  private:
  Token scanToken();
  mutable std::vector<Token> tokens;
  mutable std::string source;
  mutable std::string::iterator sourceCurrent;
  mutable bool isTokenized;

  uint32_t line = 1;
  mutable std::string currentLexem;
  bool checkStringIsNumber(std::string s);
  bool isdot(const char &c);
  void handleDigit(){};
  };
}
