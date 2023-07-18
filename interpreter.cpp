#include "expr.hh"
#include "interpreter.hh"
#include "vm_svl.hh"

void Interpreter::vmsvl_add_expr(vector<Token>& infix){
  vector<Token> pe = Expr::ToPostfix(infix);
  vmsvl.add_expr(pe);
}
void Interpreter::vmsvl_add_expr(Expr& e){
  vector<Token> pe = Expr::ToPostfix(e.infix_);
  vmsvl.add_expr(pe);
}
void Interpreter::run() {
  vmsvl.run();
}