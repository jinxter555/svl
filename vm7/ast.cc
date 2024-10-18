#include "ast.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType t) : Primordial(t) {}
//--------------------------------------------------------- 
