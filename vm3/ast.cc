#include "ast.hh"
#include "svlm_lang.hh"
#include <iostream>
#include <type_traits>
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
 : ExprAst(ExprAstType::Print) {
  add_child("exp", exp);
}
std::any PrintExprAst::evaluate(SvlmLangContext *slc) { 
  auto exp  = std::dynamic_pointer_cast<ExprAst>(get_child("exp"));
  std::any  a = exp->evaluate(slc);
  std::cout << a;
  return std::string("");
}
void PrintExprAst::codegen(std::vector<std::string>& code) const {};
void PrintExprAst::print() { 
  std::cout << "print ";
  auto exp  = std::dynamic_pointer_cast<ExprAst>(get_child("exp"));
  exp->print();
};


//----------------------------- discontinue expr ast
ControlFlowExprAst::ControlFlowExprAst(ControlFlow cf)
 : ExprAst(ExprAstType::ControlFlow) {
  add_child_data("value", cf);
};

ControlFlowExprAst::ControlFlowExprAst
( ControlFlow cf
, std::shared_ptr<ExprAst> exp
) : ExprAst(cf) {
  add_child_data("value", cf);
  add_child("exp", exp);
}

std::any ControlFlowExprAst::evaluate(SvlmLangContext *slc) {
  slc->svlm_lang->control_flow = std::any_cast<ControlFlow>(get_child_data("value"));
  //std::cout << "control flow with: "; print(); std::cout << "\n";
  //std::cout << "ast eval continue: " <<  static_cast<int>(slc->svlm_lang->control_flow)  << "\n";
  slc->svlm_lang->fc_exp = std::dynamic_pointer_cast<ExprAst>(get_child("exp"));
  return slc->svlm_lang->control_flow;
}
void ControlFlowExprAst::codegen(std::vector<std::string>& code) const {};
void ControlFlowExprAst::print() { 
  std::string outstr;
  switch(std::any_cast<ControlFlow>(get_child_data("value"))){
  case ControlFlow::run:
    outstr = "run"; break;
  case ControlFlow::ast_break:
    outstr = "break"; break;
  case ControlFlow::ast_continue:
    outstr = "continue"; break;
  case ControlFlow::ast_return:
    outstr = "return"; break;
  case ControlFlow::ast_wait:
    outstr = "wait"; break;
  case ControlFlow::sleep:
    outstr = "sleep"; break;
  case ControlFlow::stop:
    outstr = "stop"; break;
  case ControlFlow::ast_exit:
    outstr = "exit"; break;
  default: outstr = "error control state"; break;
  };
  std::cout << outstr << " ";
  auto exp  = std::dynamic_pointer_cast<ExprAst>(get_child("exp"));
  if(exp!=nullptr) exp->print();
  std::cout << "\n";




}

//----------------------------- Bin  variable expr
//----------------------------- number variable expr
OperandExprAst::OperandExprAst(Operand o) : ExprAst(ExprAstType::Operand) { 
  add_child_data("value", o);
}
void OperandExprAst::codegen(std::vector<std::string>& code) const {
}

std::any OperandExprAst::evaluate(SvlmLangContext *slc) { 
  return get_child_data("value");
}

std::any OperandExprAst::uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) {
  Operand a = std::any_cast<Operand>(evaluate(slc));
  Operand b = std::any_cast<Operand>(r->evaluate(slc));
  switch(op) {
  case ast_op::plus:  return a+b;
  case ast_op::minus: return a - b; 
  case ast_op::mul:   return a * b; 
  case ast_op::div:   return a / b;
  case ast_op::eql:   return Operand(a == b);
  case ast_op::neql:  return Operand(a != b);
  case ast_op::gt:    return Operand(a > b);
  case ast_op::lt:    return Operand(a < b);
  case ast_op::lteq:  return Operand(a <= b);
  case ast_op::gteq:  return Operand(a >= b);
  case ast_op::and_:  return Operand(a && b);
  case ast_op::or_:   return Operand(a || b);
  case ast_op::not_:  return Operand(!a);
  default: std::cerr << "wrong type:\n"; return 0;
  }
  return Operand(false);
} 

void OperandExprAst::print() { 
  Operand o = std::any_cast<Operand>(get_child_data("value"));
  std::cout << o;
}


