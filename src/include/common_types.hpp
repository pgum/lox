#pragma once
#include <iterator>
#include <optional>
#include <string>
#include <vector>

namespace Lox {
using Lexem= std::string;
using Lexems= std::vector<Lexem>;
using Errors= std::vector<std::string>;
using Input= std::string;
using Iterator = Input::const_iterator;
using Munch= std::optional<std::string>;
using SyntaxTree= std::string;

}
