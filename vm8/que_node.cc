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
  type_ = OperandType::quenode_t;
  AstList::type_ = OperandType::list_t;
  AstMap::type_ = OperandType::map_t;
}


//--------------------------------------------------------- 
void QueNode::print_l() const { 
  //cout << AstList::to_str(); 
  //cout << AstList::get_type() << "\n";
  AstList::print();
}
void QueNode::print_m() const { 
  //cout << AstMap::to_str(); 
  //cout << AstMap::get_type() << "\n";
  AstMap::print();
}
void QueNode::print() const { 
  //cout << AstList::get_type() << "\n";
  //cout << AstMap::get_type() << "\n";
  if(map_.size()!=0 ) print_m(); 
  if(list_.size()!=0 ) print_l(); 
}
ostream& operator<<(ostream& os, const QueNode& e) {
  e.print();
  return os;
}