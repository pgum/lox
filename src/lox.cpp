#include "lox.hpp"
namespace Lox {

std::string Lox::run(std::string source){
  hadError=false;
  Errors errors;
  std::cout << "Run: " << source;
  Scanner scanner;
  auto sout = Scanner().scan(source);
  if(sout.hasErrors()) errors.insert(errors.end(), sout.errors.begin(), sout.errors.end());

  std::string TokensDebug = 
/*  std::cout << "\nafter Scanner:\n  Tokens: " <<
            << [&]{ std::accumulate(std::next(sout.tokens.begin()), sout.tokens.end(), std::to_string(sout.tokens[0]),
                    [](std::string a, Token b) { return std::move(a) + ' ' + std::to_string(b); });
               }()
            << "\n  Errors after this phase: " << errors.size()
            << "\n  New errors:\n"
            << [&]{ std::accumulate(std::next(sout.errors.begin()), sout.errors.end(), std::to_string(sout.errors[0]),
                    [](std::string a, Error b) { return std::move(a) + "  * " + std::to_string(b) + '\n'; });
               }()
            << std::endl;
*/
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
