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

class Message {
};
*/
struct Error{
  Error(const uint32_t& _line,
        const uint32_t& _col,
        const std::string& _culprit,
        const std::string& _msg) : error( std::string("#") + std::to_string(_line) +
                                          std::string(":") + std::to_string(_col) +
                                          std::string(":") + _culprit +
                                          std::string(": ") + _msg){}
  const std::string error;
  friend std::ostream & operator << (std::ostream &out, const Error &e){ return out << e.error; };
};
}

