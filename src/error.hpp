#pragma once
#include <iostream>
#include <string>

namespace Lox {
enum class MsgType { Error, Warning, Debug, Info, Note };

template<MsgType E>
class Message {
  MsgType type = E;
  virtual std::string report() const{ return std::string("Hello!");
    }
};

struct Error{
  Error(const uint32_t& _line, const uint32_t& _col, const std::string& _culprit, const std::string& _msg):
    line(_line), col(_col), culprit(_culprit), msg(_msg){}
  uint32_t line, col;
  std::string culprit;
  std::string msg;
  std::string report() const{
   return std::string("#") + std::to_string(line) +
          std::string(":") + std::to_string(col) +
          std::string(":") + culprit;
          std::string(": ") + msg;
  }
};
}

