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
  AstList::type_ = OperandType::list_t;
  AstMap::type_ = OperandType::map_t;
}


//--------------------------------------------------------- 
void QueNode::print_l() const { 
  cout << AstList::to_str(); 
}
void QueNode::print_m() const { cout << AstMap::to_str(); }
void QueNode::print() const { 
  if(map_.size()!=0 ) print_m(); 
  if(list_.size()!=0 ) print_l(); 
}
ostream& operator<<(ostream& os, const QueNode& e) {
  e.print();
  return os;
}