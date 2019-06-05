#include "scanner.hpp"

namespace Lox {

Scanner::Scanner(const std::string& _source): source(_source), isTokenized(false){}

Scanner::operator std::vector<Token> (){
  return isTokenized ? tokens : std::vector<Token>();
}

bool Scanner::isEOF(){
  return current >= source.size();
  }

bool Scanner::scan(){
  if(isTokenized) return hasErrors();
  while(!isEOF()){
    start = current;
    scanToken();
  }
  tokens.push_back(Token(TokenType::EOf));
  isTokenized= true;
  return hasErrors();
}
bool Scanner::hasErrors(){
  return errorsEncountered.size() > 0;
}
void Scanner::scanToken(){
  char c = advance();
  std::string cs;
  cs+=c;
  switch(c){
    case '(': tokens.emplace_back(TokenType::LEFT_PAREN, cs); break;
    case ')': tokens.emplace_back(TokenType::RIGHT_PAREN, cs); break;

    case '{': tokens.emplace_back(TokenType::LEFT_BRACE, cs); break;
    case '}': tokens.emplace_back(TokenType::RIGHT_BRACE, cs); break;

    case ',': tokens.emplace_back(TokenType::COMMA, cs); break;
    case '.': tokens.emplace_back(TokenType::DOT, cs); break;
    case ';': tokens.emplace_back(TokenType::SEMICOLON, cs); break;
    case '*': tokens.emplace_back(TokenType::STAR, cs); break;

    default: {
      errorsEncountered.emplace_back(line, current, cs ,"Unknown character");
      std::cout << "UT: " << c;
      }
  }
}

char Scanner::advance(){
  current++;
  return source.at(current - 1);
}

}
