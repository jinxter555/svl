#include "svlm_ast.hh"


AstRepeat::AstRepeat(astnode_u_ptr cond, astnode_u_ptr body) : AstExpr(OperandType::ast_repeat_t) {
  node["cond"] = move(cond);
  node["body"] = move(body);
}

Operand AstRepeat::to_str() const {
  auto c = node["cond"]._to_str();
  auto b = node["body"]._to_str();
  return string("repeat ") +  c + " do " + b + " end";
}

Operand AstRepeat::evaluate(astnode_u_ptr &) {
  auto &c = node["cond"];
  auto &b = node["body"];

}