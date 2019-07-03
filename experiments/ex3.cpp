//g++ -o ex3 ex3.cpp -Wall -Wextra -Werror -std=c++2a && ./ex3
#include <iostream>
#include <memory>
#include <vector>
#include <string>
using Token= std::string;

namespace Lox::Parser{
class ExprBase{
  public:
  virtual ~ExprBase() = default;
  virtual void traverse() = 0;
};

using ExprPtr = std::unique_ptr<ExprBase>;

template<size_t Arity>
class Expr: public ExprBase {
  public:
  Expr(Token _operator): value(_operator){}
  void traverse() override{
    std::cout << "(" << value << ' ';
    for(auto const& child : children) child->traverse();
    std::cout<< ") ";
  }
  void add(ExprPtr ele){
    if(children.size()< Arity) children.emplace_back(std::move(ele));
    else std::cout << "Cannot push more than arity " << Arity << '\n';
  }
  protected:
  Token value;
  std::vector<ExprPtr> children;
};

class Terminal: public Expr<0>{
  public:
  Terminal(Token val) : Expr(val){}
  void traverse(){ std::cout << value << ' '; }
};

class Unary: public Expr<1>{
  public:
  Unary(Token _operator, ExprPtr rhs= nullptr): Expr(_operator){
    add(std::move(rhs));
  }
};

class Binary: public Expr<2>{
  public:
  Binary(Token _operator, ExprPtr lhs= nullptr, ExprPtr rhs= nullptr): Expr(_operator){
    add(std::move(lhs));
    add(std::move(rhs));
  }
};
}

int main()
{
  using namespace Lox::Parser;
  auto t_1 = std::make_unique<Terminal>(Token("10"));
  auto t_2 = std::make_unique<Terminal>(Token("2.3"));
  auto t_3 = std::make_unique<Terminal>(Token("-12.3"));

  auto lhs = std::make_unique<Binary>(Token("+"), std::move(t_1), std::move(t_2));
  auto rhs = std::make_unique<Unary>(Token("-"), std::move(t_3));
  auto tree = Binary(Token("-"), std::move(lhs), std::move(rhs));
  //(- (+ 10 2.3 ) (- -12.3 ) )
  tree.traverse();
  std::cout << '\n';
}

