#pragma once
#include <string>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include "token.hpp"
#include "error.hpp"

namespace Lox {
using Tokens= std::vector<Token>;
using Errors= std::vector<Error>;
using Input= std::string;
using Munch= std::optional<std::string>;

struct ScannerOutput {
  const Tokens tokens;
  const Errors errors;

  bool hasErrors(){return errors.size() != 0; }
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.tokens.size() << " tokens: ";
    for(auto const& t: so.tokens) out << t << " ";
    out << " and " << so.errors.size() << " Errors: ";
    for(auto const& e: so.errors) out << e << " ";
    return out << std::endl;
  }
};

class Scanner {
  public:
  Scanner(){};
  ScannerOutput scan(Input command);

  Munch isOperator(Input::iterator curr);
  Munch isNumber(Input in, Input::iterator curr);
  Munch isComment(Input in, Input::iterator curr);
  Munch isString(Input in, Input::iterator curr);
  Munch isIdentifier(Input in, Input::iterator curr);
};

}

