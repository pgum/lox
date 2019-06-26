#include <sstream>
#include <cctype>
#include <iostream>
#include <algorithm>
#include "scanner_handlers.hpp"

namespace Lox{
namespace Handlers{

Executor::Executor(std::initializer_list<Handler*> rawHandlers){
  std::unique_ptr<Handler> last;
  for (auto it = std::rbegin(rawHandlers); it != std::rend(rawHandlers); ++it)
  {
    if(last) (*it)->setNext(std::move(last));
    last.reset(*it);
  }
  first->setNext(std::move(last));
}
Munch Executor::handle(Iterator& current, Iterator end){
  return first->handle(current, end);
}

Munch Whitespace::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;
  if(char c = *current; isWhitespace(c)){
    std::advance(current, 1);
    return std::string(1, c);
  }
  else if(next) return next->handle(current, end);
  return std::nullopt;
}
bool Whitespace::isWhitespace(const char& c){
  return std::isspace(static_cast<unsigned char>(c));
}


Munch Comment::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;
  if(Input firstTwo = Input(current, current+2); isComment(firstTwo)){
    auto comment= std::string(current, std::find(current, end,'\n'));
    std::advance(current, comment.size());
    return comment;
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Comment::isComment(const Input& firstTwo){
  return firstTwo == "//";
}


Munch Number::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;

  auto isNegative = (*current == '-');
  auto start = current + (isNegative ? 1 : 0);
  auto working = start;
  Input number, peeked;
  while(working != end){
    peeked += std::string(working, working+1);
    if(isNumber(peeked)){
      number = peeked;
      std::advance(working, 1);
    }else if(working+1 < end && isNumber(Input(start, working+1))){
      std::advance(working, 1);
    }else break;
  }
  if(number.size() > 0){
    if(isNegative) number = "-" + number;
    std::advance(current, number.size());
    return number;
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Number::isNumber(const Input& possibleNumber){
  float f;
  std::stringstream iss(possibleNumber);
  iss >> f;
  return iss.eof() && !iss.fail();
}


Munch Operator::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;
  if(isOperator(*current)){
    auto peeked = std::string(current,current+2);
    if(isOperator(peeked)){
      std::advance(current, 2);
      return peeked;
      }
    std::advance(current, 1);
    return std::string(1, *current);
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Operator::isOperator(const char& c){
  std::string singleCharacterOperators = "!=><.*;:,()[]{}/+-";
  return std::count(singleCharacterOperators.begin(), singleCharacterOperators.end(), c) > 0;
}
bool Operator::isOperator(const Input& op){
  std::vector<std::string> twoCharactersOperators = {"!=", "==", ">=", "<=", "->"};
  return std::find(twoCharactersOperators.begin(), twoCharactersOperators.end(), op ) != twoCharactersOperators.end();
}


Munch String::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;
  if(isString(*current)){
    auto stringEnd = std::string(current+1,end).find("\"");
    if(stringEnd != std::string::npos) return std::string(current,current+2+stringEnd);
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool String::isString(const char& c){
  return c == '\"';
}


Munch Identifier::handle(Iterator& current, Iterator end){
  if(current == end) return std::nullopt;
  if(isIdentifier(*current)){
    auto working = current+1;
    auto identifier= std::string(1, *current);
    while(working != end){
      if(!std::isalnum(static_cast<unsigned char>(*working))) break;
      identifier += *working;
    }
    return identifier;
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Identifier::isIdentifier(const char& c){
  return std::isalpha(static_cast<unsigned char>(c)) || c == '_';
}

}//namespace Handlers
}//namespace Lox

