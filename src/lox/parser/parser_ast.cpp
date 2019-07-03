#include <iostream>
#include <memory>
#include <vector>
#include <string>
#include "parser_ast.hpp"

namespace Lox::Parser{

template<size_t Arity>
void Expr<Arity>::traverse() {
  print();
}

template<size_t Arity>
void Expr<Arity>::print() {
    std::cout << "(" << value << ' ';
    for(auto const& child : children) child->traverse();
    std::cout<< ") ";
}
template<size_t Arity>
void Expr<Arity>::add(Expr::Ptr ele){
  if(children.size()< Arity) children.emplace_back(std::move(ele));
  else std::cout << "Cannot push more than arity " << Arity << '\n'; //TODO: error handling
}

void Terminal::print(){
  std::cout << value << ' ';
}

}
/*
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
*/