//----------------------------- ident expr
IdentExprAst::IdentExprAst(const std::string &s) : ExprAst(ExprAstType::Ident) {
  add_child_data("value", s);
}
std::any IdentExprAst::evaluate(SvlmLangContext *slc) {
  return get_child_data("value");
}
std::string IdentExprAst::name() { 
  return std::any_cast<std::string>(get_child_data("value")); 
}
void IdentExprAst::codegen(std::vector<std::string> &code) const {}
void IdentExprAst::print() { 
  std::string s = std::any_cast<std::string>(get_child_data("value"));
  std::cout << s << "\n";
}

//----------------------------- global variable expr

GvarExprAst::GvarExprAst(const std::string &name)
 : AssignExprAst(ExprAstType::Gvar) {
  add_child_data("value", name);
}

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
  return  tn->get_data(); // this store values of the variable name! do not use get_child_data()
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
  return std::any_cast<std::string>(get_child_data("value")); 
}

void GvarExprAst::codegen(std::vector<std::string> &code) const {
}

void GvarExprAst::print() { 
  std::cout << "$" << name();
}
//----------------------------- local variable expr
LvarExprAst::LvarExprAst(const std::string &name)
 : AssignExprAst(ExprAstType::Lvar) {
  add_child_data("value", name);
}
std::string LvarExprAst::name() { 
  return std::any_cast<std::string>(get_child_data("value"));
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
  std::cout << name() << "\n";
}



//----------------------------- func arg expr
/*
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
*/

//----------------------------- tuple expr
TupleExprAst::TupleExprAst(std::shared_ptr<ListExprAst> tlist)
: ExprAst(ExprAstType::Tuple) { 
  add_child("ulist", tlist); 
  add_child_data("value", nullptr);
}

TupleExprAst::TupleExprAst(const Tuple &t)
  : ExprAst(ExprAstType::Tuple)  { 
  add_child("ulist", nullptr); 
  add_child_data("value", t);
}

/*
TupleExprAst:: TupleExprAst(const Tuple &t, std::shared_ptr<ListExprAst> tlist)
  : ExprAst(t) { add_child("ulist", tlist); }
*/
std::any TupleExprAst::evaluate(SvlmLangContext *slc) {
  //std::shared_ptr<ListExprAst> l = std::any_cast<std::shared_ptr<ListExprAst>>(get_data());
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("ulist"));
  std::cout << "tuple eval\n"; l->print();
  if(!this->evaluated) {
    //std::vector<std::any> elist = move(std::any_cast<std::vector<std::any>>(l->evaluate(slc)));
    Tuple elist(move(std::any_cast<std::vector<std::any>>(l->evaluate(slc))));
    set_child_data("value", elist);
    evaluated = true;
    return elist;
  }
  return get_child_data("value");
};

