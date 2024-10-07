#include "ast.hh"

//--------------------------------------------------------- 
//entity_u_ptr& AstNode::operator[] (int index) { return ListEntity::members[index]; }
//const entity_u_ptr& AstNode::operator[] (int index) const { return ListEntity::members[index]; }
//--------------------------------------------------------- 
//entity_u_ptr& AstNode::operator[] (const string &k) { return MapEntity::children[k]; }
// const entity_u_ptr& AstNode::operator[] (const string &k) const { return MapEntity::children[k]; }
//--------------------------------------------------------- 

//void AstNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
//void AstNode::print_m() const { cout << MapEntity::to_str() << "\n"; }

  int AstExpr::a()  {
    entity_u_ptr vptr1 = make_unique<Operand>("hello123");
    entity_u_ptr vptr2 = make_unique<ListEntity>();
    entity_u_ptr vptr3 = make_unique<AstNode>();
    entity_u_ptr vptr4 = make_unique<MapEntity>();

    add(Operand("system1"), move(vptr1));
    add(Operand("system2"), move(vptr2));
    add(string("hello1"), Operand("world1"));
    add(string("hello2"), "world2");
    add(string("hello23"), move(vptr3));
    add(string("hello24"), move(vptr4));
    cout << to_str() << "\n";;
    return 0;
  }

AstOperand::AstOperand() {};
AstOperand::AstOperand(const Operand&v) {
   add("value", 
   make_unique<Operand>(v)
   );
}
astexpr_u_ptr& AstOperand::evaluate(astexpr_u_ptr& ast_ctxt) {
  auto e = AstNode::get("value")._get_operand();

}