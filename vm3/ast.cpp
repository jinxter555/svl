#include "ast.hh"
#include "svlm_lang.hh"
#include <iostream>
//#include "printer_any.hh"
std::ostream& operator << (std::ostream& out, std::any& a) ;


#ifndef AST_CPP
#define AST_CPP

ExprAst::ExprAst() {
   current_context = {
    CONTEXT_UNIV, 
    "svlm_program_tree", 
    "symbols/1.0.0",
    "", // mod
    "", // mvar
    "", // mfun
    "", // larg
    "", // lvar
    "", // label
    };
}


ExprAst::~ExprAst() {}

//----------------------------- number variable expr
void NumberExprAst::codegen(std::vector<std::string>& code) const {
  //code.push_back("push " + std::to_string(value));
  code.push_back("push " + std::to_string(1));
}

std::any NumberExprAst::evaluate(SvlmLangContext *slc) { return ExprAst::get_data(); }

void NumberExprAst::print() { 
  //return ExprAst::get_data(); 
  //std::cout << evaluate();
  TreeNode::print_data();
}
//----------------------------- ident expr
IdentExprAst::IdentExprAst(std::string s) : ExprAst(s) {}
std::any IdentExprAst::evaluate(SvlmLangContext *slc) {return 0;}
std::string IdentExprAst::name() { return std::any_cast<std::string>(get_data()); }
void IdentExprAst::codegen(std::vector<std::string> &code) const {}
void IdentExprAst::print() { print_data(); }

//----------------------------- global variable expr

GvarExprAst::GvarExprAst(std::string s)
 : ExprAst(s) {}

std::any GvarExprAst::evaluate(SvlmLangContext *slc) {
  full_symbol_t fst = slc->current_context;  
  fst.mvar = name();
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mvar, fst));
  slc->current_context = fst;
  std::shared_ptr<TreeNode> tn = slc->svlm_lang->context_tree->get_node(keys);
  if(tn==nullptr){
    std::cerr << "variable name: " << fst.mvar << " doesn't exist\n";
    return 0;
  }
  return  tn->get_data();
}

std::string GvarExprAst::name() { 
  return std::any_cast<std::string>(get_data()); 
}

void GvarExprAst::codegen(std::vector<std::string> &code) const {
}

void GvarExprAst::print() { print_data(); }

//----------------------------- func arg expr
ArgExprAst::ArgExprAst(std::string name, unsigned char pos) {
  arg_name_pos_t arg;
  arg.name = name;
  arg.pos = pos;
  set_data(arg);
}

ArgExprAst::ArgExprAst(arg_name_pos_t arg) : ExprAst(arg) {}
void ArgExprAst::codegen(std::vector<std::string> &code) const {
}
std::string ArgExprAst::name() { 
  return std::any_cast<std::string>(get_data()); 
}
arg_name_pos_t ArgExprAst::arg() { 
  return std::any_cast<arg_name_pos_t>(get_data()); 
}
std::any ArgExprAst::evaluate(SvlmLangContext *slc) {
  return 0;
}
void ArgExprAst::print() { print_data(); }

//----------------------------- decl expr
DeclExprAst::DeclExprAst(std::shared_ptr<IdentExprAst> l, DeclOpcodeAST doa) 
: ExprAst(doa) {
    add_child("left", l);
};

class SvlmLang;

std::any DeclExprAst::evaluate(SvlmLangContext *slc) {
  auto l = std::dynamic_pointer_cast<IdentExprAst>(get_child("left"));
  auto doa = std::any_cast<DeclOpcodeAST>(get_data());
  full_symbol_t fst = slc->current_context;  
  switch(doa) {
  case DeclOpcodeAST::MODULE: 
    fst.smodule = l->name();
    break;
  default: break;
  }
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::smodule, fst));

  //std::cout << "k: "; for( auto k : keys) { std::cout << k << " "; } std::cout << "\n";

  slc->svlm_lang->context_tree->set_node(keys, std::string("module name2"));
  slc->current_context = fst;
  return 0;
}
void DeclExprAst::codegen(std::vector<std::string> &code) const {
}
void DeclExprAst::print() { 
  std::shared_ptr<IdentExprAst> l = 
    std::dynamic_pointer_cast<IdentExprAst>(get_child("left"));
  switch (std::any_cast<DeclOpcodeAST>(get_data())) {
  case DeclOpcodeAST::MODULE:  
    std::cout << "Module:" ; break;
  default: 
    std::cerr << "unknown decl!\n"; break;
  }

  l->print_data();
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
  std::shared_ptr<ExprAst> l = 
    std::dynamic_pointer_cast<ExprAst>(ExprAst::get_child("left"));
  std::shared_ptr<ExprAst> r = 
    std::dynamic_pointer_cast<ExprAst>(ExprAst::get_child("right"));

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
  std::shared_ptr<ExprAst> l = 
    std::dynamic_pointer_cast<ExprAst>(get_child("left"));
  std::shared_ptr<ExprAst> r = 
    std::dynamic_pointer_cast<ExprAst>(get_child("right"));

  l->print();
  print_data();
  r->print();
  std::cout << " ";
}

