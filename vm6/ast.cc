#include "ast.hh"

void AstNode::add(const OperandEntity& v) { 
  ListEntity::add(v);
}


entity_u_ptr& AstNode::operator[] (int index) { return ListEntity::members[index]; }

/*
const entity_u_ptr& AstNode::operator[] (int index) const {
  return ListEntity::members[index];
}
*/

//--------------------------------------------------------- 
entity_u_ptr& AstNode::operator[] (const string &k) {
  return MapEntity::children[k];
}

// assignment
/*
const entity_u_ptr& AstNode::operator[] (const string &k) const {
  return MapEntity::children[k];
}
*/
//--------------------------------------------------------- 

void AstNode::print_l() const { cout << ListEntity::to_str() << "\n"; }
void AstNode::print_m() const { cout << MapEntity::to_str() << "\n"; }
