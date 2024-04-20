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

void NumberExprAst::print() { 
  //return ExprAst::get_data(); 
  //std::cout << evaluate();
  TreeNode::print_data();
}

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
void BinOpExprAst::print() {
  std::shared_ptr<NumberExprAst> l = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("left"));
  std::shared_ptr<NumberExprAst> r = 
    std::dynamic_pointer_cast<NumberExprAst>(TreeNode::get_child("right"));

  l->print();
  print_data();
  r->print();
  std::cout << " ";


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

//--------------------

ListExprAst::ListExprAst(std::any d) : ExprAst(d) {}

void ListExprAst::add(std::shared_ptr<ExprAst> e) {
  ExprAst::add_member(e);
}

std::shared_ptr<ExprAst> ListExprAst::get(int i) {
  return std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
}

void ListExprAst::codegen(std::vector<std::string>& code) const {
  std::shared_ptr<ExprAst> e;
  for(int i=0; i<TreeNode::get_member_size(); i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    e->codegen(code);
  }
}

void ListExprAst::print() {
  std::shared_ptr<ExprAst> e;
  for(int i=0; i<ExprAst::get_member_size(); i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    e->print(); std::cout << "\n";
  }
}

std::any ListExprAst::evaluate() {
  return 0;
}

#endif