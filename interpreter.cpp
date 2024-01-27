#include "expr.hh"
#include "interpreter.hh"
#include "vm_svl.hh"

void Interpreter::add_expr(vector<Token>& infix){
  vector<Token> pe = Expr::ToPostfix(infix);
  vmsvl.add_expr(pe);
}
void Interpreter::add_expr(Expr& e){
  vector<Token> pe = Expr::ToPostfix(e.infix_);
  vmsvl.add_expr(pe);
}
void Interpreter::run() {
  vmsvl.run();
}
void Interpreter::cml_action(const string &act) {
  if(act == "\\print_stack") {
    vmsvl.print_stack();
    return;
  }
  if(act == "\\print_code") {
    vmsvl.print_code();
    return;
  }
}