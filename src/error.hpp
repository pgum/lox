#pragma once
#include <iostream>
#include <string>

namespace Lox {
//using Reason=std::string;
/*enum class MsgType { Error, Warning, Debug, Info, Note };
class MessageType {};
class Error: MessageType {};
class Debug: MessageType {};
class Info: MessageType {};
class Note: MessageType {};

templace <typename MsgType
class Message

class Message {
  public:
  std::sgType ;
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

