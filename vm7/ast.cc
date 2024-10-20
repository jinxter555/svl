#include "ast.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType t) : Primordial(t) {}
//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const AstExpr& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const astexpr_u_ptr& ptr) {
  //cout << "ptr:";
  ptr->print();
  return os;
}
