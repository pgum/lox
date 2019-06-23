#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>
#include <string>
#include <numeric>
#include "error.hpp"
#include "token.hpp"
#include "scanner.hpp"

namespace Lox {
class Scanner;

class Lox {
  public:
  std::vector<Error> errors;
  std::string run(std::string source);
  void runFile(std::string filename);
  void runPrompt();

  private:
  bool hadError;
};
}