bool TupleExprAst::assign(SvlmLangContext *slc, std::shared_ptr<ListExprAst> l, std::vector<std::any> rtva){
  if(l->get_member_size() != rtva.size()) return bool(false);

  for(int i=0; i<l->get_member_size(); i++) {
    std::shared_ptr<ExprAst> lexpr =  std::dynamic_pointer_cast<ExprAst>(l->get_member(i));

    if(lexpr->whoami() == ExprAstType::Gvar || lexpr->whoami() == ExprAstType::Lvar) continue;
   // left side == right hand side?
   // std::any a = lexpr->get_data(); std::cout << a  << " =? " <<  rtva[i] << "\n";
    if(lexpr->get_child_data("value").type() != rtva[i].type()) return bool(false);  // any type() not same

    try {
      Operand a = std::any_cast<Operand>(lexpr->get_child_data("value")); 
      Operand b = std::any_cast<Operand>(rtva[i]); 
      if(a != b) return bool(false);
    } catch(const std::bad_any_cast& e) {}
/*
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
*/
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
  std::cout << "tuple uniop\n";
  /*
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("ulist"));
 // auto ltva = std::any_cast<Tuple>(l->get_data()).get_data(); // rtva is a vector of any now

  std::cout << "tuple uniop1\n";
  auto rtva = std::any_cast<Tuple>(rl->get_child_data("value")).get_data(); // this is a problem. rtva is a vector of any now
  if(l==nullptr) std::cerr << "tpl l is nullptr\n";
  std::cout << "tuple uniop2\n";

  std::any op_print = op; 
  switch(op) {
  case ast_op::eql:  
  case ast_op::neql:    {
    Tuple a = std::any_cast<Tuple>(evaluate(slc));
    Tuple b = std::any_cast<Tuple>(rl->evaluate(slc));
    std::cout << "tuple n/eql uni_op\n";
    return a.bin_op(b, op);
  }
  case ast_op::assign:  
    return assign(slc, l, rtva);
  default: 
    std::cerr << "error operator! " << op_print << "\n"; 
    break;
  }
  return bool(false);
*/
return false;
} 


void TupleExprAst::codegen(std::vector<std::string> &code) const {};
void TupleExprAst::print() {
  //std::vector<std::any> elist = std::any_cast<std::vector<std::any>>(get_data());
  try {
    Tuple elist = std::any_cast<Tuple>(get_child_data("value"));
    elist.print();
  } catch(const std::bad_any_cast& e) {}
}

//----------------------------- decl expr
DeclExprAst::DeclExprAst(std::shared_ptr<IdentExprAst> l, DeclOpcodeAST doa) 
: ExprAst(ExprAstType::Decl) {
    add_child("left", l);
    add_child_data("value", doa);
};


std::any DeclExprAst::evaluate(SvlmLangContext *slc) {
  auto l = std::dynamic_pointer_cast<IdentExprAst>(get_child("left"));
  auto doa = std::any_cast<DeclOpcodeAST>(get_child_data("value"));
  full_symbol_t fst = slc->current_context;  
  switch(doa) {
  case DeclOpcodeAST::MODULE: 
    fst.smodule = l->name();
    break;
  default: break;
  }
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::smodule, fst));

  //std::cout << "k: "; for( auto k : keys) { std::cout << k << " "; } std::cout << "\n";

  slc->svlm_lang->context_tree->set_node(keys, std::string("module name"));
  slc->current_context = fst;
  return 0;
}
void DeclExprAst::codegen(std::vector<std::string> &code) const {
}
void DeclExprAst::print() { 
  std::shared_ptr<IdentExprAst> l = 
    std::dynamic_pointer_cast<IdentExprAst>(get_child("left"));
  switch (std::any_cast<DeclOpcodeAST>(get_child_data("value"))) {
  case DeclOpcodeAST::MODULE:  
    std::cout << "Module:" ; break;
  default: 
    std::cerr << "unknown decl!\n"; break;
  }

  l->print();// std::cout << "\n";
}


//----------------------------- Bin op

BinOpExprAst::BinOpExprAst 
( std::shared_ptr<ExprAst> l
, std::shared_ptr<ExprAst> r
, ast_op op
) : ExprAst(ExprAstType::BinOp) 
{ add_child("left", l);
  add_child("right", r);
  add_child_data("value", op);
  
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
  ast_op op = std::any_cast<ast_op>(ExprAst::get_child_data("value"));
  std::string oc;

  // std::cout <<"binop b4 left-";
  l->print();
  //print_data();
  switch(op) {
  case ast_op::noop:  oc="-noop-"; break;
  case ast_op::ast_default:  oc="default"; break;
  case ast_op::ast_else:  oc="else"; break;
  case ast_op::assign:  oc="="; break;
  case ast_op::plus:  oc="+"; break;
  case ast_op::minus: oc="-"; break;
  case ast_op::mul:   oc="*"; break;
  case ast_op::div:   oc="/"; break;
  case ast_op::eql:   oc="=="; break;
  case ast_op::neql:  oc="!="; break;
  case ast_op::gt:    oc=">"; break;
  case ast_op::lt:    oc="<"; break;
  case ast_op::lteq:  oc="<="; break;
  case ast_op::gteq:  oc=">="; break;
  case ast_op::and_:  oc="&&"; break;
  case ast_op::or_:  oc="||"; break;
  case ast_op::not_:  oc="!"; break;
  default: oc="out wrong type"; break; } 

  std::cout << oc ; 

  if(r!=nullptr) r->print();
  else std::cerr << "binop print right hand side null!\n";
  std::cout << " ";
}

