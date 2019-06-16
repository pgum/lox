#include "token.hpp"

namespace Lox {
using TokenMap = std::map<std::string, TokenType>;

TokenType Token::Lexem2TokenType(std::string lexem){
  auto s = tokenTypes.find(lexem);
  return s != tokenTypes.end() ? s->second : TokenType::INVALID;
}
const TokenMap Token::tokenTypes = {
  {"(", TokenType::LEFT_PAREN   },
  {")", TokenType::RIGHT_PAREN  },
  {"{", TokenType::LEFT_BRACE   },
  {"}", TokenType::RIGHT_BRACE  },
  {"[", TokenType::LEFT_BRACKET },
  {"]", TokenType::RIGHT_BRACKET},
  {",", TokenType::COMMA        },
  {".", TokenType::DOT          },
  {";", TokenType::SEMICOLON    },
  {"*", TokenType::STAR         },
  {"!", TokenType::BANG         },
  {"!=", TokenType::BANG_EQUAL  },
  {"=", TokenType::EQUAL        },
  {"==", TokenType::EQUAL_EQUAL },
  {">", TokenType::GREATER      },
  {">=", TokenType::GREATER_EQUAL},
  {"<", TokenType::LESS         },
  {"<=", TokenType::LESS_EQUAL  }
  };

std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "Token: " << t.lexem;
}

}