std::any BinOpExprAst::evaluate(SvlmLangContext *slc) {

  std::shared_ptr<ExprAst> l = 
    std::dynamic_pointer_cast<ExprAst>(get_child("left"));
  std::shared_ptr<ExprAst> r = 
    std::dynamic_pointer_cast<ExprAst>(get_child("right"));

  if(l ==nullptr) { std::cerr << "l is nullptr\n"; }
  if(r ==nullptr) { std::cerr << "r is nullptr\n"; }

  op_t op = std::any_cast<op_t>(ExprAst::get_data());
  switch(op.op_type) {
  case BinOpcodeAST::INT_OP_INT:  {
    int a = std::any_cast<int>(l->evaluate(slc));
    int b = std::any_cast<int>(r->evaluate(slc));
    return binop(a, b, op.op); }
  case BinOpcodeAST::FLT_OP_FLT: {
    float a = std::any_cast<float>(l->evaluate(slc));
    float b = std::any_cast<float>(r->evaluate(slc));
    return binop(a, b, op.op); }
  case BinOpcodeAST::FLT_OP_INT: {
    float a = std::any_cast<float>(l->evaluate(slc));
    float b = static_cast<float>(std::any_cast<int>(r->evaluate(slc)));
    return binop(a, b, op.op); }
  case BinOpcodeAST::INT_OP_FLT: {
    int a = std::any_cast<int>(l->evaluate(slc));
    int b = static_cast<int>(std::any_cast<float>(r->evaluate(slc)));
    return binop(a, b, op.op); }
  case BinOpcodeAST::ASSIGN_INT_G: {

    std::shared_ptr<GvarExprAst> al = 
      std::dynamic_pointer_cast<GvarExprAst>(get_child("left"));

    std::string name = al->name();
    int b = std::any_cast<int>(r->evaluate(slc));

    full_symbol_t fst = slc->current_context;  
    fst.mvar = name;
    std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mvar, fst));

    slc->svlm_lang->context_tree->set_node(keys, b);
    slc->current_context = fst;

    return b;}
  default: std::cerr << "wrong type: " <<  static_cast<int>(op.op_type) << "\n"; return 0;
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
  add_member(e);
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
  std::cout << "code size: " << get_member_size() << "\n";

  for(int i=0; i<get_member_size(); i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    if(e==nullptr) { std::cerr << "encounter null expr at " << i << "\n"; continue;; }
    e->print(); std::cout << "\n";
  }
}

std::any ListExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  std::vector<std::any> result_list;
  for(int i=0; i<ExprAst::get_member_size(); i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    result_list.push_back(e->evaluate(slc)); 
  }
  return result_list;
}
std::any ListExprAst::evaluate_last_line(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  e = 
    std::dynamic_pointer_cast<ExprAst>(
      TreeNode::get_member( ExprAst::get_member_size() -1)
    );
  //std::cout << "eval last line\n";
  std::any output = e->evaluate(slc);
  //std::cout << output << "\n";
  // remove last line here

  return output;
}
//--------------------
FuncExprAst::FuncExprAst(
  std::string name, 
  std::vector<std::string> args, 
  std::shared_ptr<ListExprAst> body) : ExprAst(name) {
  
  add_child("body", body );
};


std::any FuncExprAst::evaluate(SvlmLangContext *slc) { return 0; }
void FuncExprAst::print() {
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("body"));
  std::cout << "function body:\n";
  l->print();
}
void FuncExprAst::codegen(std::vector<std::string> &code) const {}
//--------------------
CallExprAst::CallExprAst(std::string callee, std::shared_ptr<ListExprAst> args) : ExprAst(callee) {
  add_child("args", args ); // add to universe tree instead, when evaluate push these args to stack
}
std::any CallExprAst::evaluate(SvlmLangContext *slc) { return 0;}
void CallExprAst::print() { 
  std::cout << "calling function: "; print_data(); std::cout << "\n";
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  std::cout << "with arguments: "; print_data(); std::cout << "\n";
  l->print();
  std::cout << "\n";
}
void CallExprAst::codegen(std::vector<std::string> &code) const {}

#endif