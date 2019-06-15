#include "token.hpp"

namespace Lox {
std::ostream & operator << (std::ostream &out, const Token &t){
    return out << "Token: " << t.lexem;
}

}
