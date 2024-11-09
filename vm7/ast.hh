#pragma once
#include "lang.hh"

using astexpr_u_ptr = unique_ptr<AstExpr>;
class AstExpr : public Primordial<AstExpr> {
  friend class Operand;
  friend class AstList;
  friend class QueNode;
protected:
  astexpr_u_ptr nil_ast_ptr=nullptr;

  virtual AstExpr *get_raw_ptr(const Operand &k)=0;
public:
  AstExpr();
  AstExpr(const OperandType);
  virtual astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  

  virtual bool add(const AstExpr &v) =0;  // for list
  virtual bool add(astexpr_u_ptr &&vptr) =0;  // for list

  //-------------------------------------------
  virtual bool add(const Operand &k, const AstExpr& v, bool overwrite=false)=0;

  virtual bool add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false)=0;

  virtual bool set(const Operand &k, const AstExpr& v) = 0;
  virtual bool set(const Operand &k, astexpr_u_ptr&& vptr) = 0;

  virtual Operand& getv() = 0;
  virtual Operand& getv(const Operand &k) = 0;
  virtual astexpr_u_ptr& get_u_ptr(const Operand &k) = 0;
  virtual vector<string> _get_keys() const =0;

  //-------------------------------------------
  //virtual Operand& get_branch(const Operand&k) =0 ;
  //virtual bool add_branch(const Operand&k, const AstExpr& e, bool overwrite=false)=0;
  virtual bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) ;
  virtual bool add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite=false) ;
  virtual Operand& get_branch(const vector<string> &keys) ;

  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const AstExpr& e);
  friend ostream& operator<<(ostream& os, const astexpr_u_ptr& vptr) ;
  //-------------------------------------------

};



