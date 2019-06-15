#include "lox.hpp"
namespace Lox {

std::string Lox::run(std::string source){
  hadError=false;
  errors.clear();
  Scanner scanner(source);
  if(!scanner.scan()){
    for(const auto& e: scanner.errorsEncountered){
      errors.emplace_back(e);
      hadError= true;
    }
  }
  for(const Token& t: (std::vector<Token>)scanner){
      std::cout << t << ' ' << std::endl;
  }
  return source;
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
