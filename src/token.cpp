#include "token.hpp"
#include<iostream>
#include<string>
namespace Lox {
using namespace std;
ostream & operator << (ostream &out, const Token &t){
    out << t.source;
    return out;
  }
}
