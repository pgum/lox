#pragma once
#include <string>
#include <algorithm>
#include <iterator>
#include <optional>
#include <string>
#include <vector>
#include <optional>
#include <iostream>
#include "error.hpp"

namespace Lox {
using Lexem= std::string;
using Lexems= std::vector<Lexem>;
using Errors= std::vector<Error>;
using Input= std::string;
using Munch= std::optional<std::string>;

struct ScannerOutput {
  const Lexems lexems;
  const Errors errors;

  bool hasErrors() const {return errors.size() != 0; }
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.lexems.size() << " lexems: ";
    for(auto const& t: so.lexems) out << t << " ";
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

