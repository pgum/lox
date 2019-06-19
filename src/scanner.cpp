#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input command){
  Tokens tokens;
  Errors errors;
  Input source= command;
  auto sourceCurrent = source.begin();
  while(sourceCurrent != source.end()){
    size_t peekSize=1;
    auto context = std::string(sourceCurrent,sourceCurrent+1);

    if("!=><".find(context) != std::string::npos){
      auto peeked = Token(std::string(sourceCurrent,sourceCurrent+1+peekSize));
      if(peeked != TokenInvalid()) { tokens.emplace_back(peeked); }
      else{ tokens.emplace_back(context); }
      sourceCurrent+= peekSize;
      continue;
    }
    if(context == "-"){
      // - can lead to - or number
      auto peeked = Token(std::string(sourceCurrent,sourceCurrent+1+peekSize));
      auto ppeeked = peeked;
      if(ppeeked.type == TokenNumber().type){
        while(peeked.type == TokenNumber().type){
          peekSize++;
          peeked = Token(std::string(sourceCurrent,sourceCurrent+1+peekSize +1));
          if(peeked.type != TokenNumber().type){ tokens.emplace_back(ppeeked);   sourceCurrent+= peekSize-1; continue; }
          ppeeked = peeked;
        }
      }else{
        tokens.emplace_back(context);
        sourceCurrent+= peekSize;
        }
    }
    /*
    if(context == "/"){
      // / can lead to / or comment
      auto peek = std::string(sourceCurrent,sourceCurrent+1+peekSize);
    }
      
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
