#include "scanner/include/scanner.hpp"
#include "parser/include/parser.hpp"
#include "parser/include/token.hpp"
#include "lox.hpp"

namespace Lox {
using Tokens= std::vector<Token>;

std::string Lox::run(std::string source){
  Errors errors;

  std::cout << "\n *** SCANNER ***\n";
  auto sout = Scanner().scan(source);
  errors.insert(errors.end(), sout.errors.begin(), sout.errors.end());
  Tokens tokens;
  for(const auto& l : sout.lexems) tokens.emplace_back(l);

  std::cout << "\n *** PARSER ***\n";
  auto pout = Parser().parse(tokens);
  errors.insert(errors.end(), pout.errors.begin(), pout.errors.end());
  std::cout << "SyntaxTree:\n" << pout.tree << '\n';

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
