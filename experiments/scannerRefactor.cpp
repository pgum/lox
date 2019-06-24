//g++ -o ex ex.cpp -Wall -Wextra -Werror -std=c++2a && ./ex
#include <string_view>
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
#include <optional>
#include <algorithm>

//using Token= int;
//using Error= std::string;
//using Tokens= std::vector<Token>;
//using Errors= std::vector<Error>;
//using ScannerOutput= std::pair<Tokens,Errors>;
using Input= std::string;
using Munch= std::optional<std::string>;

class HandlerBase {
  const std::vector<HandlerBase> handers;
  HandlerBase(HandlerBase... _handlers): handlers(_handlers){}
  virtual Munch handle(const Input::iterator& curr, const Input::iterator& end);
};

class HandlerWhitespace: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};
Munch HandlerWhitespace::handle(const Input::iterator& curr, const Input::iterator& end){
  if(curr* == " " || curr* == "\t" || curr* == "\n") return curr*;
  return this->HandlerBase->handle(curr, end);
}

class HandlerComment: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};
Munch HandlerComment::handle(const Input::iterator& curr, const Input::iterator& end){
  auto peeked =  std::string(curr, curr+2);
  if(peeked == "//"){
    peeked = std::string(curr, std::find(curr,end,"\n"));
    return Munch(peeked);
  }
}

class HandlerNumber: HandlerBase {
  Munch handle(const Input::iterator& curr, const Input::iterator& end) override;
};
/*
struct ScannerOutput {
  const Tokens tokens;
  const Errors errors;
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &s){
    out << "ScannerOutput: " << s.tokens.size() << " Tokens: ";
    for(auto const& t: s.tokens) out << t << " ";
    out << " and " << s.errors.size() << " Errors: ";
    for(auto const& e: s.errors) out << e << " ";
    return out << std::endl;
  }
};

class Scanner{
  public:
  Scanner() {}

  ScannerOutput scan(std::string_view command){
    if(command == "") return {{42},{"meaning?"}};
    std::string rawsource, source;
    Tokens tokens;
    Errors errors;
    rawsource = command;
    source= rawsource;

    for(const auto& t: Tokens(10)){ tokens.emplace_back(t);}

    for(const auto& e: {std::string("radio"),std::string("rmf"),std::string("fm")}){errors.emplace_back(e);}
    return {tokens, errors};
  }
};
*/

int main(){
  Scanner s;
  std::cout << s.scan("");
  auto so=s.scan(".");
  std::cout << so;
  auto s2= s.scan("][");
  std::cout << s2;
}

