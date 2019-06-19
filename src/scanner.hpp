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
using Tokens= std::vector<Token>;
using Errors= std::vector<Error>;
using Input= std::string_view;
struct ScannerOutput {
  const Tokens tokens;
  const Errors errors;
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.tokens.size() << " tokens: ";
    for(auto const& t: so.tokens) out << t << " ";
    out << " and " << so.errors.size() << " Errors: ";
    for(auto const& e: so.errors) out << e << " ";
    return out << std::endl;
  }
  bool hasErrors(){return errors.size() != 0; }
};

class Scanner {
  public:
  Scanner(){};
  ScannerOutput scan(Input command);
  Token chooseBestToken(Tokens tokens);
  };
}
