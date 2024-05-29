#include "ast.hh"
#include "svlm_lang.hh"
#include <iostream>
#include <type_traits>
#include "svlm_operand.hh"
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
//----------------------------- print expr ast
PrintExprAst::PrintExprAst(std::shared_ptr<ExprAst> exp)
 : ExprAst(std::string("print")) {
  add_child("exp", exp);
}
std::any PrintExprAst::evaluate(SvlmLangContext *slc) { 
  auto exp  = std::dynamic_pointer_cast<ExprAst>(get_child("exp"));
  std::any  a = exp->evaluate(slc);
  //std::cout << "printing: " << a;
  std::cout << a;
  return std::string("\n");
}
void PrintExprAst::codegen(std::vector<std::string>& code) const {};
void PrintExprAst::print() { print_data(); };


//----------------------------- discontinue expr ast
DisContExprAst::DisContExprAst(std::string kw) : ExprAst(kw) {};
std::any DisContExprAst::evaluate(SvlmLangContext *slc) {
  slc->svlm_lang->ast_eval_continue = false;
  //std::cout << "discontinue with: "; print(); std::cout << "\n";
  return false;
}
void DisContExprAst::codegen(std::vector<std::string>& code) const {};
void DisContExprAst::print() { print_data(); };

//----------------------------- Bin  variable expr

//----------------------------- number variable expr
NumberExprAst::NumberExprAst(Number n) : ExprAst(n) {}


void NumberExprAst::codegen(std::vector<std::string>& code) const {
  //code.push_back("push " + std::to_string(value));
  code.push_back("push " + std::to_string(1));
}

std::any NumberExprAst::evaluate(SvlmLangContext *slc) { return ExprAst::get_data(); }

std::any NumberExprAst::uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) {
  Number a = std::any_cast<Number>(this->evaluate(slc));
  Number b = std::any_cast<Number>(r->evaluate(slc));
  switch(op) {
  case ast_op::plus:  return a+b;
  case ast_op::minus: return a - b; 
  case ast_op::mul:   return a * b; 
  case ast_op::div:   return a / b;
  case ast_op::eql:   return a == b;
  case ast_op::neql:  return a != b;
  case ast_op::gt:    return a > b;
  case ast_op::lt:    return a < b;
  case ast_op::lteq:  return a <= b;
  case ast_op::gteq:  return a >= b;
  case ast_op::and_:  return a && b;
  case ast_op::or_:  return a || b;
  case ast_op::not_:  return !a;
  default: std::cerr << "wrong type:\n"; return 0;
  }
  return 1;
} 

void NumberExprAst::print() { 
  TreeNode::print_data(); //std::cout << "\n";
}
//----------------------------- atom variable expr
AtomExprAst::AtomExprAst(Atom name) : ExprAst(name) {}
std::any AtomExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
std::string AtomExprAst::name() { return std::any_cast<std::string>(get_data()); }
void AtomExprAst::codegen(std::vector<std::string> &code) const {}
void AtomExprAst::print() { print_data(); std::cout << "--\n";}

std::any AtomExprAst::uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) {
  Atom a = std::any_cast<Atom>(this->evaluate(slc));
  Atom b = std::any_cast<Atom>(r->evaluate(slc));
  switch(op) {
  case ast_op::eql:   return a == b;
  case ast_op::neql:  return a != b;
  default: return false;
  }
  return 0;
} 
//----------------------------- ident expr
IdentExprAst::IdentExprAst(std::string s) : ExprAst(s) {}
std::any IdentExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
std::string IdentExprAst::name() { return std::any_cast<std::string>(get_data()); }
void IdentExprAst::codegen(std::vector<std::string> &code) const {}
void IdentExprAst::print() { print_data(); std::cout << "\n";}

//----------------------------- global variable expr

GvarExprAst::GvarExprAst(std::string name)
 : AssignExprAst(name) {}

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
void GvarExprAst::assign(SvlmLangContext *slc, std::any d) {
    std::string name = this->name();
    //std::string name = name();
    full_symbol_t fst = slc->current_context;  
    fst.mvar = name;
    std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mvar, fst));

