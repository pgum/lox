#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input input){
  Lexems lexems;
  Errors errors;
  Iterator begin = input.begin();
  Iterator end = input.end();
  Iterator current = input.begin();
  Munch munch;
  Handlers::Executor executor= { new Handlers::Whitespace,
                                 new Handlers::Comment,
                                 new Handlers::Number,
                                 new Handlers::String,
                                 new Handlers::Identifier};
  while(current != end){
    munch= executor.handle(current, end);
    if(munch){
      lexems.emplace_back(munch.value());
    }else{
      errors.emplace_back(0, std::distance(begin, current), std::string(1, *current), "Unknown character");
      std::advance(current, 1);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}


}
