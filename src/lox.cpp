#include "lox.hpp"
namespace Lox {

std::string Lox::run(std::string source){
    Scanner scanner(source);
    if(!scanner.scan()){
      for(const auto& e: scanner.errorsEncountered){
        error(e);
      }
    }
    for(const Token& t: (std::vector<Token>)scanner){
        std::cout << t << ' ' << std::endl;
    }
    return source;
}

void Lox::error(const Error& error) {
  report(error.line, "", error.msg);
  hadError= true;
}

void Lox::report(int line, std::string where, std::string message){
 std::cout << "#" << line << ":" << where << ": " << message << std::endl;
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
  }
}

}