std::any BinOpExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> l = 
    std::dynamic_pointer_cast<ExprAst>(get_child("left"));
  std::shared_ptr<ExprAst> r = 
    std::dynamic_pointer_cast<ExprAst>(get_child("right"));
  ast_op op = std::any_cast<ast_op>(ExprAst::get_child_data("value"));

  if(l ==nullptr) { std::cerr << "eval left handside is nullptr\n"; } 
  if(r ==nullptr) { std::cerr << "eval right handside r is nullptr\n"; }

  if((l->whoami() == ExprAstType::Gvar || l->whoami() == ExprAstType::Lvar)) {
    if(op == ast_op::assign) {
      // assignment operation for both local and global/module
      std::shared_ptr<AssignExprAst> al
        = std::dynamic_pointer_cast<AssignExprAst>(get_child("left"));

      std::any b = r->evaluate(slc); 
      al->assign(slc, b); 
      return b;
    } 

    try {
    Tuple a = std::any_cast<Tuple>(l->evaluate(slc)); 
    Tuple b = std::any_cast<Tuple>(r->evaluate(slc)); 
    return a.bin_op(b, op);
    } catch(const std::bad_any_cast& e) { }
  } 

  try {
    //std::cout << "trying tuple1\n";
    if(op != ast_op::assign) // to prevent var look up error 
      Tuple a = std::any_cast<Tuple>(l->evaluate(slc)); 
    Tuple b = std::any_cast<Tuple>(r->evaluate(slc)); 
    return l->uni_op(slc, r, op);
  } catch(const std::bad_any_cast& e) { }

  try {
    // std::cout << "trying operand\n"; std::any op_print  = op; std::cout << "op: " << op_print << "\n";
    Operand a = std::any_cast<Operand>(l->evaluate(slc)); 
    OperandExprAst oea(a);
    return oea.uni_op(slc, r, op);
  } catch(const std::bad_any_cast& e) { 
    //std::cerr << "operand cast error: " << e.what() << "\n"; 
  }

  return 0;
}


//-------------------- ListExprAst
ListExprAst::ListExprAst(std::any d)
  : ExprAst(ExprAstType::List) {
  add_child_data("value", d);
}

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

  for(int i=0; i<code_count && slc->svlm_lang->control_flow == ControlFlow::run ; i++ ) {
    e = std::dynamic_pointer_cast<ExprAst>(TreeNode::get_member(i));
    if(e==nullptr) { // could have been an empty  lists of newlines
      break;}
    // if e->whoami == func,  continue 
    result_list.push_back(e->evaluate(slc)); 
  }

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
  slc->svlm_lang->control_flow=ControlFlow::run;
  std::any output = e->evaluate(slc);
  //std::cout << "output: " << output << "\n";
  slc->last_line=false;
  return output;
}

//--------------------
FuncExprAst::FuncExprAst(
  std::string name, 
  std::vector<std::string> args, 
  std::shared_ptr<ListExprAst> body) : ExprAst(ExprAstType::Func) {
  
  add_child_data("value", name );
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

  slc->svlm_lang->push_control_flow();
  slc->svlm_lang->control_flow=ControlFlow::run;
  std::any result = l->evaluate(slc);
  std::any cf = slc->svlm_lang->control_flow;
  std::any rcf = slc->svlm_lang->pop_control_flow();
  //std::cout << "function return flow control is : " << cf << "\n";
  //std::cout << "function poped flow control is : " << rcf << "\n";


  return result;
}
void FuncExprAst::print() {
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("fbody"));
  auto func_name = std::any_cast<std::string>(get_child_data("value"));
  std::cout << "def " << func_name << " {\n";
  l->print();
  std::cout << "}";
}
void FuncExprAst::codegen(std::vector<std::string> &code) const {
}


//--------------------
CallExprAst::CallExprAst(std::string callee, std::shared_ptr<ListExprAst> args) : ExprAst(ExprAstType::Callee) {
  add_child("args", args ); // add to ast tree instead, when evaluate push these args to stack
  add_child_data("value", callee);
}
void CallExprAst::fcall_setup(SvlmLangContext *slc) { 
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  auto args_evaluated = move(std::any_cast<std::vector<std::any>>(l->evaluate(slc)));
  std::cout << "with arguments evaluated size: " << args_evaluated.size() << " list:\n"; 
  for(auto e : args_evaluated) { std::cout << e << "\n"; }
  slc->fcall_stack_setup(args_evaluated, std::any_cast<std::string>(get_child_data("value"))); // s

  //std::cout << "module: " << slc->current_context.smodule  << "\n";
  //std::cout << "calling: "; print_data(); std::cout << "\n";
}

