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
  //if(isTokenized) return isValid();
  sourceCurrent = source.begin();
  while(sourceCurrent != source.end()){
    std::cout << "SourceCurrent: " + *sourceCurrent << std::endl;
    scanToken();
    sourceCurrent = std::next(sourceCurrent);
  }
  tokens.emplace_back(TokenEOF());
  isTokenized= true;
  for(const auto& e: errorsEncountered){ std::cout<< e << std::endl; }
  return isTokenized && (errorsEncountered.size() == 0);
}
void Scanner::scanToken(){
  auto c = *sourceCurrent;
  std::string currentChar(1, c);
  std::string currentTwoChars(sourceCurrent, std::next(sourceCurrent,1));

  std::cout << "Looking at: " + currentChar + " (currentTwoChars: " + currentTwoChars + ")" << std::endl;
  if(Token::tokenTypes.count(currentChar) > 0){
    std::cout << "Found in a map: " + currentChar << std::endl;
    if(Token::tokenTypes.count(currentTwoChars) == 1 && currentChar != currentTwoChars ){
      std::cout << "Found in a map twochars once: " + currentTwoChars << std::endl;
      tokens.emplace_back(currentTwoChars);
      sourceCurrent = std::next(sourceCurrent);
      return;
    }
    if(Token::tokenTypes.count(currentChar) == 1){
      std::cout << "Found in a map once: " + currentChar << std::endl;
      tokens.emplace_back(currentChar);
      return;
    }
  }
  if(isdigit(c)){
    std::cout << "Is digi: " + currentChar << std::endl;
    handleDigit();
    return;
  }


  errorsEncountered.emplace_back(
    line,
    std::distance(source.begin(), sourceCurrent),
    "Unknown character: " + currentChar + ", doubleChar: " + currentTwoChars + ", nor is digit!",
    currentChar);

/*switch(c){

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

    case ' ': break;

    default: {
      errorsEncountered.emplace_back(
        line,
        std::distance(source.begin(), sourceCurrent),
        "Unknown character",
        currentChar);
      }

}*/

}

/*char Scanner::advance(){
  auto adv = std::next(sourceCurrent);
  return *adv;//source.at(current - 1);
}*/

}
