#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input cmd){
  Lexems lexems;
  Errors errors;
  begin = cmd.begin();
  end = cmd.end();
  curr = cmd.begin();
  while(curr != end){
    context = std::string(curr,curr+1);
    if(context == " " || context == "\t"){
      std::advance(curr, 1);
      continue;
    }
    auto munch = isComment();
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isNumber();
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isOperator();
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }

    munch = isString();
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }
    munch = isIdentifier();
    if(munch){
      lexems.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
    }
    else{
      errors.emplace_back(0, std::distance(begin, curr), "Unknown character", context);
      curr++;
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}

Munch Scanner::isOperator(){
  std::string expected = "!=><.*;:,()[]{}/+-";
  if(expected.find(context) == std::string::npos){
    return std::nullopt;
  }
  peeked = std::string(curr,curr+2);
  std::vector<std::string> expectedPeek = {"!=", "==", ">=", "<=", "->"};
  if(peeked == "//"){
    return std::nullopt;
  }
  if(std::find(expectedPeek.begin(), expectedPeek.end(), peeked) != expectedPeek.end()){
    return peeked;
  }else{
    return context;
  }
}

Munch Scanner::isNumber(){
  bool hasMinus=false;
  if(context == "-"){
    size_t peekSize = 1;
    auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
    if(peekedChar.find_first_not_of("1234567890") != std::string::npos){
      return std::nullopt;
    }else{
      context = peekedChar;
      hasMinus=true;
    }
  }else if(context.find_first_not_of("1234567890") == std::string::npos){ //context is 0-9
  }else {
    return std::nullopt;
  }

  size_t peekSize = 1;
  auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
  std::string expected = "0123456789";
  if(expected.find(context) == std::string::npos){
    return std::nullopt;
  }
  bool hadDot = false;
  peekedChar = std::string(curr+peekSize, curr+peekSize+1);

  if(peekedChar.find_first_not_of("0123456789") != std::string::npos){
    if(peekedChar != "."){
      return context;
    }
  }
  peeked = context;
  while(peekedChar.find_first_not_of(".0123456789") == std::string::npos && curr+peekSize != end){
    if(hasMinus){ peekedChar = std::string(curr+peekSize+1, curr+peekSize+2); }
    else{ peekedChar = std::string(curr+peekSize, curr+peekSize+1); }
    if(peekedChar == "." && hadDot){
      if(hasMinus) peeked= "-"+peeked;
      return Munch(peeked);
    }else if(peekedChar == "." && !hadDot){
      hadDot = true;
      auto peekedChar2 = std::string(curr+1+peekSize, curr+1+peekSize+1);
      if(hasMinus){ peekedChar2 = std::string(curr+peekSize+2, curr+peekSize+3); }
      if(peekedChar2.find_first_not_of("0123456789") == std::string::npos){
        peeked += peekedChar;
      }else{
        if(hasMinus) peeked= "-"+peeked;
        return Munch(peeked);
        }
    }else if(peekedChar.find_first_of("0123456789") != std::string::npos){
      peeked += peekedChar;
    }
    peekSize++;
  }
  if(hasMinus) peeked= "-"+peeked;
  return Munch(peeked);
}

Munch Scanner::isComment(){
  peeked =  std::string(curr, curr+2);
  if(peeked == "//"){
    peeked = std::string(curr, end);
    return Munch(peeked);
  }
  return std::nullopt;
}

Munch Scanner::isString(){
  if(context == "\""){
    auto stringEnd = std::string(curr+1,end).find("\"");
    if(stringEnd+1 != std::string::npos){
      peeked = std::string(curr,curr+2+stringEnd);
      return Munch(peeked);
    }
  }
  return std::nullopt;
}

Munch Scanner::isIdentifier(){
  size_t peekSize = 1;
  peeked = context;
  auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
  std::string expected = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
  if(context.find_first_not_of(expected+"_") == std::string::npos){
    peekedChar = std::string(curr+peekSize, curr+peekSize+1);
    while(peekedChar.find_first_not_of(expected+"0123456789") == std::string::npos && curr+peekSize != end){
      peeked += peekedChar;
      peekSize++;
    }
    return Munch(peeked);
  }
  return std::nullopt;
}

}
