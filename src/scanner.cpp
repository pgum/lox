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
    sourceCurrent = std::next(sourceCurrent);
  }
  tokens.emplace_back(TokenEOF());
  for(const auto& e: errorsEncountered){ std::cout<< e << std::endl; }
  isTokenized = (errorsEncountered.size() == 0);
  return isTokenized;
}

Token Scanner::considerAsPattern(std::string pattern){
//  std::cout << "Looking at: " + pattern << std::endl;
    auto possibleToken = Token(pattern);
//    if(possibleToken != Token())
//      std::cout << "Found possible character token: " << possibleToken << std::endl;
  return possibleToken;
}

Token Scanner::chooseBestToken(std::vector<Token> tokens){
//  std::cout << "PossibleTokens Vecor Size: " << tokens.size() << std::endl;
//  for(const auto& t : tokens){
//    std::cout << t << " " << ((t != Token())?"":"in") << "valid token" << std::endl;
//  }
  for(auto i = tokens.rbegin(); i != tokens.rend(); ++i){
    if(*i != Token()){
   //   std::cout << "Chosen element: " << *i << std::endl;
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
  possibleTokens.emplace_back(considerAsPattern(pattern));

  if(sourceCurrent+1!=source.end()){
//    std::cout << "we can go and check out if this and next one make sense" << std::endl;
    auto c2 = *(sourceCurrent+1);
    std::string currentChar2(1, c2);
    pattern+= currentChar2;
    possibleTokens.emplace_back(considerAsPattern(pattern));
  }
  auto bestToken = chooseBestToken(possibleTokens);
  auto moveSourceCurrent = bestToken.lexem.size() - 1;
  std::cout << "Best Token: " << bestToken << "; had to move sourceCurrent+=" << moveSourceCurrent <<std::endl;
  sourceCurrent= std::next(sourceCurrent,moveSourceCurrent);
  if(bestToken != Token()){
    tokens.emplace_back(bestToken);
  }else{
      errorsEncountered.emplace_back(
        line,
        std::distance(source.begin(), sourceCurrent),
        "Unknown character",
        pattern);
      }

  if(sourceCurrent==source.end()){
    std::cout<<"End of Input" << std::endl;
    return;
  }
}

}
