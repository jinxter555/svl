#include "que_node.hh"


void Tree::print() const {
  cout << root;
}

//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const Tree& e) {
  e.print();
  return os;
}