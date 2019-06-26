#include "error.hpp"
namespace Lox {

std::string Error(const uint32_t& _line, const uint32_t& _col, const std::string& _culprit, const std::string& _msg){
 return std::string("#")+ std::to_string(_line)+ std::string(":")+ std::to_string(_col)+ std::string(":")+
        std::string(_culprit)+ std::string(": ")+ std::string(_msg);
}

}