std::any CallExprAst::evaluate(SvlmLangContext *slc) { 
  fcall_setup(slc);

  full_symbol_t fst = slc->current_context;  
  fst.mfunction = std::any_cast<std::string>(get_child_data("value"));
  std::vector<std::string> keys = move(slc->get_sym_key(key_tok_t::mfunction, fst));

  keys.push_back("fbody");
  std::shared_ptr<TreeNode> tn = slc->svlm_lang->context_tree->get_node(keys);
  if(tn==nullptr) {std::cerr << "can't find function!\n"; return 0;}
  std::shared_ptr<ExprAst> func = std::any_cast<std::shared_ptr<ExprAst>> ( tn->get_data());

  if(func!=nullptr) {
    //std::cout << "in caller print and eval func_body ptr: " << func<< "\n";

    slc->svlm_lang->push_control_flow();
    slc->svlm_lang->control_flow=ControlFlow::run;

    func->evaluate(slc);
    // func->print();
    // handle return value
    ControlFlow cf = slc->svlm_lang->pop_control_flow();        
    if(slc->svlm_lang->control_flow == ControlFlow::ast_return) {
      slc->svlm_lang->control_flow = cf;
      return slc->svlm_lang->fc_exp->evaluate(slc); // return the return 
    }


  } else {
    std::cerr << "function body is nullptr!\n";
  }
  return 0;

}

void CallExprAst::print() { 
  auto callee = std::any_cast<std::string>(get_child_data("value"));
  std::cout << "func "<<  callee;
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("args"));
  std::cout << "("; l->print(); std::cout << ")\n";
}
void CallExprAst::codegen(std::vector<std::string> &code) const {}


//--------------------  Case expr
CaseExprAst::CaseExprAst(
  std::shared_ptr<ExprAst> top, 
  std::shared_ptr<ListExprAst> body) 
  : ExprAst(ExprAstType::Case) {
  add_child("cbody", body);
  add_child_data("top", top);
  //std::cout << "CaseExprAst adding c body\n";
}

std::any CaseExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> top = std::any_cast<std::shared_ptr<ExprAst>>( get_child_data("top"));
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  if(l == nullptr) {
    std::cerr << "CaseExprAst match list items are null\n";
    return false;
  }

  for(int i=0; i<l->get_member_size(); i++)  {
    std::shared_ptr<CaseMatchExprAst> match_item = std::dynamic_pointer_cast<CaseMatchExprAst>(l->get(i));
    std::shared_ptr<ListExprAst> cbody = std::dynamic_pointer_cast<ListExprAst>(match_item->get_child("cbody"));

    if(match_item->match(top, slc) == true)
      return cbody->evaluate(slc);
  }
  return false;
}


void CaseExprAst::codegen(std::vector<std::string> &code) const {}
void CaseExprAst::print() { 
  std::shared_ptr<ExprAst> e = std::any_cast<std::shared_ptr<ExprAst>>( get_child_data("top"));
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  if(e==nullptr) { std::cerr << "Case is null!\n"; return; }
  if(l==nullptr) { std::cerr << "Case match list is null!\n"; return; }

  std::cout << "case "; e->print(); std::cout << " do\n";
  l->print();
}

//--------------------  Case match expr
void CaseMatchExprAst::print() {
  std::cout << "case match\n";
}

//--------------------  Case match Is expr
CaseMatchIsExprAst::CaseMatchIsExprAst(std::shared_ptr<ExprAst> match,
 std::shared_ptr<ListExprAst> body) : CaseMatchExprAst(ExprAstType::CaseMatchIs) {
  add_child("match", match);
  add_child("cbody", body);
}
std::any CaseMatchIsExprAst::evaluate(SvlmLangContext *slc) {
  return get_data();
}

void CaseMatchIsExprAst::codegen(std::vector<std::string> &code) const {}
void CaseMatchIsExprAst::print() { 
  auto m = std::dynamic_pointer_cast<ExprAst>(get_child("match"));
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  m->print();
  if(l != nullptr) l->print();
  else std::cout << " flow match cbody is null";
}

