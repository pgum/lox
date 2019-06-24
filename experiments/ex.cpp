//g++ -o ex ex.cpp -Wall -Wextra -Werror -std=c++2a && ./ex
#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <algorithm>

//src/include/scanner.hpp
using Lexem= std::string;
using Lexems= std::vector<Lexem>;
using Errors= std::vector<Error>;
using Input= std::string;
using Munch= std::optional<std::string>;

struct ScannerOutput {
  const Lexems lexems;
  const Errors errors;

  bool hasErrors() const {return errors.size() != 0; }
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.lexems.size() << " lexems: ";
    for(auto const& t: so.lexems) out << t << " ";
    out << "\nand " << so.errors.size() << " Errors: ";
    for(auto const& e: so.errors) out << e << " ";
    return out << '\n';
  }
};

class HandlerBase {
  const std::vector<HandlerBase> handers;
  HandlerBase(HandlerBase... _handlers): handlers(_handlers){}
  virtual Munch handle(const Input::iterator& curr, const Input::iterator& end);
};

class HandlerWhitespace: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};

class HandlerComment: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};



Munch handle::HandlerBase(const Input::iterator& curr, const Input::iterator& end){
  for(const auto& h: handlers) if(const auto munch= h.handle(curr, end); m ) return munch;
  return std::nullopt;
}

Munch HandlerWhitespace::handle(const Input::iterator& curr, const Input::iterator& end){
  if(curr* == ' ' || curr* == '\t' || curr* == '\n') return Munch(curr*);
  return std::nullopt;
}

Munch HandlerComment::handle(const Input::iterator& curr, const Input::iterator& end){
  auto peeked =  std::string(curr, curr+2);
  if(peeked == "//"){
    peeked = std::string(curr, std::find(curr,end,'\n'));
    return Munch(peeked);
  }
  return std::nullopt;
}


bool isDigit(const std::string& p){
  return (p.find_first_not_of("0123456789") == std::string::npos);
}

bool isDot(const std::string& p){
  return (p.find_first_not_of(".") == std::string::npos);
}

bool isFloat(const std::string& str ) {
  std::istringstream iss(str);
  float f;
  iss >> noskipws >> f; // noskipws considers leading whitespace invalid
  return iss.eof() && !iss.fail();
}

class HandlerNumber: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};

Munch HandlerNumber::handle(const Input::iterator& curr, const Input::iterator& end){
  auto isNegative = (curr* == '-');
  const Input::iterator start = curr + (isNegative ? 1 : 0);
  Input::iterator working = start;
  Input number, peeked;
  while(working != end){
    peeked += std::string(working*);
    if(isFloat(peeked)){
      number = peeked;
      std::advance(woring);
    }else if(working+1 < end && isFloat(Input(start, working+1)){
      std::advance;
    }else break;
  }
  if(isNegative) number = "-" + number;
  return Munch(number);
  return std::nullopt;
}


ScannerOutput scan(const Input& input){
  Lexems lexems;
  Errors errors;
  auto MunchInput = HandlerBase(HandlerWhitespace, HandlerComment, HandlerNumber);
  const Input::iterator end = input.end();
  Input::iterator curr = input.begin();
  Munch munch;
  while(curr != end){
    munch = MunchInput.handle(curr, end);
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }else{
      errors.emplace_back(0, std::distance(input.begin(), curr), "Unknown character", curr*);
      std::advance(curr);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}
int main(){
  std::cout << scan("123 45.6 Hello! //my friend\nLong example()...\n\"Is this a string?\" -> yup");
  
}
