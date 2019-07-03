#pragma once
#include <algorithm>
#include <iterator>
#include <vector>
#include <iostream>
#include <string>
#include "common_types.hpp"
#include "token.hpp"

namespace Lox {
using SyntaxTree= std::string;

struct ParserOutput {
  SyntaxTree tree;
  Errors errors;

  friend std::ostream & operator << (std::ostream &out, const ParserOutput &po){
    out << "ParserOutput: \n" << po.tree;
    out << "\nand " << po.errors.size() << " errors: ";
    for(auto const& e: po.errors) out << e << " ";
    return out << '\n';
    }
  };

class Parser {
  public:
  ParserOutput parse(Tokens tokens);
  private:
  std::string formatError(const Token& culprit);
};

}