//    slc->svlm_lang->context_tree->set_node(keys, d);
    slc->svlm_lang->context_tree->add_node(keys, d);
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
//----------------------------- local variable expr
LvarExprAst::LvarExprAst(std::string name)
 : AssignExprAst(name) {
}
std::string LvarExprAst::name() { 
  return std::any_cast<std::string>(get_data()); 
}
std::any LvarExprAst::evaluate(SvlmLangContext *slc) {
  //std::map<std::string, std::shared_ptr<TreeNode>> lvars;
  if (slc->svlm_lang->svlm_stack.empty()) { std::cerr << "empty stack: Can't find local variable!\n"; return 0; }
  if (slc->svlm_lang->svlm_stack.back()==nullptr) { std::cerr << "stack ack is empty!\n"; return 0; }
  std::shared_ptr<TMA> lvars_tma = std::any_cast<std::shared_ptr<TMA>>(slc->svlm_lang->svlm_stack.back());
  if(lvars_tma==nullptr) { std::cerr << "lvar_tma is null for " << name() << " !\n"; return 0;}

  if( ! (*lvars_tma).count(name()) ) {
    std::cerr << "unknown local variable: " << name() << " !\n"; return 0;
  }
  std::any a = (*lvars_tma)[name()];
  //std::cout << "eval lvar " << name() << " = " << a << "\n";
  return a;
}
void LvarExprAst::codegen(std::vector<std::string> &code) const {
}
void LvarExprAst::assign(SvlmLangContext *slc, std::any d) {
  //std::cout << "assign lvar " << name() << " = " << d << "\n";
    if(slc->svlm_lang->svlm_stack.empty()) { std::cerr << "empty stack: to assign local variable!\n"; return; }
  std::shared_ptr<TMA> lvars_tma 
    = std::any_cast<std::shared_ptr<TMA>>(slc->svlm_lang->svlm_stack.back());
  (*lvars_tma)[name()]= d;
}
void LvarExprAst::print() {
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

//----------------------------- tuple expr
TupleExprAst:: TupleExprAst(std::shared_ptr<ListExprAst> tlist)
: ExprAst("unevaluated tuple") {
  add_child("ulist", tlist);
  //std::cout << "adding tuple\n"; tlist->print();
}

std::any TupleExprAst::evaluate(SvlmLangContext *slc) {
  //std::shared_ptr<ListExprAst> l = std::any_cast<std::shared_ptr<ListExprAst>>(get_data());
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("ulist"));
  //std::cout << "tuple eval\n"; l->print();
  if(!this->evaluated) {
    //std::vector<std::any> elist = move(std::any_cast<std::vector<std::any>>(l->evaluate(slc)));
    Tuple elist(move(std::any_cast<std::vector<std::any>>(l->evaluate(slc))));
    set_data(elist);
    evaluated = true;
    return elist;
  }
  return get_data();
};

bool TupleExprAst::assign(SvlmLangContext *slc, std::shared_ptr<ListExprAst> l, std::vector<std::any> rtva){
  if(l->get_member_size() != rtva.size()) return bool(false);

  for(int i=0; i<l->get_member_size(); i++) {
    std::shared_ptr<ExprAst> lexpr =  std::dynamic_pointer_cast<ExprAst>(l->get_member(i));

    if(lexpr->whoami() == ExprAstType::Gvar || lexpr->whoami() == ExprAstType::Lvar) continue;
   // left side == right hand side?
   // std::any a = lexpr->get_data(); std::cout << a  << " =? " <<  rtva[i] << "\n";
    if(lexpr->get_data().type() != rtva[i].type()) return bool(false);  // any type() not same

    try {
      Number a_n = std::any_cast<Number>(lexpr->get_data()); 
      Number b_n = std::any_cast<Number>(rtva[i]); 
      if(a_n != b_n) return bool(false);
    } catch(const std::bad_any_cast& e) {}

    try {
      Atom a_a = std::any_cast<Atom>(lexpr->get_data()); 
      Atom b_a = std::any_cast<Atom>(rtva[i]); 
      if(a_a != b_a) return bool(false);
    } catch(const std::bad_any_cast& e) {}

  }

  //std::cout << "assign\n";
  for(int i=0; i<l->get_member_size(); i++) {
    std::shared_ptr<ExprAst> lexpr =  std::dynamic_pointer_cast<ExprAst>(l->get_member(i));
    // have to all match here before assign
    if(lexpr->whoami() == ExprAstType::Gvar ||
      lexpr->whoami() == ExprAstType::Lvar) {
      std::shared_ptr<AssignExprAst> lexprv 
      =  std::dynamic_pointer_cast<AssignExprAst>(lexpr);
      lexprv->assign(slc, rtva[i]);
    }

  }
  return bool(true);

}

