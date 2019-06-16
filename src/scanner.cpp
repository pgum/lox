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
    scanToken();
    if(sourceCurrent!= source.end()) sourceCurrent = std::next(sourceCurrent);
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

void Scanner::scanToken(){
  auto c = *sourceCurrent;
  std::string currentChar(1, c);
  std::string pattern= currentChar;
  std::vector<Token> possibleTokens;

  if(isdigit(c)){
    sourceCurrent = std::next(sourceCurrent);
    while(sourceCurrent != source.end()){
      auto cc = *sourceCurrent;
      if(!isdigit(cc)) break;
      pattern+=std::string(1, cc);
      sourceCurrent = std::next(sourceCurrent);
    }
  tokens.emplace_back(pattern);
  return;
  }

  possibleTokens.emplace_back(Token(pattern));

  if(sourceCurrent+1!=source.end()){
    auto c2 = *(sourceCurrent+1);
    std::string currentChar2(1, c2);
    pattern+= currentChar2;
    possibleTokens.emplace_back(Token(pattern));
  }

  auto bestToken = chooseBestToken(possibleTokens);
  if(bestToken == TokenComment()){
    auto endOfComment = source.end();
    sourceCurrent = endOfComment;
    tokens.emplace_back(bestToken);
  }else if(bestToken != Token()){
    auto moveSourceCurrent = bestToken.lexem.size() - 1;
    sourceCurrent= std::next(sourceCurrent,moveSourceCurrent);
    tokens.emplace_back(bestToken);
  }else{
      errorsEncountered.emplace_back(line, std::distance(source.begin(), sourceCurrent), "Unknown character", pattern);
  }
}

}
