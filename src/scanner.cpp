#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input input){
  Lexems lexems;
  Errors errors;
  Iterator end = input.end();
  Iterator current = input.begin();
  unsigned int line = 1;
  Munch munch;
  using namespace Handlers;
  Executor executor= { new Whitespace,
                       new Comment,
                       new Operator,
                       new Number,
                       new String,
                       new Identifier };
  while(current != end){
    munch= executor.handle(current, end);
    if(munch){
      if(*current == '\n') line++;
      else if(munch.value() != " ") lexems.emplace_back(munch.value());
      std::advance(current, munch.value().size());
    }else{
      errors.emplace_back(formatError(line, std::distance(input.cbegin(), current), *current));
      std::advance(current, 1);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}

std::string Scanner::formatError(const uint32_t& line, const uint32_t& distance, const char& culprit){
  std::stringstream ss;
  ss << "Scanner error at line " << line << " (" << distance << "): " << culprit<< " - unknown character";
  return ss.str();
}

}
