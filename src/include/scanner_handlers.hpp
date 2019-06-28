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
    Munch handle(Iterator current, const Iterator& end);
  private:
    Ptr first;
};

struct Handler{
  public:
    virtual Munch handle(Iterator current, const Iterator& end) = 0;
    virtual void setNext(Ptr h) = 0;
};

struct HandlerBase: public Handler{
  public:
    void setNext(Ptr h) override { next = std::move(h); }
  protected:
    Ptr next;
};

struct Whitespace : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isWhitespace(const char& c);
};

struct Comment : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isComment(const Input& firstTwo);
};

struct Number : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isNumber(const Input& possibleNumber);
};

struct Operator : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isOperator(const char& c);
    bool isOperator(const Input& op);
};

struct String : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isString(const char& c);
};

struct Identifier : public HandlerBase{
  public:
    Munch handle(Iterator current, const Iterator& end) override;
  private:
    bool isIdentifier(const char& c);
};

}//namespace Handlers

}//namespace Lox

