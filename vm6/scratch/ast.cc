#include "ast.hh"
#include "map_entity.hh"
#include "operand_entity.hh"
//-------------------------------------- Ast Node


AstExpr::AstExpr(const Operand &v) { node = make_unique<OperandEntity>(v); }
AstExpr::AstExpr(const OperandEntity &v) { node = make_unique<OperandEntity>(v); }
AstExpr::AstExpr(const ListEntity &v) { node = make_unique<ListEntity>(v); }
AstExpr::AstExpr(const MapEntity &v) { node = make_unique<MapEntity>(v); }

//-------------------------------------- Ast Operand
AstOperand::AstOperand(const Operand &v) {
  node = make_unique<OperandEntity>(v);
}

void AstOperand::print() const {
}
const astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr &ast_ctxt) {
  //return this;
}
//-------------------------------------- Ast Root