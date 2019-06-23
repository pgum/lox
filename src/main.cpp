#include <sysexits.h>
#include <iostream>
#include <string>
#include "lox.hpp"
void printHeader(std::string content){
  std::cout<< "--= CLox++ " << content << " =--" << std::endl;
  }
int main(int argc, char *argv[]){
  Lox::Lox lox;
  if(argc > 2){
    printHeader("Usage: " + std::string(argv[0]) + " [script]");
    return EX_USAGE;
  }else if(argc == 2){
    std::string filename(argv[1]);
    printHeader("Running file: " + filename);
    lox.runFile(filename);
  }else {
    printHeader("REPL (Ctrl+@ input)");
    lox.runPrompt();
  }
return EX_OK;
}