std::any TupleExprAst::uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> rl, ast_op op) {
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("ulist"));
  auto rtva = std::any_cast<Tuple>(rl->get_data()).get_data(); // rtva is a vector of any now
  //auto rta = rt.get_data(); 

  if(l==nullptr) std::cerr << "tpl l is nullptr\n";

  //std::cout << "lsize:" << l->get_member_size() << "\n"; std::cout << "rsize:" << rtva.size() << "\n";
  switch(op) {
  case ast_op::assign:  return assign(slc, l, rtva);
  default: break;
  }
  return bool(false);
} 
void TupleExprAst::codegen(std::vector<std::string> &code) const {};
void TupleExprAst::print() {
  //std::vector<std::any> elist = std::any_cast<std::vector<std::any>>(get_data());
  try {
    Tuple elist = std::any_cast<Tuple>(get_data());
    elist.print();
  } catch(const std::bad_any_cast& e) {}
}

//----------------------------- decl expr
DeclExprAst::DeclExprAst(std::shared_ptr<IdentExprAst> l, DeclOpcodeAST doa) 
: ExprAst(doa) {
    add_child("left", l);
};


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
, ast_op op
) : ExprAst(op) 
{ ExprAst::add_child("left", l);
  ExprAst::add_child("right", r);
}


void BinOpExprAst::codegen(std::vector<std::string>& code) const {
  /*
  std::shared_ptr<ExprAst> l = 
    std::dynamic_pointer_cast<ExprAst>(ExprAst::get_child("left"));
  std::shared_ptr<ExprAst> r = 
    std::dynamic_pointer_cast<ExprAst>(ExprAst::get_child("right"));

  l->codegen(code);
  r->codegen(code);

  ast_op op = std::any_cast<ast_op>(ExprAst::get_data());

  code.push_back("pop ebx");
  code.push_back("pop eax");
  switch(op) {
    case ast_op::plus: code.push_back("add eax, ebx"); break;
    case ast_op::minus: code.push_back("sub eax, ebx"); break;
    case ast_op::mul: code.push_back("imul eax, ebx"); break;
    case ast_op::div: code.push_back("cdq"); code.push_back("div ebx"); break;
  default: throw std::invalid_argument("Invalid opeartor");
  }
*/
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
  ast_op op = std::any_cast<ast_op>(ExprAst::get_data());
  std::any a_op = op;

  if(l ==nullptr) { std::cerr << "eval left handside is nullptr\n"; } 
  if(r ==nullptr) { std::cerr << "eval right handside r is nullptr\n"; }

  if((l->whoami() == ExprAstType::Gvar || l->whoami() == ExprAstType::Lvar)) {
    if(op == ast_op::assign) {
      // assignment operation for both local and global/module
      std::shared_ptr<AssignExprAst> al
        = std::dynamic_pointer_cast<AssignExprAst>(get_child("left"));
      std::any b = r->evaluate(slc); al->assign(slc, b); return b;
    } 
  } 

  try {
    Number a = std::any_cast<Number>(l->evaluate(slc)); 
    NumberExprAst nea(a);
    return nea.uni_op(slc, r, op);
  } catch(const std::bad_any_cast& e) {}

  try {
//    std::cout << "try tuple!\n";
    Tuple a = std::any_cast<Tuple>(l->evaluate(slc)); 
    Tuple b = std::any_cast<Tuple>(r->evaluate(slc)); 
    l->whoami();
    return l->uni_op(slc, r, op);
  } catch(const std::bad_any_cast& e) {}

  try {
    Atom a = std::any_cast<Atom>(l->evaluate(slc)); 
    AtomExprAst nea(a);
    return nea.uni_op(slc, r, op);
  } catch(const std::bad_any_cast& e) {}


  return 0;
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
    //e->whoami(); std::cout << "\n";
  }
}

std::any ListExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  std::vector<std::any> result_list;
  int code_count = get_member_size();
  //std::cout  << "list eval!\n";
  for(int i=0; i<code_count && slc->svlm_lang->ast_eval_continue; i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    if(e==nullptr) { // could have been an empty  lists of newlines
      /*
      std::cerr << "code count: " << code_count << "\n";
      std::cerr << "list member: "<< i << " is null\n"; 
      return result_list;
      */
      break;}
    result_list.push_back(e->evaluate(slc)); 
  }
  slc->svlm_lang->ast_eval_continue=true; // reset it to true regardless for the next run
  return result_list;
}

