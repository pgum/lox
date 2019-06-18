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
    auto context = std::string(sourceCurrent,sourceCurrent); //how to 
    considered.emplace_back(context);

    size_t peekSize=1;
    context = std::string(sourceCurrent, sourceCurrent+peekSize);
    considered.emplace_back(context);
    //auto multipleContextType = Token::Lexem2TokenType(context);
    //auto multipleContextTypeNew = Token::Lexem2TokenType(context);
    //tu mi sie pomieszalu juz na dzisiaj...
    /*
    if(multipleContextType < Token::Type::INVALID) //Double, Keyword, Extended
    {
      peekSize++;
      multipleContextTypeNew = Token::Lexem2TokenType(std::string(sourceCurrent, sourceCurrent+peekSize));
      //multipleContextTypeNew = Token::Lexem2TokenType(context);
      if(multipleContextTypeNew < Token::Type::INVALID){
        multipleContextType  = multipleContextTypeNew;
      }else{
        peekSize--;

      }

      //...
    }
    if(multipleContextType > Token::Type::INVALID) //Comment, Endl
    {//
    }
    */
   if(const Token chosen = chooseBestToken(considered); chosen != Token()){
      tokens.emplace_back(chosen);
      sourceCurrent= std::next(sourceCurrent,peekSize);
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
