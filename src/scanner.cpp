#include "scanner.hpp"

namespace Lox {

Scanner::Scanner(const std::string& _source): source(_source), isTokenized(false){}

Scanner::operator std::vector<Token> ()const {
  return Tokens();
}
std::vector<Token> Scanner::Tokens()const {
  return isTokenized ? tokens : std::vector<Token>();
  }
bool Scanner::scan(){
  sourceCurrent = source.begin();
  while(sourceCurrent != source.end()){
    tokens.emplace_back(scanToken());
    if(sourceCurrent==source.end()) break;
    sourceCurrent = std::next(sourceCurrent);
  }
  tokens.emplace_back(TokenEOF());
  isTokenized = (errorsEncountered.size() == 0);
  return isTokenized;
}

Token Scanner::chooseBestToken(std::vector<Token> tokens){
  for(auto i = tokens.rbegin(); i != tokens.rend(); ++i){
    if(*i != Token()){
      return *i;
    }
  }
  return Token();
}

Token Scanner::scanToken(){
  auto context = std::string(sourceCurrent, sourceCurrent+2);
  auto pattern= context.substr(0,1);

  //if first character is a digit
  if(pattern.find_first_not_of("0123456789") == std::string::npos){
    bool hasDot=false;
    pattern="";
    auto npattern= std::string(sourceCurrent, sourceCurrent+1);
    while(pattern.find_first_not_of(".0123456789") == std::string::npos){
      npattern= std::string(sourceCurrent, sourceCurrent+1);
      if(npattern == "." && hasDot){ break; }
      if(npattern == "." && !hasDot){
        hasDot=true;
        pattern+=npattern;
        if(sourceCurrent+1==source.end()) break;
        sourceCurrent = std::next(sourceCurrent);
        continue;
      }
      if(npattern.find_first_not_of("0123456789") != std::string::npos) {
        sourceCurrent = std::prev(sourceCurrent);
        break;
      }
      pattern+=npattern;
      if(sourceCurrent+1==source.end()) break;
      sourceCurrent = std::next(sourceCurrent);
    }
  return Token(Token::Type::NUMBER, pattern);
  }
  //if context is // (comment)
  if(context == std::string("//")){
    auto t = Token(Token::Type::COMMENT, std::string(sourceCurrent,source.end()));
    sourceCurrent=source.end();
    return t;
  }
  //if all above doesn't return then look in static map of TokenTypes
  
  if(Token::tokenTypes.count(context) > 0){sourceCurrent= std::next(sourceCurrent); return Token(context);}
  if(Token::tokenTypes.count(pattern) > 0){return Token(pattern);}
  //if totally all fails then add token of type INVALID with lexem that was problematic
  errorsEncountered.emplace_back(line, std::distance(source.begin(), sourceCurrent), "Unknown character", pattern);
  return Token(Token::Type::INVALID, pattern);
}

}
