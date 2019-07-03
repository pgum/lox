#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "token.hpp"
#include "scanner.hpp"
#include "parser.hpp"

namespace Lox {

class Lox {
  public:
  std::vector<std::string> errors;
  std::string run(std::string source);
  void runFile(std::string filename);
  void runPrompt();
};

}
