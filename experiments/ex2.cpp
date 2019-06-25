#include <iostream>
#include <cctype>
#include <iterator>
#include <vector>
#include <string>
#include <memory>
#include <optional>
#include <utility>
#include <algorithm>
namespace Lox{
using Input= std::string;
using Iterator = Input::const_iterator;
using Munch= std::optional<Input>;

using Lexem= std::string;
using Error= std::string;
using Lexems= std::vector<Lexem>;
using Errors= std::vector<Error>;
using ScannerOutput= std::pair<Lexems, Errors>;

namespace Handlers{
class Handler;
using Ptr = std::unique_ptr<Handler>;
using Handlers = std::vector<Ptr>;

class Handler
{
    public:
      virtual Munch handle(Iterator& current, Iterator end) = 0;
};

class Whitespace : public Handler
{
  public:
    Whitespace(Ptr n = nullptr) : next(std::move(n)) {}
    ~Whitespace() = default;
    Munch handle(Iterator& current, Iterator end) override
    {
      if(current == end) return std::nullopt;
      if(char c = *current; isWhitespace(c)){
        ++current;
        return std::string(1, c);
      }
      else if (next) return next->handle(current, end);
      return std::nullopt;
    }
  private:
    bool isWhitespace(char c){
      return std::isspace(static_cast<unsigned char>(c));
    }
    Ptr next;
};


class Comment : public Handler
{
  public:
    Comment(Ptr n = nullptr) : next(std::move(n)) {}
    ~Comment() = default;
    Munch handle(Iterator& current, Iterator end) override
    {
      if(current == end) return std::nullopt;
      if(Input firstTwo = Input(current, current+2); isComment(firstTwo)){
        auto comment= std::string(current, std::find(current, end,'\n'));
        std::advance(current, comment.size());
        return comment;
      }
      else if (next) return next->handle(current, end);
      return std::nullopt;
    }
  private:
    Ptr next;
    bool isComment(Input firstTwo){
      return firstTwo == "//";
    }
};

}

ScannerOutput scan(const Input& input){
  Lexems lexems;
  Errors errors;
  auto comment = Handlers::Ptr(new Handlers::Comment());
  auto whitespace = Handlers::Ptr(new Handlers::Whitespace(std::move(comment)));
  
  Iterator end = input.end();
  Iterator current = input.begin();
  Munch munch;
  while(current != end){
    munch = whitespace->handle(current, end);
    if(munch){
      lexems.emplace_back(munch.value());
    }else{
      std::string e= "0:" + std::to_string(std::distance(input.begin(), current)) + " Unknown character: " + std::string(1, *current) + "\n";
      errors.emplace_back(e);
      std::advance(current, 1);
    }
  }
  lexems.emplace_back("\0");
  return {lexems, errors};
}


}


int main(){
  auto output = Lox::scan(" //a\n  //b");
  for(const auto& l : output.first) std::cout << "Lexem: \"" <<  l << "\"\n";
}
