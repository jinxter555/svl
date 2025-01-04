#pragma once
#include "lang.hh"
//#include "operand.hh"

class Operand;
class AstExpr;
using astexpr_u_ptr = unique_ptr<AstExpr>;
class AstExpr : public Primordial<AstExpr> {
public:
  AstExpr();
  AstExpr(const OperandType);
  virtual Operand evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const AstExpr& e);
  friend ostream& operator<<(ostream& os, const astexpr_u_ptr& vptr) ;
  //-------------------------------------------

};



