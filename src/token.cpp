#include "token.hpp"

namespace Lox {
using TokenMap = std::map<Expr, Token::Type>;
const TokenMap Token::operatorTypes = {
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
  {"->",    Token::Type::ARROW  }
};
const TokenMap Token::keywordsTypes = {
  {"auto",  Token::Type::AUTO   },//more compatible with intended output
  {"and",   Token::Type::AND    },
  {"class", Token::Type::CLASS  },
  {"else",  Token::Type::ELSE   },
  {"false", Token::Type::FALSE  },
  {"fun",   Token::Type::FUN    },
  {"for",   Token::Type::FOR    },
  {"if",    Token::Type::IF     },
  {"nil",   Token::Type::NIL    },
  {"or",    Token::Type::OR     },
  {"print", Token::Type::PRINT  },//TODO:Remove print statement
  {"return",Token::Type::RETURN },
  {"super", Token::Type::SUPER  },
  {"this",  Token::Type::THIS   },
  {"true",  Token::Type::TRUE   },
  {"auto",  Token::Type::AUTO   },
  {"var",   Token::Type::VAR    },
  {"while", Token::Type::WHILE  }
};
const TokenMap Token::otherTypes= {
  {"[a-zA-Z_][a-zA-Z0-9]*",  Token::Type::IDENTIFIER },
  {"\\\"(.|(\r\n|\n))*\\\"",             Token::Type::STRING     },
  {"\\-?[0-9]+\\.?[0-9]*",   Token::Type::NUMBER     },
  {"//.*",    Token::Type::COMMENT },
  {"\0",    Token::Type::EOf }
};
Token::Type Token::Lexem2TokenType(Lexem lexem){
  for( const auto& tokenTypes: {operatorTypes, keywordsTypes, otherTypes}){
    for( const auto& tt: tokenTypes) if(std::regex_match(lexem, std::regex(tt.first))) return tt.second;
  }
  return Token::Type::INVALID;
}
std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "[" << (int)t.type << "| " << t.lexem << " ]";
}

}
