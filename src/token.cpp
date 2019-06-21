#include "token.hpp"

namespace Lox {
using Lexem = std::string;
using TokenMap = std::map<Expr, Token::Type>;
const TokenMap Token::tokenTypes = {
  {"\\(",   Token::Type::LEFT_PAREN    },
  {"\\)",   Token::Type::RIGHT_PAREN   },
  {"\\{",   Token::Type::LEFT_BRACE    },
  {"\\}",   Token::Type::RIGHT_BRACE   },
  {"\\[",   Token::Type::LEFT_BRACKET  },
  {"]",     Token::Type::RIGHT_BRACKET },
  {",",     Token::Type::COMMA         },
  {"\\.",   Token::Type::DOT           },
  {"-",     Token::Type::MINUS         },
  {"\\+",   Token::Type::PLUS          },
  {":",     Token::Type::COLON         },
  {";",     Token::Type::SEMICOLON     },
  {"/",     Token::Type::SLASH         },
  {"!",     Token::Type::BANG          },
  {"\\*",   Token::Type::STAR          },
  {"=",     Token::Type::EQUAL         },
  {">",     Token::Type::GREATER       },
  {"<",     Token::Type::LESS          },
  {"!=",    Token::Type::BANG_EQUAL    },
  {"==",    Token::Type::EQUAL_EQUAL   },
  {">=",    Token::Type::GREATER_EQUAL },
  {"<=",    Token::Type::LESS_EQUAL    },
  {"->",    Token::Type::ARROW  },
  {"if",    Token::Type::IF     },
  {"and",   Token::Type::AND    },
  {"class", Token::Type::CLASS  },
  {"else",  Token::Type::ELSE   },
  {"false", Token::Type::FALSE  },
  {"fun",   Token::Type::FUN    },
  {"for",   Token::Type::FOR    },
  {"nil",   Token::Type::NIL    },
  {"or",    Token::Type::OR     },
  {"print", Token::Type::PRINT  },//TODO:Remove print statement
  {"return",Token::Type::RETURN },
  {"super", Token::Type::SUPER  },
  {"this",  Token::Type::THIS   },
  {"true",  Token::Type::TRUE   },
  {"auto",  Token::Type::AUTO   },//more compatible with intended output
  {"var",   Token::Type::VAR    },
  {"while", Token::Type::WHILE  },
  {"[a-zA-Z_][a-zA-Z0-9]*",  Token::Type::IDENTIFIER },
  {"\\\".*\\\"",             Token::Type::STRING     },
  {"\\-?[0-9]+\\.?[0-9]*",   Token::Type::NUMBER     },
  {"//.*\\n",    Token::Type::COMMENT}
  //{"/\*.*\*/",   Token::Type::COMMENT}, debating if should allow block comments, or discourage at all comments
  //{"\\n",        Token::Type::ENDL}
};
Token::Type Token::Lexem2TokenType(Lexem lexem){
  for( const auto& tt : tokenTypes){
    std::string lex = lexem;
    if(tt.first.size() == lexem.size() && std::regex_match(lex, std::regex(tt.first))){
      std::cout << "Lexem: " << lexem << "  Regex:" << tt.first << " Recognized:" << std::endl;
     return tt.second;
    }
  }
  return Token::Type::INVALID;
}

std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "[" << (int)t.type << "| " << t.lexem << " ]";
}

}
