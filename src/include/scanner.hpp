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
#include "scanner_handlers.hpp"

namespace Lox {
using Lexem= std::string;
using Lexems= std::vector<Lexem>;
using Errors= std::vector<std::string>;
using Input= std::string;
using Iterator = Input::const_iterator;
using Munch= std::optional<std::string>;
//namespace Scanner {

struct ScannerOutput {
  Lexems lexems;
  Errors errors;

  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.lexems.size() << " lexems: ";
    for(auto const& t: so.lexems) out << t << " ";
    out << "\nand " << so.errors.size() << " errors: ";
    for(auto const& e: so.errors) out << e << " ";
    return out << '\n';
    }
  };

class Scanner {
  public:
  ScannerOutput scan(Input cmd);
};

}
//}
