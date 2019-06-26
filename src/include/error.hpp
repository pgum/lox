#pragma once
#include <iostream>
#include <string>

namespace Lox {
std::string Error(const uint32_t& _line, const uint32_t& _col, const std::string& _culprit, const std::string& _msg);
}

