#include <string>
#include <sstream>
#include <vector>
#include <iterator>
#include "token.hpp"
#include "scanner.hpp"
namespace Lox{
using namespace std;

vector<Token> Scanner::scanSource(string source){
  istringstream iss(source);
  vector<string> sources((istream_iterator<string>(iss)),
                   istream_iterator<string>());
  vector<Token> r;
  for(const string& s: sources){
      Token t(s);
      r.push_back(t);
    }
  return r;
  }
}