bool CaseMatchIsExprAst::match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) { 
  auto m = std::dynamic_pointer_cast<ExprAst>(get_child("match"));
  auto a = std::any_cast<Operand>(top->evaluate(slc));
  auto b = std::any_cast<Operand>(m->evaluate(slc));
  return a == b;
}

//--------------------  case match WHEN expr
CaseMatchWhenExprAst::CaseMatchWhenExprAst(
  std::shared_ptr<ExprAst> assign,
  std::shared_ptr<ExprAst> match,
 std::shared_ptr<ListExprAst> body) : CaseMatchExprAst(ExprAstType::CaseMatchWhen) {
  add_child("match", match);
  add_child("cbody", body);
  add_child("assign", assign);
}
std::any CaseMatchWhenExprAst::evaluate(SvlmLangContext *slc) {return get_data();}

void CaseMatchWhenExprAst::codegen(std::vector<std::string> &code) const {}
void CaseMatchWhenExprAst::print() { 
  std::shared_ptr<AssignExprAst> assign_expr = 
    std::any_cast<std::shared_ptr<AssignExprAst>>(get_child_data("assign"));
  std::cout << "is "; 
  assign_expr->print();
  auto m = std::dynamic_pointer_cast<ExprAst>(get_child("match"));
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  m->print_data();
  if(l != nullptr) l->print();
}

bool CaseMatchWhenExprAst::match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) { 
  std::shared_ptr<AssignExprAst> assign = 
    std::dynamic_pointer_cast<AssignExprAst>(get_child("assign"));
  assign->assign(slc, top->evaluate(slc));

  auto m = std::dynamic_pointer_cast<ExprAst>(get_child("match"));
  auto a = std::any_cast<Operand>(m->evaluate(slc));
  return a == Operand(true);
}

//--------------------  case match ELSE expr
CaseMatchElseExprAst::CaseMatchElseExprAst(std::shared_ptr<ListExprAst> body) 
  : CaseMatchExprAst(ExprAstType::CaseMatchElse) {
  add_child("cbody", body);
}
bool CaseMatchElseExprAst::match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) { 
  return true;
}
std::any CaseMatchElseExprAst::evaluate(SvlmLangContext *slc) {
  return get_data();
}
void CaseMatchElseExprAst::print() { 
  auto l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody"));
  std::cout << "else -> ";
  if(l != nullptr) l->print();
  else std::cout << " flow match cbody is null";
}

void CaseMatchElseExprAst::codegen(std::vector<std::string> &code) const {}


//--------------------  while expr
WhileExprAst::WhileExprAst
( std::shared_ptr<ExprAst> cond
, std::shared_ptr<ListExprAst> body
) : ExprAst(ExprAstType::While) {
  add_child("cbody", body);
  add_child("cond", cond);
}
std::any WhileExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  //std::shared_ptr<ExprAst> cond = std::any_cast<std::shared_ptr<ExprAst>>(get_data("")); 
  std::shared_ptr<ExprAst> cond  = std::dynamic_pointer_cast<ExprAst>(get_child("cond")); 
  std::shared_ptr<ListExprAst> l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody")); 
  std::any result;
  int code_count = l->get_member_size();

  std::cout  << "while eval!\n";

  slc->svlm_lang->push_control_flow();
  slc->svlm_lang->control_flow=ControlFlow::run;


  while( std::any_cast<Operand>(cond->evaluate(slc)) == Operand(true) 
      && slc->svlm_lang->control_flow == ControlFlow::run) {
    for(int i=0; i<code_count && slc->svlm_lang->control_flow == ControlFlow::run; i++ ) {
      e = std::dynamic_pointer_cast<ExprAst>(l->get_member(i));
      //if(e==nullptr)  break; // could have been an empty  lists of newlines
      if(e==nullptr)  continue; // could have been an empty  lists of newlines
      result = e->evaluate(slc);

      //std::any cf = slc->svlm_lang->control_flow ; std::cout << "---code[i]: " << i << " continue?  " << cf << "\n";

      if( slc->svlm_lang->control_flow  == ControlFlow::ast_break ||
          slc->svlm_lang->control_flow  == ControlFlow::ast_return
      ) break;
    }
    if(slc->svlm_lang->control_flow ==ControlFlow::ast_break ||
      slc->svlm_lang->control_flow ==ControlFlow::ast_return) {
      //std::cout << "ast eval cont -- i have go to now\n";
      break;
    }
  }

  ControlFlow cf = slc->svlm_lang->pop_control_flow();        
  if(slc->svlm_lang->control_flow != ControlFlow::ast_return) // if leave ast_return untouched
    slc->svlm_lang->control_flow = cf;

  return result;
}

