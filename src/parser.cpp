#include "parser.hpp"

namespace Lox{
ParserOutput Parser::parse(Tokens tokens){
  Errors errors;
  for(const auto& t: tokens) if(t == TokenInvalid()) errors.emplace_back(formatError(t));
  return {"{}", errors};
}
std::string Parser::formatError(const Token& culprit){
  std::stringstream ss;
  ss << "Parser error: " << culprit << '\n';
  return ss.str();
}
}//namespace Lox
