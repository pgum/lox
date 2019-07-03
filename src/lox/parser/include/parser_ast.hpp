//#include <iostream>
#include <memory>
#include <vector>
#include "token.hpp"

namespace Lox::Parser{
class ExprBase{
  public:
  virtual ~ExprBase() = default;
  virtual void print() = 0;
  virtual void traverse() = 0;
};

template<size_t Arity>
class Expr: public ExprBase {
  public:
  using Ptr = std::unique_ptr<ExprBase>;
  Expr(Token _operator): value(_operator){}
  void print() override;
  void traverse() override;
  void add(Ptr ele);
  protected:
  Token value;
  std::vector<Ptr> children;
};

class Terminal: public Expr<0>{
  public:
  Terminal(Token val) : Expr(val){}
  void print() override;
};

class Unary: public Expr<1>{
  public:
  Unary(Token _operator, Expr::Ptr rhs= nullptr): Expr(_operator){
    if(rhs) add(std::move(rhs));
  }
};

class Binary: public Expr<2>{
  public:
  Binary(Token _operator, Expr::Ptr lhs= nullptr, Expr::Ptr rhs= nullptr): Expr(_operator){
    if(lhs) add(std::move(lhs));
    if(rhs) add(std::move(rhs));
  }
};

}
