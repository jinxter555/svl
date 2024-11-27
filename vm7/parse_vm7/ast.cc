#include "ast.hh"
#include "operand.hh"

//--------------------------------------------------------- 

//--------------------------------------------------------- 

AstExpr::AstExpr() : Primordial(OperandType::nil_t) {}
AstExpr::AstExpr(const OperandType t) : Primordial(t) {}
//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const AstExpr& e) {
//  if(e == nil_operand)  cerr << "AstExpr is nil"; else e.print();
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const astexpr_u_ptr& ptr) {
  //cout << "ptr:";
  if(ptr==nullptr) { cout << "astexpr_u_ptr is null\n"; } 
  else ptr->print();
  return os;
}