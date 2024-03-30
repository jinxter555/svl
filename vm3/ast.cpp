#include "ast.hh"

#ifndef AST_CPP
#define AST_CPP

template<typename T>
Expr<T>::~Expr() {}

template<typename T>
void NumberExpr<T>::codegen(std::vector<std::string>& code) const {
  code.push_back("push " + std::to_string(value));
}

template<typename T>
T NumberExpr<T>::evaluate() const { return value; }

template <>
int NumberExpr<int>::evaluate() const { return value; }

template<typename T>
T BinOpExpr<T>::evaluate(T v) const {
  T l_val= left->evaluate();
  T r_val= right->evaluate();
  switch(op) {
  case '+': return l_val + r_val;
  case '-': return l_val - r_val;
  case '*': return l_val * r_val;
  case '/': return r_val !=0 ? l_val / r_val : 0;
  default: throw std::invalid_argument("Invalid operator");
  }
}
template<typename T>
void BinOpExpr<T>::codegen(std::vector<std::string>& code) const {
  left->codgen(code);
  right->codegen(code);
  code.push_back("pop ebx");
  code.push_back("pop eax");
  switch(op) {
  case '+': code.push_back("add eax, ebx"); break;
  case '-': code.push_back("sub eax, ebx"); break;
  case '*': code.push_back("imul eax, ebx"); break;
  case '/': code.push_back("cdq"); code.push_back("idv ebx"); break;
  default: throw std::invalid_argument("Invalid opeartor");
  }
}

/*
int main() {
  std::unique_ptr<Expr<int>> n1 = std::make_unique<NumberExpr<int>>(3);
  std::unique_ptr<Expr<float>> f1 = std::make_unique<NumberExpr<float>>(3.145f);

  std::cout <<  n1->evaluate() << "\n";
  std::cout <<  f1->evaluate() << "\n";
}*/

#endif