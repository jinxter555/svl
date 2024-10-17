#include "ast.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType &t) : Primordial(t) {}

//--------------------------------------------------------- 
AstOperand::AstOperand() : AstExpr(OperandType::ast_operand_t){
}
AstOperand::AstOperand(const OperandVariant v) : value_(v)  {}
AstOperand::AstOperand(const OperandVariant& v) : value_(v)  {}
AstOperand::AstOperand(const Operand& v) : value_(v.clone_val()) {}

astexpr_u_ptr AstOperand::clone() const {return make_unique<AstOperand>(value_);};
Operand AstOperand::to_str() const { return value_.to_str();}
Operand AstOperand::get_type() const { return type_; };
void    AstOperand::print() const {
  cout << value_;
}

astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr& ast_ctxt) { }



//----------------------------------------------------------------------------------------------------------------- 
AstBinOp::AstBinOp(astexpr_u_ptr&& l, astexpr_u_ptr&& r, AstOpCode op) {
   MapEntity::add(Operand("left"), Operand(l));

}