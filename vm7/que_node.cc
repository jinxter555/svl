#include "que_node.hh"

QueNode nil_qnode;

std::ostream& operator << (std::ostream& out, vector<string> vs) {
  std::cout << "keys: "; for(auto k: vs) { std::cout << k << ","; } std::cout << "\n\n";
  return out;
}

astexpr_u_ptr QueNode::clone() {
  list_u_ptr nl = make_unique<AstList>();
  nl->add(AstList::clone());
  nl->add(AstMap::clone());
  return nl;
}

QueNode::QueNode() {
  AstList::type_ = OperandType::quenode_t;
  AstMap::type_ = OperandType::quenode_t;
}


//--------------------------------------------------------- 
void QueNode::print_l() const { cout << AstList::to_str() << "\n"; }
void QueNode::print_m() const { cout << AstMap::to_str() << "\n"; }