#pragma once
#include <string>

namespace Lox {

struct Error{
  Error(const uint32_t& _line, const uint32_t& _col, const std::string& _culprit, const std::string& _msg):
    line(_line), col(_col), culprit(_culprit), msg(_msg){}
  uint32_t line, col;
  std::string culprit;
  std::string msg;
};
}

