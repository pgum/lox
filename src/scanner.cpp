#include "scanner.hpp"

namespace Lox {

ScannerOutput Scanner::scan(Input cmd){
  Tokens tokens;
  Errors errors;
  //std::cout << "Scan command: " << cmd << '\n';
  begin = cmd.begin();
  end = cmd.end();
  curr = cmd.begin();
  while(curr != end){
    context = std::string(curr,curr+1);
    //std::cout << "Scan command: while curr != end: " << " context= " << context << '\n';
    auto munch = isComment();
    if(munch){
      //std::cout << munch.value() << " is a comment\n";
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isNumber();
    if(munch){
      //std::cout << munch.value() << " is a number\n";
      tokens.emplace_back(munch.value());
      std::advance(curr, munch.value().size());
      continue;
    }
    munch = isOperator();
    if(munch){
      //std::cout << munch.value() << " is a operator\n";
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
    else{
      errors.emplace_back(0, std::distance(begin, curr), "Unknown character", context);
      curr++;
    }
  }
  tokens.emplace_back("\0");
  //std::cout << "Scan command: " << cmd << " DONE\nScanned Tokens: ";
  //for(const auto& t: tokens) std::cout << t << " ";
  //std::cout << std::endl;
  //std::cout << "Scan errors: ";
  //if(errors.size() >0) for(const auto& e: errors) std::cout << e << '\n';
  //std::cout << "----------------------------" << std::endl;
  return {tokens, errors};
}

Munch Scanner::isOperator(){
  //std::cout << "check if \"" << context << "\" is a operator: ";
  std::string expected = "!=><.*;:,()[]{}/+-";
  if(expected.find(context) == std::string::npos){
    //std::cout << "No, because contex is not in ops: " << expected << std::endl;
    return std::nullopt;
  }
  peeked = std::string(curr,curr+2);
  std::vector<std::string> expectedPeek = {"!=", "==", ">=", "<=", "->"};
  //std::cout << "peeked: " << peeked;
  if(peeked == "//"){
    //std::cout << "This is comment starter, not operator\n";
    return std::nullopt;
  }
  if(std::find(expectedPeek.begin(), expectedPeek.end(), peeked) != expectedPeek.end()){
    //std::cout << "Yes, from peeked: " << peeked << std::endl;
    return peeked;
  }else{
    //std::cout << "Yes, from context: " << context << std::endl;
    return context;
  }
}

Munch Scanner::isNumber(){
  //std::cout << "[IsNumber] Check if \"" << context << "\" is a number\n";
  //std::cout << "[IsNumber] Check if context is minus: ";
  bool hasMinus=false;
  if(context == "-"){ //start with minus
    //std::cout << "yes\n";
    //hasMinus=true;
    size_t peekSize = 1;
    auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
    if(peekedChar.find_first_not_of("1234567890") != std::string::npos){
      //std::cout << "[IsNumber] Context was MINUS but PeekedChar is not 0-9: " << peekedChar <<'\n';
      //std::cout << "[IsNumber] Not a number\n";
      return std::nullopt;
    }else{
      //std::cout << "[IsNumber] Context was MINUS and PeekedChar is 0-9: " << peekedChar <<'\n';
      //std::cout << "[IsNumber] Change Context was " << context << " into " << peekedChar <<'\n';
      context = peekedChar;
      hasMinus=true;
    }
  }else if(context.find_first_not_of("1234567890") == std::string::npos){ //context is 0-9
    //std::cout << "no. ";
    //std::cout << "Context is a digit: " << context << '\n';
  }else { //context is not - nor a digit -> not a number
    //std::cout << "no. ";
    //std::cout << "[IsNumber] Context ("<<context<<") is not a digit, nor minus. Not a number\n";
    return std::nullopt;
  }

  size_t peekSize = 1;
  auto peekedChar = std::string(curr+peekSize, curr+peekSize+1);
  std::string expected = "0123456789";
  if(expected.find(context) == std::string::npos){
    //std::cout << "No, because contex is not in expected: " << expected << std::endl;
    return std::nullopt;
  }
//  std::cout << "[IsNumber] Context fits " <<expected << '\n';
  bool hadDot = false;
  peekedChar = std::string(curr+peekSize, curr+peekSize+1);

  if(peekedChar.find_first_not_of("0123456789") != std::string::npos){
    //std::cout << "[IsNumber] " << context + peekedChar << " is not a number?\n";
    if(peekedChar != "."){
    //  std::cout << "PeekedChar is not dot ("<< peekedChar;
    //  std::cout << ") so its not part of number, but context ("<< context <<") was, so return context!\n";
      return context;
    }
    if(peekedChar =="."){
    //  std::cout << "PeekedChar is a dot, peek once more to see if next character is a number?\n";
      auto peekedChar2 = std::string(curr+1+peekSize, curr+1+peekSize+1);
      if(peekedChar2.find_first_not_of("1234567890") == std::string::npos){
    //    std::cout << "PeekedChar2 is a number: " <<peekedChar2 <<" so " << context + peekedChar + peekedChar2 << '\n';
        }
      }
  }
  peeked = context;
  while(peekedChar.find_first_not_of(".0123456789") == std::string::npos && curr+peekSize != end){
    if(hasMinus){ peekedChar = std::string(curr+peekSize+1, curr+peekSize+2); }
    else{ peekedChar = std::string(curr+peekSize, curr+peekSize+1); }
    //std::cout << "[IsNumber] PeekedChar: " << peekedChar << '\n';
    if(peekedChar == "." && hadDot){
      //std::cout << "PeekedChar: " << peekedChar << " is a dot, and there was one already, so its not part of number\n";
      //std::cout << "Final number: " << peeked << "\n";
      if(hasMinus) peeked= "-"+peeked;
      return Munch(peeked);
    }else if(peekedChar == "." && !hadDot){
      //std::cout << " is a dot, and there was no previous dot\n";
      hadDot = true;
      auto peekedChar2 = std::string(curr+1+peekSize, curr+1+peekSize+1);
      if(hasMinus){ peekedChar2 = std::string(curr+peekSize+2, curr+peekSize+3); }
      //std::cout << "Check if after a dot there is another digit: " << peekedChar2 << " ";
      if(peekedChar2.find_first_not_of("0123456789") == std::string::npos){
        //std::cout << "yes.\n";
        peeked += peekedChar;
        //std::cout << "[IsNumber] new number:" << peeked << "\n";
      }else{
        //std::cout << "no.\n";
        if(hasMinus) peeked= "-"+peeked;
        return Munch(peeked);
        }
    }else if(peekedChar.find_first_of("0123456789") != std::string::npos){
      //std::cout << "PeekedChar: " << peekedChar << " is 01233456789\n";
      //std::cout << "peeked before: " << peeked << " new peeked: ";
      peeked += peekedChar;
      //std::cout << peeked << '\n';
      //std::cout << "[IsNumber] new number:" << peeked << "\n";
    }
    peekSize++;
  }
  if(hasMinus) peeked= "-"+peeked;
  //std::cout << "Final number: " << peeked << "\n";
  return Munch(peeked);
}

Munch Scanner::isComment(){
  peeked =  std::string(curr, curr+2);
  //std::cout << "Check if \"" << context << "\" is a comment (peeked:"<< peeked <<"): ";
  if(peeked == "//"){
    peeked = std::string(curr, end);
    //std::cout << "Yes, whole comment:"<< peeked <<"\n";
    //std::cout << peeked << '\n';
    //auto endl = peeked.find_first_of("\n\0");
    //peeked = std::string(curr,begin+endl);
    //std::cout << "Yes\nComment:" << peeked << '\n';
    return Munch(peeked);
  }
  //std::cout<< "No\n";
  return std::nullopt;
}

Munch Scanner::isString(){
  //std::cout << "Check if \"" << context << "\" is a string: \n";
  return std::nullopt;
}

Munch Scanner::isIdentifier(){
  //std::cout << "Check if \"" << context << "\" is a identifier: \n" ;
  return std::nullopt;
}

}
