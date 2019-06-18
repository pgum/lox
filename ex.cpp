//g++ -o ex ex.cpp -Wall -Wextra -Werror -std=c++2a && ./ex
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <tuple>
using Token= int;
using Error= std::string;
using Tokens= std::vector<Token>;
using Errors= std::vector<Error>;
//using ScannerOutput= std::tuple<Tokens,Errors>;
struct ScannerOutput {
  Tokens tokens;
  Errors errors;
  friend std::ostream & operator << (std::ostream &out, const ScannerOutput &s){
    out << "### S\n";
    out << s.tokens.size() << " Tokens: ";
    for(auto const& t: s.tokens) out << t << " ";
    out << '\n' << s.errors.size() << " Errors: ";
    for(auto const& e: s.errors) out << e << " ";
    return out << std::endl;
  }
};

class Scanner{
  public:
  Scanner() {}

  ScannerOutput scan(std::string command){
    if(command == "") return {{42},{"meaning?"}};
    std::string rawsource, source;
    Tokens tokens;
    Errors errors;
    rawsource = command;
    source= rawsource;

    for(Tokens tt = Tokens(10); const auto& t: tt){ tokens.emplace_back(t);}

    for(const auto& e: {std::string("radio"),std::string("rmf"),std::string("fm")}){errors.emplace_back(e);}
    return {tokens, errors};
  }
};


int main(){
  Scanner s;
  std::cout << s.scan("");
  auto so=s.scan(".");
  std::cout << so;
  auto s2= s.scan("][");
  std::cout << s2;
}
