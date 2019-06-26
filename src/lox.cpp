#include "lox.hpp"

namespace Lox {
using Tokens= std::vector<Token>;

std::string Lox::run(std::string source){
  Errors errors;
  auto sout = Scanner().scan(source);
  errors.insert(errors.end(), sout.errors.begin(), sout.errors.end());

  Tokens tokens;
  for(const auto& l : sout.lexems){ tokens.emplace_back(l); std::cout << l << ' ';}
  for(const auto& e: errors) std::cout << e << '\n';
  return "";
}
void Lox::runFile(std::string filename){
  std::ifstream file(filename);
  std::string content((std::istreambuf_iterator<char>(file)),
                      std::istreambuf_iterator<char>());
  run(content);
}

void Lox::runPrompt(){
  std::string command;
  for(;;){
    std::cout << "> ";
    std::getline(std::cin, command, '\0');
    std::cout << run(command) << std::endl;
  }
}

}
