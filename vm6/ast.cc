#include "ast.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType &t) : Primordial(t) {}

//--------------------------------------------------------- 
AstOperand::AstOperand() : AstExpr(OperandType::ast_operand_t){
}
AstOperand::AstOperand(const Operand& v)   {

}

astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr& ast_ctxt) { }