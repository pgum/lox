#pragma once
#include <vector>
#include <memory>

#include "scanner.hpp"

namespace Lox{
using Input= std::string;
using Iterator = Input::const_iterator;
using Munch= std::optional<std::string>;

namespace Handlers{
class Handler;
using Ptr = std::unique_ptr<Handler>;
using Handlers = std::vector<Ptr>;

class Executor{
  public:
    Executor(std::initializer_list<Handler*> rawHandlerPtrs);
    Munch handle(Iterator& current, Iterator end);
  private:
    Ptr first;
};

struct Handler{
    public:
      virtual Munch handle(Iterator& current, Iterator end) = 0;
      virtual void setNext(Ptr h) = 0;
};

struct Whitespace : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isWhitespace(const char& c);
};

struct Comment : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isComment(const Input& firstTwo);
};

struct Number : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isNumber(const Input& possibleNumber);
};

struct Operator : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isOperator(const char& c);
    bool isOperator(const Input& op);
};

struct String : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isString(const char& c);
};

struct Identifier : public Handler{
  public:
    Munch handle(Iterator& current, Iterator end) override;
    void setNext(Ptr h){ next = std::move(h); }
  private:
    Ptr next;
    bool isIdentifier(const char& c);
};

}//namespace Handlers

}//namespace Lox

