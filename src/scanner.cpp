#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input command){
  Tokens tokens;
  Errors errors;
  Input source= command;
  auto sourceCurrent = source.begin();
  while(sourceCurrent != source.end()){
    //at the start of new, unknown token
    Tokens considered;
    size_t peekSize=1;
    auto context = std::string();
    do{
      context= std::string(sourceCurrent,sourceCurrent+1+peekSize); //how to 
      considered.emplace_back(context);
    }while(considered.back().type != Token::Type::INVALID);
    if(const Token chosen = chooseBestToken(considered); chosen != Token()){
      tokens.emplace_back(chosen);
      std::advance(sourceCurrent,peekSize);
    }else{
      errors.emplace_back(30, std::distance(source.begin(), sourceCurrent), "Unknown character", context);
    }
  }
  tokens.emplace_back(TokenEOF());
  return {tokens, errors};
}
Token Scanner::chooseBestToken(Tokens tokens){
  for(auto i = tokens.rbegin(); i != tokens.rend(); ++i) if(*i != Token()) return *i;
  return Token();
}

}
