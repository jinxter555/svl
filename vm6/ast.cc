#include "ast.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType &t) : Primordial(t) {}

//--------------------------------------------------------- 
AstOperand::AstOperand() : AstExpr(OperandType::ast_operand_t){
}
AstOperand::AstOperand(const OperandVariant& v) : operand(v)  {}
AstOperand::AstOperand(const Operand& v) : operand(v.clone_val()) {
}

astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr& ast_ctxt) { }