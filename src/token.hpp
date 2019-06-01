#pragma once
#include<iostream>
#include<string>

namespace Lox{
using namespace std;
class Token {
  string source;
  public:
  explicit Token(string s) : source(s) {}
  friend ostream & operator << (ostream &out, const Token &t);
  };
}
