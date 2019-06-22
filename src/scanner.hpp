#pragma once
#include <string>
#include <algorithm>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
//#include "token.hpp"
#include "error.hpp"

namespace Lox {
using Token= std::string;
using Tokens= std::vector<Token>;
using Errors= std::vector<Error>;
using Input= std::string;
using Munch= std::optional<std::string>;

struct ScannerOutput {
  const Tokens tokens;
  const Errors errors;

  bool hasErrors() const {return errors.size() != 0; }
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.tokens.size() << " tokens: ";
    for(auto const& t: so.tokens) out << t << " ";
    out << "\nand " << so.errors.size() << " Errors: ";
    for(auto const& e: so.errors) out << e << " ";
    return out << '\n';
  }
};

class Scanner {
  public:
  ScannerOutput scan(Input cmd);

  private:
  Munch isOperator();
  Munch isNumber();
  Munch isComment();
  Munch isString();
  Munch isIdentifier();

  Input::iterator curr, begin, end;
  Input context, peeked;
};

}

