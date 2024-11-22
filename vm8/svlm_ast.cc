#include "svlm_ast.hh"
#include "svlm_interactive.hh"

/*
#define rl_loc "readline", "commands"

void SvlmAst::add_readline_cmds(const string&cmd) {
  root.add_branch({rl_loc, cmd}, 1l);
}
vector<string> SvlmAst::get_readline_cmds(const string& cmd) {
  auto &v = root.get_branch({rl_loc});
}
*/

astexpr_u_ptr SvlmAst::evaluate_last_line() {
  return nullptr;
}
#define MOD "modules"
void SvlmAst::add_module(const Operand& n, astexpr_u_ptr clist) {
  s_integer i, s=clist->size();
  auto nm = make_unique<AstMap>();
  vector<string> func_keys = {CONTEXT_UNIV, MOD, "function"};
  for(i=0; i < s; i++) {
    auto &nan = clist->getv(i);
    cout << "nan" << i << ":" << nan << "\n";
    switch(nan.get_type()._get_type()) {
    case OperandType::ast_func_t: {
      auto func_name = nan.getv("name")._to_str();
      vector<string> k = func_keys;
      cout << "ast_func_t!\n";
      k.push_back(func_name);
      root.add_branch(k, move(nm));
      }
    default:
      cerr << "unknown nan type!\n";
    }
  }
}
void SvlmAst::add_code(const Operand&n, unique_ptr<AstExpr> c ) {
  cout << "adding mod!" << MOD << "\n";
  cout << "code: " << c << " type: " << c->get_type() << "\n";
  cout << "\n";
  auto nm = make_unique<AstMap>();
  nm->add(n, move(c));
  root.add_branch({CONTEXT_UNIV, MOD}, move(nm));

  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "mname"});
  cout << "after adding mod!" << MOD << n << "\n";
  l.print();
  cout << "\n";
}

void SvlmAst::run_evaluate() {
  cout << "run eval!\n";
  auto& l = root.get_branch({CONTEXT_UNIV, MOD, "mname"});
  auto &c = l.get_u_ptr();
  
  l.print();
  cout << "code list type: " <<  l.get_type() << "\n";
  cout << "size: " <<  l.size() << "\n";

  for(s_integer i=0; i<l.size();  i++){
    auto &c = l[i];
    cout << "c: " << c << "\n";
    cout << "c::getype " << c->get_type() << "\n";
    cout << "c::evaluate " << c->evaluate(c) << "\n";
  }
}
//-----------------------------------------------------------------------

AstBinOp::AstBinOp(std::unique_ptr<AstExpr> l, std::unique_ptr<AstExpr> r, AstOpCode op) 
 // : AstExpr(OperandType::ast_binop_t) 
  {
  add(string("left"), move(l));
  add(string("right"), move(r));
  add(string("op"), Operand(op));
}
void AstBinOp::print() {
  cout << "AstBinOp:\n";
  cout << to_str();
}
Operand AstBinOp::to_str() const { 
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto &o = (*this)["op"];
  return  l->to_str() + o->to_str() +  r->to_str();
}
astexpr_u_ptr AstBinOp::evaluate(astexpr_u_ptr& ast_ctxt) {
  cout << "in astbinop eval!\n";
  auto &l = (*this)["left"];
  auto &r = (*this)["right"];
  auto &o = (*this)["op"]->getv();
  cout << "opcode" << o.get_opcode() << "\n";
  cout << "str: " << l->to_str() + o.to_str() +  r->to_str() << "\n";

  return make_unique<Operand>(l->opfunc(r, o._get_opcode()));
}


AstFunc::AstFunc(const Operand &n, astexpr_u_ptr c) {
  name = n._to_str();
  add(string("name"), n);
  add(string("code"), move(c));
}

astexpr_u_ptr AstFunc::evaluate(astexpr_u_ptr& ast_ctxt) {
  auto &l = map_["code"];
  cout << "in func eval!\n";
  return l->evaluate(ast_ctxt);
}
Operand AstFunc::to_str() const {
  return string("func: ") + name;
}
Operand AstFunc::get_type() const { return OperandType::ast_func_t;}