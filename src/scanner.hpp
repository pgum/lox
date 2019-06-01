#pragma once
#include<string>
#include<vector>
namespace Lox {
class Scanner {
    public:
    std::vector<Token> scanSource(std::string source);
  };
}
