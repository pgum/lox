#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include "error.hpp"
#include "token.hpp"
#include "scanner.hpp"
namespace Lox {
class Scanner;

class Lox {
  friend class Scanner;
  private:
  bool hadError;
  void error(const Error& error);
  void report(int line, std::string where, std::string message);
  public:
  std::string run(std::string source);
  void runFile(std::string filename);
  void runPrompt();
};
}
