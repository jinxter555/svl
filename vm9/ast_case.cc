#include "ast_case.hh"
AstCase::AstCase(astnode_u_ptr top, astnode_u_ptr body) : AstExpr(OperandType::ast_case_t) {
  node["top"] = move(top);
  node["body"] = move(body);
}