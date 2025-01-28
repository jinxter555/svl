#include "operand_vars.hh"
#include "svlm_ast.hh"

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//----------------------------------------------------------------------- AstCase
AstCase::AstCase(astnode_u_ptr top, astnode_u_ptr body) : AstExpr(OperandType::ast_case_t) {
  MYLOGGER(trace_function , string("AstCase::AstCase()") , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("top: ") + AstPtr2Str(top), SLOG_FUNC_INFO+9);
  MYLOGGER_MSG(trace_function, string("body: ") + AstPtr2Str(body), SLOG_FUNC_INFO+9);
  node["top"] = move(top);
  node["body"] = move(body);
}

Operand AstCase::to_str() const {
  auto t = node["top"]._to_str();
  auto b = node["body"]._to_str();
  return string("case") +  t + " do " + b + " end";
}

Operand AstCase::evaluate(astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , string("AstCase::evalaute()") , __func__, SLOG_FUNC_INFO);
  auto &top = node["top"].get_u_ptr();
  auto blist = node["body"].get_list_ptr_nc();

  for(s_integer i=0; i<blist->size(); i++) {
    auto match_item =(AstCaseMatch*) blist[i]._vrptr();
    if(match_item->match(top, ctxt )) {
      return match_item->evaluate(ctxt);
    }
  }
  return nil;
}

void AstCase::print() const {
  cout << to_str();
}

Operand AstCase::get_type() const { return OperandType::ast_case_t;}
OperandType AstCase::_get_type() const { return OperandType::ast_case_t;}

//----------------------------------------------------------------------- AstCaseMatchIs
AstCaseMatchIs::AstCaseMatchIs(astnode_u_ptr is_, astnode_u_ptr body) 
: AstCaseMatch(OperandType::ast_case_match_is_t ) {
  MYLOGGER(trace_function , string("AstCaseMatchIs::CaseMatchIs()") , __func__, SLOG_FUNC_INFO);

  node["is"] = move(is_);
  node["body"] = move(body);
}

void AstCaseMatchIs::print() const {
  cout << to_str();
}
Operand AstCaseMatchIs::to_str() const {
  auto is_ = node["is"]._to_str();
  auto b = node["body"]._to_str();
  return string("is ") +  is_ + " -> " + b ;
}
Operand AstCaseMatchIs::get_type() const { return OperandType::ast_case_match_is_t;}
OperandType AstCaseMatchIs::_get_type() const { return OperandType::ast_case_match_is_t;}

bool AstCaseMatchIs::match(const astnode_u_ptr& top, astnode_u_ptr &ctxt) {
  MYLOGGER(trace_function , string("AstCaseMatchIs::match()") , __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("top: ") + AstPtr2Str(top), SLOG_FUNC_INFO+9);

  auto &is_ = node["is"];
  auto a = top->evaluate(ctxt);
  auto b = is_.evaluate(ctxt);
  return a == b;
}

Operand AstCaseMatchIs::evaluate(astnode_u_ptr &ctxt) {
  return AstMap::evaluate(ctxt);
}