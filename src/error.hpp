#pragma once
#include <iostream>
#include <string>

namespace Lox {
/*enum class MsgType { Error, Warning, Debug, Info, Note };

template<MsgType E>
class Message {
  public:
  MsgType type = E;
  virtual std::string report() const{ return std::string("Hello!"); }
};
*/
struct Error{
  Error(const uint32_t& _line,
        const uint32_t& _col,
        const std::string& _msg,
        const std::string& _culprit):
    line(_line), col(_col), msg(_msg), culprit(_culprit){}
  uint32_t line, col;
  std::string msg;
  std::string culprit;
  std::string report() const{
   return std::string("#") + std::to_string(line) +
          std::string(":") + std::to_string(col) +
          std::string(":") + culprit +
          std::string(": ") + msg;
  }
  friend std::ostream & operator << (std::ostream &out, const Error &t){return out << t.report() << std::endl; };
};
}

