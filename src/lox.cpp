#include "lox.hpp"
#include <fstream>
namespace Lox {
using namespace std;

string Lox::run(string source){
  return string("Running following source: ") + source;
  }
void Lox::runFile(string filename){
  ifstream file(filename);
  string content((istreambuf_iterator<char>(file)),
                      istreambuf_iterator<char>());
  //cout << filename << endl << content << endl;
  run(content);
}
void Lox::runPrompt(){
  string in_prompt("> "), out_prompt("< "), line;
  for(;;){
    cout << in_prompt;
    cin >> line;
    cout << out_prompt << run(line) << endl;
  }
}

}
