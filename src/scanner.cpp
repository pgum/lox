#include "scanner.hpp"

namespace Lox {

Scanner::Scanner(const std::string& _source): source(_source), isTokenized(false){}

Scanner::operator std::vector<Token> ()const {
  return Tokens();
}
std::vector<Token> Scanner::Tokens()const {
  return isTokenized ? tokens : std::vector<Token>();
  }
bool Scanner::scan(){
  sourceCurrent = source.begin();
  std::cout << "Beginning of SCAN: "<< source<<std::endl;
  while(sourceCurrent != source.end()){
    tokens.emplace_back(scanToken());
    //if(sourceCurrent!= source.end()) sourceCurrent = std::next(sourceCurrent);
    if(sourceCurrent==source.end()) break;
    sourceCurrent = std::next(sourceCurrent);
  }
  tokens.emplace_back(TokenEOF());
  isTokenized = (errorsEncountered.size() == 0);
  std::cout <<std::endl << "End of SCAN"<<std::endl;
  return isTokenized;
}

Token Scanner::chooseBestToken(std::vector<Token> tokens){
  for(auto i = tokens.rbegin(); i != tokens.rend(); ++i){
    if(*i != Token()){
      return *i;
    }
  }
  return Token();
}

Token Scanner::scanToken(){
  auto context = std::string(sourceCurrent, sourceCurrent+2);
  auto pattern= context.substr(0,1);
  std::cout << "SCANTOKENS - START p:"<<pattern << " c:"<<context <<std::endl;

  //if first character is a digit
  if(pattern.find_first_not_of("0123456789") == std::string::npos){
    std::cout << "SCANTOKENS - p:"<<pattern << " is DIGIT!"<<std::endl;
    bool hasDot=false;
    pattern="";
    auto npattern= std::string(sourceCurrent, sourceCurrent+1);
    std::cout << "SCANTOKENS - Npattern:"<<npattern <<std::endl;
    while(pattern.find_first_not_of(".0123456789") == std::string::npos){
      npattern= std::string(sourceCurrent, sourceCurrent+1);
      std::cout << "Npattern is [.0123456789]" << npattern <<std::endl;
      if(npattern == "." && hasDot){ std::cout<<"another DOT! breaking"; break; }
      if(npattern == "." && !hasDot){ std::cout<<"first DOT!"; hasDot=true; 
      pattern+=npattern;
      std::cout << "Current pattern:" << pattern <<std::endl;
      if(sourceCurrent+1==source.end()) break;
      sourceCurrent = std::next(sourceCurrent);
      continue;
      }

      if(npattern.find_first_not_of("0123456789") != std::string::npos) { std::cout<<"wierd character in Npattern:" <<npattern;
        sourceCurrent = std::prev(sourceCurrent);
        break;
      }
      pattern+=npattern;
      std::cout << "Current pattern:" << pattern <<std::endl;
      if(sourceCurrent+1==source.end()) break;
      sourceCurrent = std::next(sourceCurrent);
    }
  std::cout << "Scanned number: " << pattern;
  return Token(Token::Type::NUMBER, pattern);
  }
  //if context is // (comment)
  if(context == std::string("//")){
    auto t = Token(Token::Type::COMMENT, std::string(sourceCurrent,source.end()));
    sourceCurrent=source.end();
    return t;
  }
  //if all above doesn't return then look in static map of TokenTypes
  if(Token::tokenTypes.count(context) > 0) return Token(context);
  if(Token::tokenTypes.count(pattern) > 0) return Token(pattern);
  //if totally all fails then add token of type INVALID with lexem that was problematic
  errorsEncountered.emplace_back(line, std::distance(source.begin(), sourceCurrent), "Unknown character", pattern);
  std::cout << "SCANTOKENS - "<< Error(line, std::distance(source.begin(), sourceCurrent), "Unknown character", pattern);
  std::cout << "SCANTOKENS - END"<<std::endl;
  return Token(Token::Type::INVALID, pattern);
}
/*
void Scanner::scanToken(){
  auto c = *sourceCurrent;
  std::string currentChar(1, c);
  std::string pattern= currentChar;
  std::vector<Token> possibleTokens;

  if(isdigit(c)){
    sourceCurrent = std::next(sourceCurrent);
    bool hasDot=false;
    while(sourceCurrent != source.end()){
      auto cc = *sourceCurrent;
      if(isdot(cc) && !hasDot){ pattern+=std::string(1,cc); hasDot=true; continue; }
      if(!isdigit(cc) || (isdot(cc) && hasDot)) { sourceCurrent = std::prev(sourceCurrent); break; }
      pattern+=std::string(1, cc);
      sourceCurrent = std::next(sourceCurrent);
    }
  tokens.emplace_back(pattern);
  return;
  }


  possibleTokens.emplace_back(Token(pattern));

  if(sourceCurrent+1!=source.end()){
    auto c2 = *(sourceCurrent+1);
    std::string currentChar2(1, c2);
    pattern+= currentChar2;
    possibleTokens.emplace_back(Token(pattern));
  }

  auto bestToken = chooseBestToken(possibleTokens);
  if(bestToken.type == Token::Type::COMMENT){
    auto endOfComment = source.end();
    sourceCurrent = endOfComment;
    bestToken.lexem+=std::string(sourceCurrent, source.end());
    tokens.emplace_back(bestToken);
  }else if(bestToken != Token()){
    auto moveSourceCurrent = bestToken.lexem.size() - 1;
    sourceCurrent= std::next(sourceCurrent,moveSourceCurrent);
    tokens.emplace_back(bestToken);
  }else{
      errorsEncountered.emplace_back(line, std::distance(source.begin(), sourceCurrent), "Unknown character", pattern);
  }
}*/
//bool Scanner::isdot(const char &c){return c == '.'; }

/*bool Scanner::checkStringIsNumber(std::string s){
  //Eliminate obvious irritants that could spoil the party
  //Handle special cases here, e.g. return true for "+", "-", "" if they are acceptable as numbers to you
  if (s == "" || s == "." || s == "+" || s == "-" || s == "+." || s == "-.") return false;

  //Remove leading / trailing spaces **IF** they are acceptable to you
  while (s.size() > 0 && s[0] == ' ') s = s.substr(1, s.size() - 1);
  while (s.size() > 0 && s[s.size() - 1] == ' ') s = s.substr(0, s.size() - 1);


  //Remove any leading + or - sign
  if (s[0] == '+' || s[0] == '-')
      s = s.substr(1, s.size() - 1);

  //Remove decimal points
  auto prevLength = s.size();

  size_t start_pos = 0;
  while((start_pos = s.find(".", start_pos)) != std::string::npos)
    s.replace(start_pos, 1, "");

  //If the string had more than 2 decimal points, return false.
  if (prevLength > s.size() + 1) return false;

  //Check that you are left with numbers only!!
  //Courtesy selected answer by Charles Salvia above
  std::string::const_iterator it = s.begin();
  while (it != s.end() && std::isdigit(*it)) ++it;
  return !s.empty() && it == s.end();
}*/

}
