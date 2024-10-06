#include "ast.hh"

//--------------------------------------------------------- 
//entity_u_ptr& AstNode::operator[] (int index) { return ListEntity::members[index]; }
//const entity_u_ptr& AstNode::operator[] (int index) const { return ListEntity::members[index]; }
//--------------------------------------------------------- 
entity_u_ptr& AstNode::operator[] (const string &k) { return MapEntity::children[k]; }
// const entity_u_ptr& AstNode::operator[] (const string &k) const { return MapEntity::children[k]; }
//--------------------------------------------------------- 

//void AstNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
//void AstNode::print_m() const { cout << MapEntity::to_str() << "\n"; }

  int AstExpr::a()  {
    entity_u_ptr vptr1 = make_unique<OperandEntity>(Operand("hello123"));
    entity_u_ptr vptr2 = make_unique<ListEntity>();
    entity_u_ptr vptr3 = make_unique<AstNode>();
    //AstNode::MapEntity::add(Operand("k2"), vptr1->clone());
    //AstNode::MapEntity::add(OperandEntity("k2"), vptr1->clone());
    add(Operand("system"), vptr1);
    add("hello1", Operand("world1"));
    add("hello2", "world2");
    cout << to_str() << "\n";;
    return 0;
  }