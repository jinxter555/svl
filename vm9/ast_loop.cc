#include "svlm_ast.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//----------------------------------------------------------------------- AstRepeat
AstRepeat::AstRepeat(astnode_u_ptr cond, astnode_u_ptr body) : AstExpr(OperandType::ast_repeat_t) {
  MYLOGGER(trace_function , string("AstRepeat::AstRepeat()") , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("cond: ") + AstPtr2Str(cond), SLOG_FUNC_INFO+9);
  MYLOGGER_MSG(trace_function, string("body: ") + AstPtr2Str(body), SLOG_FUNC_INFO+9);
  node["cond"] = move(cond);
  node["body"] = move(body);
}

Operand AstRepeat::to_str() const {
  auto c = node["cond"]._to_str();
  auto b = node["body"]._to_str();
  return string("repeat ") +  b + " until " + c + " done";
}

Operand AstRepeat::evaluate(astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , string("AstRepeat::evalaute()") , __func__, SLOG_FUNC_INFO);
  auto &c = node["cond"];
  auto &b = node["body"];
  do {// cout << "repeat!\n";
    auto rv=b.evaluate(ctxt);
  } while(c.evaluate(ctxt)==Operand(false));
  return Operand();
}

void AstRepeat::print() const {
  cout << to_str();
}

Operand AstRepeat::get_type() const { return OperandType::ast_repeat_t;}
OperandType AstRepeat::_get_type() const { return OperandType::ast_repeat_t;}

//----------------------------------------------------------------------- AstWhile
AstWhile::AstWhile(astnode_u_ptr cond, astnode_u_ptr body) : AstExpr(OperandType::ast_while_t) {
  MYLOGGER(trace_function , string("AstWhile::AstWhile()") , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("cond: ") + AstPtr2Str(cond), SLOG_FUNC_INFO+9);
  MYLOGGER_MSG(trace_function, string("body: ") + AstPtr2Str(body), SLOG_FUNC_INFO+9);
  node["cond"] = move(cond);
  node["body"] = move(body);
}

Operand AstWhile::to_str() const {
  auto c = node["cond"]._to_str();
  auto b = node["body"]._to_str();
  return string("while") +  c + " do " + c + " end";
}

Operand AstWhile::evaluate(astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , string("AstWhile::evalaute()") , __func__, SLOG_FUNC_INFO);
  auto &c = node["cond"];
  auto &b = node["body"];
  while(c.evaluate(ctxt)==Operand(true)) {
    auto rv=b.evaluate(ctxt);
  }
  return Operand();
}

void AstWhile::print() const {
  cout << to_str();
}

Operand AstWhile::get_type() const { return OperandType::ast_while_t;}
OperandType AstWhile::_get_type() const { return OperandType::ast_while_t;}