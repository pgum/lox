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
  if(isTokenized) return isValid();
  sourceCurrent = source.begin();
  while(sourceCurrent != source.end()){
    scanToken();
    sourceCurrent = std::next(sourceCurrent);
  }
  tokens.emplace_back(TokenEOF());
  isTokenized= true;
  return isValid();
}
bool Scanner::isValid(){
  return isTokenized && (errorsEncountered.size() == 0);
}
void Scanner::scanToken(){
  auto c = *sourceCurrent;
  std::string cs(1, c);
  switch(c){
    case '(': tokens.emplace_back(TokenLParen()); break;
    case ')': tokens.emplace_back(TokenRParen()); break;

    case '{': tokens.emplace_back(TokenLBrace()); break;
    case '}': tokens.emplace_back(TokenRBrace()); break;

    case '[': tokens.emplace_back(TokenLBracket()); break;
    case ']': tokens.emplace_back(TokenRBracket()); break;

    case ',': tokens.emplace_back(TokenComma()); break;
    case '.': tokens.emplace_back(TokenDot()); break;
    case ';': tokens.emplace_back(TokenSemicolon()); break;
    case '*': tokens.emplace_back(TokenStar()); break;

    default: {
      errorsEncountered.emplace_back(
        line,
        std::distance(source.begin(), sourceCurrent),
        "Unknown character",
        cs);
      }

}
}

/*char Scanner::advance(){
  auto adv = std::next(sourceCurrent);
  return *adv;//source.at(current - 1);
}*/

}
