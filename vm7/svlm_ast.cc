#include "svlm_ast.hh"

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