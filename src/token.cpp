#include<iostream>
#include<string>
#include "token.hpp"

namespace Lox {
using namespace std;
ostream & operator << (ostream &out, const Token &t){
    out << t.source;
    return out;
  }
}