std::any ListExprAst::evaluate_last_line(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> 
  e = std::dynamic_pointer_cast<ExprAst>(
    TreeNode::get_member( ExprAst::get_member_size() -1));


  if(e==nullptr){
    std::cerr << "eval expr is null\n";
    return 0;
  }
  slc->last_line=true;
  std::any output = e->evaluate(slc);
  slc->last_line=false;
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
  if(slc->defining_func && slc->interactive) { 
    //std::cout << "prompt defining function\n"; 
    slc->defining_func=false;
    return 0;
  }
  //std::cout << "In function: "; print_data(); std::cout << " eval!\n";
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
  add_child("args", args ); // add to ast tree instead, when evaluate push these args to stack
}
void CallExprAst::fcall_setup(SvlmLangContext *slc) { 
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  auto args_evaluated = move(std::any_cast<std::vector<std::any>>(l->evaluate(slc)));
  //std::cout << "with arguments evaluated:\n"; for(auto e : args_evaluated) { std::cout << e << "\n"; }
  slc->fcall_stack_setup(args_evaluated, std::any_cast<std::string>(get_data())); // s

  //std::cout << "module: " << slc->current_context.smodule  << "\n";
  //std::cout << "calling: "; print_data(); std::cout << "\n";
}

std::any CallExprAst::evaluate(SvlmLangContext *slc) { 
  fcall_setup(slc);

  full_symbol_t fst = slc->current_context;  
  fst.mfunction = std::any_cast<std::string>(get_data());
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mfunction, fst));

  keys.push_back("fbody");
  std::shared_ptr<TreeNode> tn = slc->svlm_lang->context_tree->get_node(keys);
  if(tn==nullptr) {std::cerr << "can't find function!\n"; return 0;}
  std::shared_ptr<ExprAst> func = std::any_cast<std::shared_ptr<ExprAst>> ( tn->get_data());

  if(func!=nullptr) {
    //std::cout << "in caller print and eval func_body ptr: " << func<< "\n";
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

//--------------------  case expr
CaseExprAst::CaseExprAst(std::shared_ptr<ExprAst> top) : ExprAst(top) {
}
std::any CaseExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
void CaseExprAst::codegen(std::vector<std::string> &code) const {}
void CaseExprAst::print() { print_data(); std::cout << "\n";}


//--------------------  case match expr
CaseMatchExprAst::CaseMatchExprAst(std::shared_ptr<ExprAst> match,
 std::shared_ptr<ListExprAst> body, ast_op op) : ExprAst(op) {
  add_child("match", match);
  add_child("cbody", body);
}
std::any CaseMatchExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
void CaseMatchExprAst::codegen(std::vector<std::string> &code) const {}
void CaseMatchExprAst::print() { print_data(); std::cout << "\n";}

//--------------------  flow expr
FlowExprAst::FlowExprAst(std::shared_ptr<ExprAst> top, 
std::shared_ptr<ListExprAst> body) : ExprAst(top) {
  add_child("cbody", body);
  std::cout << "FlowExprAst adding c body\n";
  //body->print();
}
std::any FlowExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
void FlowExprAst::codegen(std::vector<std::string> &code) const {}
void FlowExprAst::print() { 
  std::shared_ptr<ExprAst> e = std::any_cast<std::shared_ptr<ExprAst>>( get_data());
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  if(e==nullptr) { std::cerr << "flow is null!\n"; return; }
  if(l==nullptr) { std::cerr << "flow match list is null!\n"; return; }

  std::cout << "flow "; e->print_data(); std::cout << " do\n";

  std::cout << "---flow match list--\n";
  l->print();
}


//--------------------  flow match expr
FlowMatchExprAst::FlowMatchExprAst(std::shared_ptr<ExprAst> match,
 std::shared_ptr<ListExprAst> body, ast_op op) : ExprAst(op) {
  add_child("match", match);
  add_child("cbody", body);
}
std::any FlowMatchExprAst::evaluate(SvlmLangContext *slc) {return get_data();}
void FlowMatchExprAst::codegen(std::vector<std::string> &code) const {}
void FlowMatchExprAst::print() { 
  std::any op = get_data(); std::cout << "op "; std::cout << op;
  auto m = std::dynamic_pointer_cast<ExprAst>(get_child("match"));
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  std::cout << " match ";
  m->print_data();
  std::cout << " cbody ";
  l->print();
  std::cout << "\n";
}

#endif