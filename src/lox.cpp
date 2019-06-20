#include "lox.hpp"
namespace Lox {

std::string Lox::run(std::string source){
  hadError=false;
  Errors errors;
  std::cout << "Run: " << source << std::endl;
  Scanner scanner;
  auto sout = Scanner().scan(source);
  if(sout.hasErrors()) errors.insert(errors.end(), sout.errors.begin(), sout.errors.end());

  std::stringstream TokensDebugS;
  TokensDebugS << "After Scanner Tokens: " << std::to_string(sout.tokens.size()) << "Tokens:\n";
  for(const auto& t : sout.tokens){ TokensDebugS << t << " "; }
  
  std::stringstream ScannerErrorsS;
  ScannerErrorsS << "After Scanner Errors - " << std::to_string(sout.errors.size()) << " new errors:\n";
  for(const auto& e : sout.errors){ ScannerErrorsS << "  * " << e << '\n'; }

  return TokensDebugS.str()+"\n"+ScannerErrorsS.str();
}
void Lox::runFile(std::string filename){
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  run(content);
}

void Lox::runPrompt(){
  std::string in_prompt("> "), line;
  for(;;){
    std::cout << in_prompt;
    std::cin >> line;
    std::cout << run(line) << std::endl;
    for(const auto& e: errors){std::cout << e.report() << std::endl; }
  }
}

}
