#include "token.hpp"

namespace Lox {
using TokenMap = std::map<std::string, Token::Type>;

Token::Type Token::Lexem2TokenType(std::string lexem){
  auto s = tokenTypes.find(lexem);
  return s != tokenTypes.end() ? s->second : Token::Type::INVALID;
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
  {"<=", Token::Type::LESS_EQUAL  },

  {"//", Token::Type::COMMENT     }
  };

std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "Token: " << t.lexem;
}

}
