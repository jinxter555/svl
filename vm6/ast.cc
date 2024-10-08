#include "ast.hh"

//--------------------------------------------------------- 

void QueNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
void QueNode::print_m() const { cout << MapEntity::to_str() << "\n"; }

//--------------------------------------------------------- 
AstExpr::AstExpr(const OperandType &t) : Primordial(t) {}

//--------------------------------------------------------- 
AstOperand::AstOperand() : AstExpr(OperandType::ast_operand_t){}
int AstOperand::test_a()  {
  operand_u_ptr vptr1 = make_unique<Operand>("hello123");
  entity_u_ptr vptr2 = make_unique<ListEntity>();
  entity_u_ptr vptr4 = make_unique<MapEntity>();

  node.add(Operand("system2"), move(vptr2));
  node.add(string("hello1"), Operand("world1"));
  node.add(string("hello2"), "world2");
  node.add(string("hello23"), move(vptr4));
  node.add(string("hello24"), move(vptr4));
  cout << node.to_str() << "\n";;
  return 0;
}

astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr& ast_ctxt) { }