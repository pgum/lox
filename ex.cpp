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
using ScannerOutput= std::tuple<Tokens,Errors,bool>;

class Scanner{
  public:
  Scanner(): isTokenized(false) {}

  ScannerOutput scan(std::string command){
    rawsource = command;
    source= rawsource;
    return someHardcoreScanning();
  }

  private:
  std::string rawsource, source;
  Tokens tokens;
  Errors errors;
  bool isTokenized;
  const static ScannerOutput EmptySourceOutput;
  ScannerOutput someHardcoreScanning(){
    Tokens tt = Tokens(10); for(const auto& t: tt){ tokens.emplace_back(t);}
    for(const auto& e: {std::string("radio"),std::string("rmf"),std::string("fm")}){errors.emplace_back(e);}
    isTokenized=true;
    return {tokens, errors, isTokenized};
  }
};

const ScannerOutput Scanner::EmptySourceOutput = ScannerOutput({42},{"meaning?"},false);

void describe(const ScannerOutput& s){
  std::cout << std::get<0>(s).size() << "Tokens: ";
  for(auto const& t: std::get<0>(s)) std::cout << t << " ";
  std::cout << std::endl;
  std::cout << std::get<1>(s).size() << "Errors: ";
  for(auto const& e: std::get<1>(s)) std::cout << e << " ";
  std::cout << std::endl << "isTokenized: " << std::get<2>(s) << std::endl;
}

int main(){
  Scanner s;
  std::cout << "### S" << std::endl;
  describe(s.scan(""));
  auto so=s.scan("");
  describe(so);
  auto s2= s.scan("][");
  describe(s2);
}
