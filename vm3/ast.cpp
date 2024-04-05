#include "ast.hh"
#include <iostream>

#ifndef AST_CPP
#define AST_CPP

ExprAst::~ExprAst() {}

void NumberExprAst::codegen(std::vector<std::string>& code) const {
  //code.push_back("push " + std::to_string(value));
  code.push_back("push " + std::to_string(1));
}

std::any NumberExprAst::evaluate() { return ExprAst::get_data(); }

//-----------------------------

BinOpExprAst::BinOpExprAst 
( std::shared_ptr<ExprAst> l
, std::shared_ptr<ExprAst> r
, op_t op
) : ExprAst(op) 
{ ExprAst::add_child("left", l);
  ExprAst::add_child("right", r);
}

BinOpExprAst::BinOpExprAst
( std::shared_ptr<ExprAst> l
, std::shared_ptr<ExprAst> r
, BinOpcodeAST t, char o) 
{ op_t op = {t, o};
  ExprAst::set_data(op);
  ExprAst::add_child("left", l);
  ExprAst::add_child("right", r);
}

void BinOpExprAst::codegen(std::vector<std::string>& code) const {
  std::shared_ptr<NumberExprAst> l = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("left"));
  std::shared_ptr<NumberExprAst> r = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("right"));

  l->codegen(code);
  r->codegen(code);

  op_t op = std::any_cast<op_t>(ExprAst::get_data());

  code.push_back("pop ebx");
  code.push_back("pop eax");
  switch(op.op) {
  case '+': code.push_back("add eax, ebx"); break;
  case '-': code.push_back("sub eax, ebx"); break;
  case '*': code.push_back("imul eax, ebx"); break;
  case '/': code.push_back("cdq"); code.push_back("idv ebx"); break;
  default: throw std::invalid_argument("Invalid opeartor");
  }
}


std::any BinOpExprAst::evaluate() {
  std::shared_ptr<NumberExprAst> l = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("left"));
  std::shared_ptr<NumberExprAst> r = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("right"));

  op_t op = std::any_cast<op_t>(ExprAst::get_data());
  switch(op.op_type) {
  case BinOpcodeAST::INT_OP_INT:  {
    int a = std::any_cast<int>(l->evaluate());
    int b = std::any_cast<int>(r->evaluate());
    return binop(a, b, op.op); }
  case BinOpcodeAST::FLT_OP_FLT: {
    float a = std::any_cast<float>(l->evaluate());
    float b = std::any_cast<float>(r->evaluate());
    return binop(a, b, op.op); }
  case BinOpcodeAST::FLT_OP_INT: {
    float a = std::any_cast<float>(l->evaluate());
    float b = static_cast<float>(std::any_cast<int>(r->evaluate()));
    return binop(a, b, op.op); }
  case BinOpcodeAST::INT_OP_FLT: {
    int a = std::any_cast<int>(l->evaluate());
    int b = static_cast<int>(std::any_cast<float>(r->evaluate()));
    return binop(a, b, op.op); }
  default: std::cerr << "wrong type\n"; return 0;
  }
}

template <typename T>
std::any BinOpExprAst::binop(T a, T b, char op) {
  switch(op) {
  case '+': return std::any_cast<T>(a) + std::any_cast<T>(b);
  case '-': return std::any_cast<T>(a) - std::any_cast<T>(b);
  case '*': return std::any_cast<T>(a) * std::any_cast<T>(b);
  case '/': return std::any_cast<T>(a) !=0 
    ? std::any_cast<T>(a) / std::any_cast<T>(b) : 0;
  default: throw std::invalid_argument("Invalid operator");
  }
}
/*
template <typename T, typename U>
std::any BinOpExprAst::binop(T a, U b, char op) {
  switch(op) {
  case '+': return std::any_cast<T>(a) + std::any_cast<U>(b);
  case '-': return std::any_cast<T>(a) - std::any_cast<U>(b);
  case '*': return std::any_cast<T>(a) * std::any_cast<U>(b);
  case '/': return std::any_cast<T>(a) !=0 
    ? std::any_cast<T>(a) / std::any_cast<U>(b) : 0;
  default: throw std::invalid_argument("Invalid operator");
  }
}
*/



int main() {
  //NumberExprAst a(3);
  std::shared_ptr<ExprAst> n1 = std::make_shared<NumberExprAst>(3);
  std::shared_ptr<ExprAst> n2 = std::make_shared<NumberExprAst>(5);
  std::shared_ptr<ExprAst> f1 = std::make_shared<NumberExprAst>(3.145f);

  std::cout <<  std::any_cast<int>(n1->evaluate()) << "\n";
  std::cout <<  std::any_cast<float>(f1->evaluate()) << "\n";

  op_t op1 = {BinOpcodeAST::INT_OP_INT, '-'};
  op_t op2 = {BinOpcodeAST::FLT_OP_FLT, '*'};
  op_t op3 = {BinOpcodeAST::FLT_OP_INT, '*'};

  // std::shared_ptr<ExprAst> b1 = std::make_shared<BinOpExprAst>( std::make_shared<NumberExprAst>(3), std::make_shared<NumberExprAst>(5), op1); std::cout <<  std::any_cast<int>(b1->evaluate()) << "\n";

  // std::shared_ptr<ExprAst> b2 = std::make_shared<BinOpExprAst>( std::make_shared<NumberExprAst>(3.145f), std::make_shared<NumberExprAst>(5.15f), op2); std::cout <<  std::any_cast<float>(b2->evaluate()) << "\n";

  std::shared_ptr<ExprAst> b3 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3.145f),
    std::make_shared<NumberExprAst>(5), 
    BinOpcodeAST::FLT_OP_INT, '*');

  std::shared_ptr<ExprAst> b4 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3),
    std::make_shared<NumberExprAst>(75.5555f), 
    BinOpcodeAST::INT_OP_FLT, '*');


  std::cout <<  std::any_cast<float>(b3->evaluate()) << "\n";
  std::cout <<  std::any_cast<int>(b4->evaluate()) << "\n";
}

/*
  std::shared_ptr<ExprAst> b1 = std::make_shared<BinOpExprAst>(
    std::make_shared<NumberExprAst>(3),
    std::make_shared<NumberExprAst>(5),
  '-');



  std::cout <<  std::any_cast<int>(n1->evaluate()) << "\n";
  std::cout <<  std::any_cast<float>(f1->evaluate()) << "\n";
  std::cout <<  std::any_cast<int>(b1->evaluate()) << "\n";
  //std::cout <<  std::any_cast<float>(b2->evaluate()) << "\n";
}
*/
#endif