#include "token.hpp"

namespace Lox {
template<TokenType T>
std::ostream & operator << (std::ostream &out, const TToken<T> &t){
    return out << "TToken: " << t.lexem;
}

std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "Token: " << t.lexem;
}

}
