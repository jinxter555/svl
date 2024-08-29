#include "tuple.hh"
#include "operand.hh"
#include <stdexcept>

std::ostream& operator << (std::ostream& out, std::any& a) ;

Tuple::Tuple(const Tuple& other) {
  for(auto e: other.tlist ) {
    tlist.push_back(e);
  }
}

std::vector<std::any> Tuple::get_data() const {
  return tlist;
}

void Tuple::print() {
  int i;
  std::cout << "{";
  for(i=0; i<tlist.size()-1; i++) { 
    std::cout <<  tlist[i] << ", "; //Operand v = std::any_cast<Operand>(tlist[i]);
  }
  std::cout <<  tlist[i] << "}";    //std::cout <<  std::any_cast<Operand>(tlist[i]) << "}";
}

bool Tuple::operator!=(const Tuple& other) const{
  return !(*this == other);
}

bool Tuple::operator==(const Tuple& other) const{
  int i;
  if(tlist.size()!= other.tlist.size()) return false;
  for(i=0; i<tlist.size(); i++) {
    try {
    Operand a = std::any_cast<Operand>(tlist[i]);
    Operand b = std::any_cast<Operand>(other.tlist[i]);
    if(a!=b) return false; 
    }catch(const std::bad_any_cast& e) {}
  }
  return true;
}



bool Tuple::opfunc(const Tuple& other, ast_op op) const {
  std::cout << "tuple bin op\n";
  switch(op) {
    case ast_op::eql: {
    //  std::cout << "eql\n";
      return *this == other;
    }
    case ast_op::neql: {
     // std::cout << "neql\n";
      return !(*this == other);
    }
    default: {
      std::cerr << "unknown tuple operation!\n";
      return false;
    }
  }
}