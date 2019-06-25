#include <cctype>
#include <string>
#include <memory>
#include <optional>

using Munch= std::optional<std::string>;
using Iterator = std::string::iterator;

class Handler
{
    public:
      virtual Munch handle(Iterator& current, Iterator end) = 0;
};

class HandlerWhitespace : public Handler
{
  public:
    HandlerWhitespace(std::unique_ptr<Handler> n = nullptr) : next(std::move(n)) {}
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
    std::unique_ptr<Handler> next;
};


int main(){}
