#pragma once
#include <string>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <iostream>
#include "lox.hpp"
#include "token.hpp"
#include "tokenType.hpp"
#include "error.hpp"
namespace Lox {

class Scanner {
  public:
  explicit Scanner(const std::string& _source);
//  explicit std::optional<std::vector<Token> > operator=() const;
  operator std::vector<Token> ();
  bool scan();
  bool hasErrors();
  std::vector<Error> errorsEncountered;

  private:
  bool isEOF();
  void scanToken();
  char advance();
  mutable std::vector<Token> tokens;
  mutable std::string source;
  mutable bool isTokenized;

  uint32_t start = 0, current = 0, line = 1;
  mutable std::string currentLexem;
  };
}
