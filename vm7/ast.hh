#pragma once
#include "lang.hh"

class Operand;
using astexpr_u_ptr = unique_ptr<AstExpr>;
class AstExpr : public Primordial<AstExpr> {
  friend class Operand;
protected:
  astexpr_u_ptr nil_ast_ptr=nullptr;
public:
  AstExpr();
  AstExpr(const OperandType);
  virtual astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  

  virtual bool add(const AstExpr &v) =0;  // for list
  virtual bool add(astexpr_u_ptr &&vptr) =0;  // for list

  //-------------------------------------------
  virtual bool add(const Operand &k, const AstExpr& v)=0;
  virtual bool add(const Operand &k, astexpr_u_ptr&& vptr)=0;

  virtual bool set(const Operand &k, const Operand& v) = 0;
  virtual bool set(const Operand &k, astexpr_u_ptr&& vptr) = 0;

  virtual const Operand& getv() = 0;
  virtual const Operand& getv(const Operand &k) = 0;
  virtual const astexpr_u_ptr& getptr(const Operand &k) = 0;

  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const AstExpr& e);
  friend ostream& operator<<(ostream& os, const astexpr_u_ptr& vptr) ;
  //-------------------------------------------

};



