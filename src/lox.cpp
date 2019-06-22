#include "lox.hpp"
namespace Lox {
using Tokens= std::vector<Token>;

std::string Lox::run(std::string source){
  hadError=false;
  Errors errors;
  std::cout << "Run: " << source << std::endl;
  Scanner scanner;
  auto sout = Scanner().scan(source);
  if(sout.hasErrors()) errors.insert(errors.end(), sout.errors.begin(), sout.errors.end());

  Tokens tokens;
  for(const auto& l : sout.lexems) tokens.emplace_back(l);
  std::stringstream ss;
  ss << "After scanner:\n" << sout << "\n-----\n";
  return ss.str();
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