void WhileExprAst::codegen(std::vector<std::string> &code) const {}

void WhileExprAst::print() {
  //std::shared_ptr<ExprAst> cond = std::any_cast<std::shared_ptr<ExprAst>>(get_data()); 
  std::shared_ptr<ExprAst>  cond = std::dynamic_pointer_cast<ExprAst>(get_child("cond")); 
  std::shared_ptr<ListExprAst> l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody")); 
  std::cout  << "while "; cond->print(); std::cout  << " do\n";
  l->print();
  std::cout  << "end";
}

//--------------------  reepat expr
RepeatExprAst::RepeatExprAst
( std::shared_ptr<ExprAst> cond
, std::shared_ptr<ListExprAst> body
) : ExprAst(ExprAstType::Repeat) {
  add_child("cbody", body);
  add_child("cond", cond);
}
std::any RepeatExprAst::evaluate(SvlmLangContext *slc) {
  std::shared_ptr<ExprAst> e;
  //std::shared_ptr<ExprAst> cond = std::any_cast<std::shared_ptr<ExprAst>>(get_data()); 
  std::shared_ptr<ExprAst>  cond = std::dynamic_pointer_cast<ExprAst>(get_child("cond")); 
  std::shared_ptr<ListExprAst> l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody")); 
  std::any result;
  int code_count = l->get_member_size();

  //std::cout  << "repeat eval!\n";

  slc->svlm_lang->push_control_flow();
  slc->svlm_lang->control_flow=ControlFlow::run;

  do {
    for(int i=0; i<code_count && slc->svlm_lang->control_flow == ControlFlow::run; i++ ) {
      e = std::dynamic_pointer_cast<ExprAst>(l->get_member(i));
      //if(e==nullptr)  break; // could have been an empty  lists of newlines
      if(e==nullptr)  continue; // could have been an empty  lists of newlines
      result = e->evaluate(slc);

      //std::any cf = slc->svlm_lang->control_flow ; std::cout << "---code[i]: " << i << " continue?  " << cf << "\n";

      if( slc->svlm_lang->control_flow  == ControlFlow::ast_break ||
          slc->svlm_lang->control_flow  == ControlFlow::ast_return
      ) break;
    }
    if(slc->svlm_lang->control_flow ==ControlFlow::ast_break ||
      slc->svlm_lang->control_flow ==ControlFlow::ast_return) {
      //std::cout << "ast eval cont -- i have go to now\n";
      break;
    }
  //} while( !std::any_cast<bool>(cond->evaluate(slc)) && slc->svlm_lang->control_flow == ControlFlow::run) ;
  } while( (std::any_cast<Operand>(cond->evaluate(slc))==Operand(false)) && slc->svlm_lang->control_flow == ControlFlow::run) ;

  ControlFlow cf = slc->svlm_lang->pop_control_flow();        
  if(slc->svlm_lang->control_flow != ControlFlow::ast_return) // if leave ast_return untouched
    slc->svlm_lang->control_flow = cf;

  return result;
}

void RepeatExprAst::codegen(std::vector<std::string> &code) const {}

void RepeatExprAst::print() {
  //std::shared_ptr<ExprAst> cond = std::any_cast<std::shared_ptr<ExprAst>>(get_data()); 
  std::shared_ptr<ExprAst> cond = std::dynamic_pointer_cast<ExprAst>(get_child("cond")); 
  std::shared_ptr<ListExprAst> l = std::dynamic_pointer_cast<ListExprAst>(get_child("cbody")); 
  std::cout  << "repeat "; 
  l->print();
  std::cout  << "until " ; cond->print() ; std::cout <<  " done\n";
}


#endif