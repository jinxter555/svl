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

//----------------------------- discontinue expr ast

DisContExprAst::DisContExprAst(std::string s) : ExprAst(s) {};
std::any DisContExprAst::evaluate(SvlmLangContext *slc) {
  slc->svlm_lang->ast_eval_continue = false;
  std::cout << "discontinue with: "; print(); std::cout << "\n";
  return false;
}

void DisContExprAst::codegen(std::vector<std::string>& code) const {};
void DisContExprAst::print() { print_data(); };

//----------------------------- number variable expr
NumberExprAst::NumberExprAst(Number n) : ExprAst(n) {}

void NumberExprAst::codegen(std::vector<std::string>& code) const {
  //code.push_back("push " + std::to_string(value));
  code.push_back("push " + std::to_string(1));
}

std::any NumberExprAst::evaluate(SvlmLangContext *slc) { return ExprAst::get_data(); }

void NumberExprAst::print() { 
  TreeNode::print_data(); //std::cout << "\n";
}
//----------------------------- ident expr
IdentExprAst::IdentExprAst(std::string s) : ExprAst(s) {}
std::any IdentExprAst::evaluate(SvlmLangContext *slc) {return 0;}
std::string IdentExprAst::name() { return std::any_cast<std::string>(get_data()); }
void IdentExprAst::codegen(std::vector<std::string> &code) const {}
void IdentExprAst::print() { print_data(); std::cout << "\n";}

//----------------------------- global variable expr

GvarExprAst::GvarExprAst(std::string s)
 : AssignExprAst(s) {}

std::any GvarExprAst::evaluate(SvlmLangContext *slc) {
  full_symbol_t fst = slc->current_context;  
  fst.mvar = name();
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mvar, fst));
  slc->current_context = fst;
  std::shared_ptr<TreeNode> tn = slc->svlm_lang->context_tree->get_node(keys);
  if(tn==nullptr){
    std::cerr << "variable name: " << fst.mvar << " doesn't exist\n";
    std::cout << "k: "; for( auto k : keys) { std::cout << k << " "; } std::cout << "\n";
    return 0;
  }
  return  tn->get_data();
}
void GvarExprAst::assign(SvlmLangContext *slc, Number &n) {
    std::string name = this->name();
    full_symbol_t fst = slc->current_context;  
    fst.mvar = name;
    std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mvar, fst));

    slc->svlm_lang->context_tree->set_node(keys, n);
    slc->current_context = fst;
}

std::string GvarExprAst::name() { 
  return std::any_cast<std::string>(get_data()); 
}

void GvarExprAst::codegen(std::vector<std::string> &code) const {
}

void GvarExprAst::print() { 
  print_data(); //std::cout << "\n";
}

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
void ArgExprAst::print() { print_data(); std::cout << "\n";}

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

  l->print_data();// std::cout << "\n";
}


//-----------------------------

BinOpExprAst::BinOpExprAst 
( std::shared_ptr<ExprAst> l
, std::shared_ptr<ExprAst> r
, char op
) : ExprAst(op) 
{ ExprAst::add_child("left", l);
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

  char op = std::any_cast<char>(ExprAst::get_data());

  switch(op) {
  case '+': {
    Number a = std::any_cast<Number>(l->evaluate(slc));
    Number b = std::any_cast<Number>(r->evaluate(slc));
    return a + b; }
  case '-': {
    Number a = std::any_cast<Number>(l->evaluate(slc));
    Number b = std::any_cast<Number>(r->evaluate(slc));
    return a - b; }
  case '*': {
    Number a = std::any_cast<Number>(l->evaluate(slc));
    Number b = std::any_cast<Number>(r->evaluate(slc));
    return a * b; }
  case '/': {
    Number a = std::any_cast<Number>(l->evaluate(slc));
    Number b = std::any_cast<Number>(r->evaluate(slc));
    return a / b;}
  case '=': {
    std::shared_ptr<AssignExprAst> al = std::dynamic_pointer_cast<AssignExprAst>(get_child("left"));
    Number b = std::any_cast<Number>(r->evaluate(slc));
    al->assign(slc, b);
    return b; }
  default: std::cerr << "wrong type:\n"; return 0;
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
    std::cout << "code[" <<i << "]: ";
    e->print(); std::cout << "\n";
  }
}

std::any ListExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  std::vector<std::any> result_list;
  int code_count = get_member_size();
  std::cout  << "list eval!\n";
  for(int i=0; i<code_count && slc->svlm_lang->ast_eval_continue; i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    result_list.push_back(e->evaluate(slc)); 
  }
  slc->svlm_lang->ast_eval_continue=true; // reset it to true regardless for the next run
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
  
  add_child("fbody", body );
};

std::any FuncExprAst::evaluate(SvlmLangContext *slc) { 
  std::cout << "In function:"; print_data(); std::cout << " eval!\n";
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("fbody"));
  return l->evaluate(slc);
}
void FuncExprAst::print() {
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("fbody"));
  std::cout << "def "; print_data(); std::cout << " {\n";
  l->print();
  std::cout << "}";
}
void FuncExprAst::codegen(std::vector<std::string> &code) const {
}
//--------------------
CallExprAst::CallExprAst(std::string callee, std::shared_ptr<ListExprAst> args) : ExprAst(callee) {
  add_child("args", args ); // add to universe tree instead, when evaluate push these args to stack
}
void CallExprAst::fcall_args_setup(SvlmLangContext *slc) { 
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  auto args_evaluated = move(std::any_cast<std::vector<std::any>>(l->evaluate(slc)));
  std::cout << "with arguments evaluated:\n"; for(auto e : args_evaluated) { std::cout << e << "\n"; }
  slc->svlm_lang->fcall_args_setup(args_evaluated); // s
}

std::any CallExprAst::evaluate(SvlmLangContext *slc) { 
  fcall_args_setup(slc);

  full_symbol_t fst = slc->current_context;  
  fst.mfunction = std::any_cast<std::string>(get_data());
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mfunction, fst));

  keys.push_back("fbody");
  std::shared_ptr<TreeNode> tn = slc->svlm_lang->context_tree->get_node(keys);
  std::shared_ptr<ExprAst> func = std::any_cast<std::shared_ptr<ExprAst>> ( tn->get_data());

  if(func!=nullptr) {
    std::cout << "in caller print and eval func_body ptr: " << func<< "\n";
    func->evaluate(slc);
    // func->print();
  } else {
    std::cerr << "function body is nullptr!\n";
  }
  return 0;

}

void CallExprAst::print() { 
  std::cout << "call function: "; print_data(); std::cout << "\n";
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  std::cout << "with arguments:{\n"; l->print(); std::cout << "}";

}
void CallExprAst::codegen(std::vector<std::string> &code) const {}

#endif