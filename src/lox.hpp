#pragma once
#include <iostream>
#include <string>
namespace Lox {
  class Lox {
    public:
    std::string run(std::string source);
    void runFile(std::string filename);
    void runPrompt();
  };
}
