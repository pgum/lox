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
  Scanner(const std::string& _source): source(_source){scan();}

  ScannerOutput scan()const{
    return (source != "") ? scan(source) : Scanner::EmptySourceOutput;
  }
  ScannerOutput scan(std::string command)const{
    std::string source;
    bool isTokenized;

    source = command;
    s= source;
    return someHardcoreScanning();
    //return std::make_tuple(tokens,errors,isTokenized);
  }

  private:
  const static ScannerOutput EmptySourceOutput;
  ScannerOutput someHardcoreScanning()const{
    std::string s;
    Tokens tokens;
    Errors errors;
    Tokens tt = Tokens(10); for(const auto& t: tt) tokens.emplace_back(t);
    for(const auto& e: {std::string("radio"),std::string("rmf"),std::string("fm")}) errors.emplace_back(e);
    isTokenized=true;
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
  Scanner s, s1("!");

  std::cout << "### S (default ctor)" << std::endl;
  describe(s.scan());

  std::cout << "### S1" << std::endl;
  describe(s1.scan());

  std::cout << "### S operator (\"\"))" << std::endl;
  auto so=s.scan("");
  describe(so);

  std::cout << "### S scan(\"[]\")" << std::endl;
  auto s2= s.scan("][");
  describe(s2);
}
