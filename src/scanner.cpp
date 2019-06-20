#include "scanner.hpp"

namespace Lox {

Munch Scanner::isOperator(Input::iterator curr){
  auto context =  std::string(curr, curr+1);
  std::cout << "check if \"" << context << "\" is a operator: ";
  std::string expected = "!=><.*;:,()[]{}/";
  if(expected.find(context) == std::string::npos){
    std::cout << "No, because contex is not in ops: " << expected << std::endl;
    return std::nullopt;
  }
  auto peeked = std::string(curr,curr+1+1);
  //std::cout << "peeked: " << peeked;
  if(expected.find(peeked) == std::string::npos){
    std::cout << "Yes, from context" << context << std::endl;
    return context;
  }else{
    std::cout << "Yes, from peeked: " << peeked << std::endl;
    return peeked;
  }
}

Munch Scanner::isNumber(Input in, Input::iterator curr){
  auto context =  std::string(curr, curr+1);
  std::cout << "[IsNumber] check if \"" << context << "\" is a number: ";
  std::string expected = "-0123456789";
  if(expected.find(context) == std::string::npos){
    std::cout << "No, because contex is not in expected: " << expected << std::endl;
    return std::nullopt;
  }

  auto taken = std::string(curr, in.end());
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

Munch Scanner::isComment(Input in, Input::iterator curr){
  auto context =  std::string(curr, curr+2);
  std::cout << "In: "<< in <<" check if \"" << context << "\" is a comment: ";
  if(context == "//"){
    auto peeked = std::string(curr, in.end());
    auto endl = peeked.find("\n");
    std::cout << "Yes" << std::endl;
    return Munch(in.substr(0,endl));
  }
  return std::nullopt;
}

Munch Scanner::isString(Input in, Input::iterator curr){
  auto context =  std::string(curr, curr+1);
  std::cout << "In: "<< in <<" check if \"" << context << "\" is a string: " << std::endl;
  return std::nullopt;
}

Munch Scanner::isIdentifier(Input in, Input::iterator curr){
  auto context =  std::string(curr, curr+1);
  std::cout << "In: "<< in <<" check if \"" << context << "\" is a identifier: " << std::endl;
  return std::nullopt;
}

ScannerOutput Scanner::scan(Input command){
  Tokens tokens;
  Errors errors;
  Input in= command;
  std::cout << "Command: " << command << '\n';
  auto curr = in.begin();
  while(curr != in.end()){
    //size_t peekSize=1;
    auto context = std::string(curr,curr+1);
    std::cout << "While: sC != in.end(): " << " context= " << context << '\n';
    for(auto const&munch : {isComment(in,curr), isNumber(in,curr), isOperator(curr), isString(in,curr), isIdentifier(in,curr)}){
      if(munch){
        tokens.emplace_back(munch.value());
        std::advance(curr, munch.value().size());
      }
    }
    errors.emplace_back(30, std::distance(in.begin(), curr), "Unknown character", context);
  }
  tokens.emplace_back(TokenEOF());
  return {tokens, errors};
}

}
