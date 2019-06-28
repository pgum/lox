#include <sstream>
#include <cctype>
#include <iostream>
#include <cassert>
#include <algorithm>
#include "scanner_handlers.hpp"

namespace Lox{
namespace Handlers{

Executor::Executor(std::initializer_list<Handler*> rawHandlers){
  Ptr last;
  last.reset();
  for (auto it = std::rbegin(rawHandlers); it != std::rend(rawHandlers); ++it)
  {
    if(last) (*it)->setNext(std::move(last));
    last.reset(*it);
  }
  first= std::move(last);
}
Munch Executor::handle(Iterator current, const Iterator& end){
  assert(first != nullptr);
  return first->handle(current, end);
}

Munch Whitespace::handle(Iterator current, const Iterator& end){
  if(current == end) return std::nullopt;
  if(char c = *current; isWhitespace(c)){
    //std::advance(current, 1);
    return std::string(1, ' ');
  }
  else if(next) return next->handle(current, end);
  return std::nullopt;
}
bool Whitespace::isWhitespace(const char& c){
  return std::isspace(static_cast<unsigned char>(c)) || c == '\n';
}


Munch Comment::handle(Iterator current, const Iterator& end){
 //std::cout << "Comment handling current= " << *current << '\n';
  if(current == end) return std::nullopt;
  if(Input firstTwo = Input(current, current+2); isComment(firstTwo)){
    auto comment= std::string(current, std::find(current, end,'\n'));
    //std::advance(current, comment.size());
    return comment;
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Comment::isComment(const Input& firstTwo){
  return firstTwo == "//";
}


Munch Number::handle(Iterator current, const Iterator& end){
 //std::cout << "Number handling current= " << *current << '\n';
  if(current == end) return std::nullopt;
  //std::cout << "Number muncher:";
  auto isNegative = (*current == '-');
  auto start = current + (isNegative ? 1 : 0);
  auto working = start;
  Input number, peeked;
  while(working != end){
    peeked.append(1,*working);
    //std::cout << peeked << '\n';
    if(isNumber(peeked)){
      number = peeked;
      //std::cout << "(now:"<< number << ")";
      std::advance(working, 1);
    } else if(auto p2 = peeked + std::string(1,*(working+1)); isNumber(p2)){
      //std::cout << "not digit but a "<< *(working+1) <<", peek more:" << Input(start, working+1) << '\n';
      std::advance(working, 1);
    }else break;
  }
  if(number.size() > 0){
    if(isNegative) number = "-" + number;
    //std::advance(current, number.size());
    return number;
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Number::isNumber(const Input& possibleNumber){
  if(possibleNumber.back() == '.') return false;
  float f;
  std::stringstream iss(possibleNumber);
  iss >> f;
  return iss.eof() && !iss.fail();
}


Munch Operator::handle(Iterator current, const Iterator& end){
 //std::cout << "Operator handling current= " << *current << '\n';
  if(current == end) return std::nullopt;
  if(isOperator(*current)){
    auto peeked = std::string(current,current+2);
    if(peeked.front() == '-' && isdigit(peeked.back())) return next->handle(current,end);
    if(isOperator(peeked)){
      return peeked;
      }
    return std::string(1, *(current));
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool Operator::isOperator(const char& c){
  std::string singleCharacterOperators = "!=><.*;:,()[]{}/+-";
  auto r = std::count(singleCharacterOperators.begin(), singleCharacterOperators.end(), c) > 0;
  return r;
}
bool Operator::isOperator(const Input& op){
  std::vector<std::string> twoCharactersOperators = {"!=", "==", ">=", "<=", "->"};
  auto r = std::find(twoCharactersOperators.begin(), twoCharactersOperators.end(), op ) != twoCharactersOperators.end();
  return r;
}


Munch String::handle(Iterator current, const Iterator& end){
 //std::cout << "String handling current= " << *current << '\n';
 //std::cout << "String now\n";//: " << identifier << "\n";
  if(current == end) return std::nullopt;
  if(isString(*current)){
   //std::cout << "IS A String!!!\n";//: " << identifier << "\n";
    auto stringEnd = std::string(current+1,end).find("\"");
   //std::cout << "String position end: "<< stringEnd << '\n'; //: " << identifier << "\n";
    if(stringEnd != std::string::npos){
      auto r= std::string(current,current+2+stringEnd);
     //std::cout << "String whole: "<< r << '\n'; //std::distance(current, stringEnd); //: " << identifier << "\n";
      //std::advance(current, r.size());
      return r;
    }
  }
  else if (next) return next->handle(current, end);
  return std::nullopt;
}
bool String::isString(const char& c){
 //std::cout << "isString: "<<c<<"\n";//: " << identifier << "\n";
  return c == '\"';
}


Munch Identifier::handle(Iterator current, const Iterator& end){
 //std::cout << "Identifier handling current= " << *current << '\n';
  if(current == end) return std::nullopt;
  if(isIdentifier(*current)){
    auto identifier= std::string(1, *current);
    std::advance(current,1);
    while(current != end){
     //std::cout << "identifier now: " << identifier << "\n";
      if(std::isalnum(static_cast<unsigned char>(*current))){
        identifier.append(1,*current);
        std::advance(current,1);
      }else{
        break;//return identifier;
      }
    }
    std::cout << "Identifier recognized as: " << identifier << '\n';
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

