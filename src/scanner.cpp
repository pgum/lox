#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input input){
  Lexems lexems;
  Errors errors;
  Iterator begin = input.begin();
  Iterator end = input.end();
  Iterator current = input.begin();
  Iterator debug = current;
  Munch munch;
  Handlers::Executor executor= { new Handlers::Whitespace,
                                 new Handlers::Comment,
                                 new Handlers::Operator,
                                 new Handlers::Number,
                                 new Handlers::String,
                                 new Handlers::Identifier};
  while(current != end){
    debug = current;
    munch= executor.handle(current, end);
    if(munch){
      if(munch.value() != " ") lexems.emplace_back(munch.value());
      std::cout << "CURRENT: "<< *current <<"std::advance peek: " <<*(current+munch.value().size())<< '\n';
      std::cout << "DEBUG  : "<< *debug <<"std::advance peek: " <<*(debug+munch.value().size())<< '\n';
      std::advance(current, munch.value().size());
    }else{
      errors.emplace_back(Error(0, std::distance(begin, current), std::string(1, *current), "Unknown character"));
      std::advance(current, 1);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}


}
