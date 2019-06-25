//g++ -o ex ex.cpp -Wall -Wextra -Werror -std=c++2a && ./ex
//#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <optional>
#include <sstream>
#include <algorithm>
#include <memory>
#include <utility>
#include <initializer_list>

//src/include/scanner.hpp
using Lexem= std::string;
using Lexems= std::vector<Lexem>;
using Error= std::string;
using Errors= std::vector<Error>;
using Input= std::string;
using Munch= std::optional<std::string>;

using InputCit = Input::const_iterator;

struct ScannerOutput {
  const Lexems lexems;
  const Errors errors;

  bool hasErrors() const {return errors.size() != 0; }
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &so){
    out << "ScannerOutput: " << so.lexems.size() << " lexems: ";
    for(auto const& t: so.lexems) out << t << " ";
    out << "\nand " << so.errors.size() << " Errors:\n ";
    for(auto const& e: so.errors) out << e << " ";
    return out << '\n';
  }
};

struct HandlerBase {
  HandlerBase(){}
  virtual Munch handle(const InputCit curr, const InputCit end) const;
  std::vector<std::unique_ptr<HandlerBase>> handlers;
};

struct HandlerWhitespace: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

struct HandlerComment: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

struct HandlerNumber: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

struct HandlerOperator: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

struct HandlerString: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

struct HandlerIdentifier: HandlerBase {
  Munch handle(const InputCit curr, const InputCit end) const override;
};

Munch HandlerBase::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerBase\n";
  for(const auto& h: handlers) if(const auto& munch= h->handle(curr, end); munch ) return munch;
  return std::nullopt;
}

Munch HandlerWhitespace::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerWhitespace\n";
  if(curr != end && (*curr == ' ' || *curr == '\t' || *curr == '\n')) return Input(std::string(curr, curr+1));
  return std::nullopt;
}

Munch HandlerComment::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerComment\n";
  auto peeked =  std::string(curr, curr+2);
  if(peeked == "//") return std::string(curr, std::find(curr,end,'\n'));
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
  iss >> std::noskipws >> f; // noskipws considers leading whitespace invalid
  return iss.eof() && !iss.fail();
}

Munch HandlerNumber::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerNumber\n";
  auto isNegative = (*curr == '-');
  const InputCit start = curr + (isNegative ? 1 : 0);
  InputCit working = start;
  Input number, peeked;
  while(working != end){
    peeked += std::string(working, working+1);
    if(isFloat(peeked)){
      number = peeked;
      std::advance(working, 1);
    }else if(working+1 < end && isFloat(Input(start, working+1))){
      std::advance(working, 1);
    }else break;
  }
  if(isNegative) number = "-" + number;
  return number;
}

Munch HandlerOperator::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerOperator\n";
  if(!(std::string(curr, curr+1).find_first_not_of("!=><.*;:,()[]{}/+-") == std::string::npos)) return std::nullopt;
  auto peeked = std::string(curr,curr+2);
  if(curr+1 == end) return std::string(curr, curr+1);
  if(peeked == "//") return std::nullopt;
  std::vector<std::string> expectedPeek = {"!=", "==", ">=", "<=", "->"};
  if(std::find(expectedPeek.begin(), expectedPeek.end(), peeked) != expectedPeek.end()) return peeked;
  return std::nullopt;
}

Munch HandlerString::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerString\n";
  if(*curr != '\"') return std::nullopt;
  auto stringEnd = std::string(curr+1,end).find('\"');
  if(stringEnd != std::string::npos) return Munch(std::string(curr,curr+2+stringEnd));
  return std::nullopt;
}

Munch HandlerIdentifier::handle(const InputCit curr, const InputCit end) const {
  std::cout << "HandlerIdentifier\n";
  size_t peekSize = 1;
  auto peeked = std::string(curr, curr+1);
  auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
  std::string expected = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if(peeked.find_first_not_of(expected+"_") == std::string::npos){
    peekedChar = std::string(curr+peekSize, curr+peekSize+1);
    while(peekedChar.find_first_not_of(expected+"0123456789") == std::string::npos && curr+peekSize != end){
      peekedChar = std::string(curr+peekSize, curr+peekSize+1);
      peekSize++;
      peeked += peekedChar;
    }
    if(peekedChar.find_first_not_of(expected+"0123456789") != std::string::npos) return Munch(std::string(peeked.begin(), peeked.end()-1));
  }
  return std::nullopt;
}

ScannerOutput scan(const Input& input){
  Lexems lexems;
  Errors errors;
  HandlerBase munchInput;
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerWhitespace()));
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerComment()));
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerNumber()));
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerOperator()));
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerString()));
  munchInput.handlers.emplace_back(std::make_unique<HandlerBase>(HandlerIdentifier()));

  const Input::const_iterator end = input.cend();
  Input::const_iterator curr = input.begin();
  Munch munch;
  while(curr != end){
    munch = munchInput.handle(curr, end);
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }else{
      std::string e= "0:" + std::to_string(std::distance(input.begin(), curr)) + " Unknown character: " + std::string(curr,curr+1) + "\n";
      errors.emplace_back(e);
      std::advance(curr, 1);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}
int main(){
  std::string cmd = "123 45.6 Hello! //my friend\nLong example()...\n\"Is this a string?\" -> yup";
  std::cout << scan(cmd);;
}

