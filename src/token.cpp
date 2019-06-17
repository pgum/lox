#include "token.hpp"

namespace Lox {
using TokenMap = std::map<std::string, Token::Type>;
bool Token::checkStringIsNumber(std::string s){
  //Eliminate obvious irritants that could spoil the party
  //Handle special cases here, e.g. return true for "+", "-", "" if they are acceptable as numbers to you
  if (s == "" || s == "." || s == "+" || s == "-" || s == "+." || s == "-.") return false;

  //Remove leading / trailing spaces **IF** they are acceptable to you
  //while (s.size() > 0 && s[0] == ' ') s = s.substr(1, s.size() - 1);
  //while (s.size() > 0 && s[s.size() - 1] == ' ') s = s.substr(0, s.size() - 1);


  //Remove any leading + or - sign
  //if (s[0] == '+' || s[0] == '-')
  //    s = s.substr(1, s.size() - 1);

  //Remove decimal points
  auto prevLength = s.size();

  size_t start_pos = 0;
  while((start_pos = s.find(".", start_pos)) != std::string::npos)
    s.replace(start_pos, 1, "");

  //If the string had more than 2 decimal points, return false.
  if (prevLength > s.size() + 1) return false;

  //Check that you are left with numbers only!!
  //Courtesy selected answer by Charles Salvia above
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}

Token::Type Token::Lexem2TokenType(std::string lexem){
  std::cout<< "Lexem2TokenType for lexem: "<< lexem << std::endl;
  auto s = tokenTypes.find(lexem);
  //1 and 2 - size tokens;
  if(s != tokenTypes.end()) return s->second;
  //NUMBERS

  if(checkStringIsNumber(lexem)){
    std::cout <<"***" <<lexem << " is NUMBER" << std::endl;
    return Token::Type::NUMBER;
  }
  if(lexem.find_first_of("-") != std::string::npos){
    auto smallLexem = lexem.substr(1,lexem.size()-1);
    std::cout <<"***" <<lexem << " *** (cut to:"<< smallLexem << ") maybe is NEGATIVE NUMBER" << std::endl;
    if(checkStringIsNumber(smallLexem)){
      std::cout <<"***" <<lexem << " is NUMBER" << std::endl;
      return Token::Type::NUMBER;
      }
  }
  //COMMENTS
  if(lexem.substr(0,2) == "//"){  return Token::Type::COMMENT;}
  return Token::Type::INVALID;
}
const TokenMap Token::tokenTypes = {
  {"(", Token::Type::LEFT_PAREN   },
  {")", Token::Type::RIGHT_PAREN  },
  {"{", Token::Type::LEFT_BRACE   },
  {"}", Token::Type::RIGHT_BRACE  },
  {"[", Token::Type::LEFT_BRACKET },
  {"]", Token::Type::RIGHT_BRACKET},
  {",", Token::Type::COMMA        },
  {".", Token::Type::DOT          },
  {";", Token::Type::SEMICOLON    },
  {"/", Token::Type::SLASH        },
  {"*", Token::Type::STAR         },

  {"!", Token::Type::BANG         },
  {"!=", Token::Type::BANG_EQUAL  },
  {"=", Token::Type::EQUAL        },
  {"==", Token::Type::EQUAL_EQUAL },
  {">", Token::Type::GREATER      },
  {">=", Token::Type::GREATER_EQUAL},
  {"<", Token::Type::LESS         },
  {"<=", Token::Type::LESS_EQUAL  }
  };

std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "[" << (int)t.type << "| " << t.lexem << "]";
}

}
