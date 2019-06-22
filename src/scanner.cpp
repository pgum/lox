#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input cmd){
  Tokens tokens;
  Errors errors;
  std::cout << "Scan command: " << cmd << '\n';
  begin = cmd.begin();
  end = cmd.end();
  curr = cmd.begin();
  while(curr != end){
    context = std::string(curr,curr+1);
    std::cout << "Scan command: while curr != end: " << " context= " << context << '\n';
    auto munch = isComment();
    if(munch){
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isNumber();
    if(munch){
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isOperator();
    if(munch){
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    /*
    munch = isString();
    if(munch){
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }
    munch = isIdentifier();
    if(munch){
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }
    */
    errors.emplace_back(30, std::distance(begin, curr), "Unknown character", context);
    curr++;
  }
  tokens.emplace_back("\0");
  std::cout << "Scan command: " << cmd << "DONE\n";
  return {tokens, errors};
}

Munch Scanner::isOperator(){
  std::cout << "check if \"" << context << "\" is a operator: ";
  std::string expected = "!=><.*;:,()[]{}/";
  if(expected.find(context) == std::string::npos){
    std::cout << "No, because contex is not in ops: " << expected << std::endl;
    return std::nullopt;
  }
  auto peeked = std::string(curr,curr+2);
  std::vector<std::string> expectedPeek = {"!=", "==", ">=", "<=", "->"};
  std::cout << "peeked: " << peeked;
  if(std::find(expectedPeek.begin(), expectedPeek.end(),peeked) != expectedPeek.end()){
    std::cout << "Yes, from peeked: " << peeked << std::endl;
    return peeked;
  }else{
    std::cout << "Yes, from context: " << context << std::endl;
    return context;
  }
}

Munch Scanner::isNumber(){
  std::cout << "[IsNumber] check if \"" << context << "\" is a number: ";
  std::string expected = "-0123456789";
  if(expected.find(context) == std::string::npos){
    std::cout << "No, because contex is not in expected: " << expected << std::endl;
    return std::nullopt;
  }

  auto taken = std::string(curr, end);
  auto peeked = std::string();
  auto numberFirstPart = std::string();
  auto numberSecondPart = std::string();

  auto dot = peeked.find(".");
  if( dot != std::string::npos){
    auto numberFirstPart = taken.substr(0,dot);
  }
  auto p1 = peeked.substr(0, peeked.find("."));
  peeked = peeked.substr(0, peeked.find_first_not_of("0123456789"));
  auto number = p1 + "." + peeked;
  return Munch(number);
}

Munch Scanner::isComment(){
  peeked =  std::string(curr, curr+2);
  std::cout << "Check if \"" << context << "\" is a comment (peeked:"<<peeked<<"): ";
  if(context == "//"){
    auto peeked = std::string(curr, end);
    auto endl = peeked.find("\n");
    std::cout << "Yes\n";
    return Munch(std::string(begin,begin+endl));
  }
  std::cout<< "No\n";
  return std::nullopt;
}

Munch Scanner::isString(){
  std::cout << "Check if \"" << context << "\" is a string: \n";
  return std::nullopt;
}

Munch Scanner::isIdentifier(){
  std::cout << "Check if \"" << context << "\" is a identifier: \n" ;
  return std::nullopt;
}

}
