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

void SvlmAst::run_evaluate() {
}
astexpr_u_ptr SvlmAst::evaluate_last_line() {
  return nullptr;
}
#define MOD "modules"
void SvlmAst::add_module(const Operand& n) {
  root.add_branch({MOD}, n);
}
void SvlmAst::add_code(const Operand&n, unique_ptr<AstExpr> c ) {
  cout << "adding mod!" << MOD << "\n";
  cout << "code: " << c << " type: " << c->get_type() << "\n";
  cout << "\n";
  auto nm = make_unique<AstMap>();
  nm->add(n, move(c));
  root.add_branch({CONTEXT_UNIV, MOD}, move(nm));
  //cout << "root: " << root << "\n";
}

AstBinOp::AstBinOp(std::unique_ptr<AstExpr> l, std::unique_ptr<AstExpr> r, AstOpCode op) {
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
  return  l.to_str() + o.to_str() +  r.to_str();
}