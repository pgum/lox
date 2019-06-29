//sudo apt install clisp
//g++ -o ex3 ex3.cpp -Wall -Wextra -Werror -std=c++2a && ./ex3 | clisp -q
//
#include <iostream>
#include <vector>
#include <string>

using Token= std::string;
class ExprBase{
  public:
  virtual void traverse() = 0;
};

template<size_t Arity>
class Expr: public ExprBase {//: public ExpressionBase {
  public:
  Expr(Token _operator): value(_operator){}
  void add(ExprBase *ele){
    if(children.size()< Arity) children.push_back(ele);
    else std::cout << "Cannot push more than arity " << Arity << '\n';
  }
  void traverse() override{
    std::cout << "(" << value << ' ';
    for(auto const& child : children) child->traverse();
    std::cout<< ") ";
  }
  protected:
  Token value;
  std::vector<ExprBase*> children;
};

class Terminal: public Expr<0>{
  public:
  Terminal(Token val) : Expr(val){ value = val; }
  void traverse(){ std::cout << value << ' '; }
};

class Unary: public Expr<1>{
  public:
  Unary(Token _operator, ExprBase *rhs= nullptr): Expr(_operator){ add(rhs); }
};

class Binary: public Expr<2>{
  public:
  Binary(Token _operator, ExprBase *lhs= nullptr, ExprBase *rhs= nullptr): Expr(_operator){ add(lhs); add(rhs); }
};

int main()
{
  auto lhs = Binary(Token("+"), new Terminal("10"), new Terminal("2.3"));
  auto rhs = Unary(Token("-"), new Terminal("-12.3"));

  auto tree = Binary(Token("-"), &lhs, &rhs);
  tree.traverse();
  std::cout << '\n';
}

/*
Rules ruleset =
{
  {Expression, Literal  },
  //{Expression, Grouping }, - probably dont need that
  {Expression, Unary    },
  {Expression, Binary   },

  {Literal, Terminal<Number> },
  {Literal, Terminal<String> },

  {Literal, Terminal("true") },
  {Literal, Terminal("false") },
  {Literal, Terminal("nil") },

  //{Grouping, Terminal("("), Expression, Terminal(")") },

  {Unary, Terminal("-"), Expression },
  {Unary, Terminal("!"), Expression },

  {Binary, Expression, Operator, Expression },

  {Operator, Terminal("==") },
  {Operator, Terminal("!=") },
  {Operator, Terminal("<") },
  {Operator, Terminal("<=") },
  {Operator, Terminal(">") },
  {Operator, Terminal(">=") },
  {Operator, Terminal("+") },
  {Operator, Terminal("-") },
  {Operator, Terminal("*") },
  {Operator, Terminal("/") },
}

*/
