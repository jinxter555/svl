#pragma once
#include "lang.hh"

using astexpr_u_ptr = unique_ptr<AstExpr>;
class AstExpr : public Primordial<AstExpr> {
  friend class Operand;
  friend class AstList;
  friend class AstMap;
  friend class QueNode;
protected:
  astexpr_u_ptr nil_ast_ptr=nullptr;

public:
  AstExpr();
  AstExpr(const OperandType);
  //virtual Operand evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  virtual Operand evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  virtual Operand opfunc(const AstExpr&, AstOpCode op) =0;
  

  virtual bool add(const AstExpr &v) =0;  // for list
  virtual bool add(astexpr_u_ptr &&vptr) =0;  // for list

  virtual Operand clone_val() const=0;
  virtual astexpr_u_ptr clone_usu() =0;
  //-------------------------------------------
  virtual Operand& operator[] (const Operand& k) =0;
  virtual const Operand& operator[] (const Operand &k) const =0;

  //-------------------------------------------
  virtual bool is_current_nil() const=0;
  virtual bool is_nil() const=0;

  virtual bool add(const Operand &k, const AstExpr& v, bool overwrite=false)=0;

  virtual bool add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false)=0;

  virtual bool set(const Operand &k, const AstExpr& v) = 0;
  virtual bool set(const Operand &k, astexpr_u_ptr&& vptr) = 0;

  virtual const Operand& _get_value() const = 0;
  virtual operand_variant_t _get_variant() const=0 ;
  //-------------------------------------------
  virtual const Operand* _get_operand_ptr() const = 0;
  virtual const AstList* _get_list_ptr() const = 0;
  virtual const AstMap* _get_map_ptr() const = 0;

  //-------------------------------------------

  //virtual Operand& getv_nc() = 0;

  virtual Operand& getv(const Operand &k) = 0;
  //virtual Operand& getv(const string &k) = 0;
  virtual vector<string> _get_keys() const =0;
  virtual s_integer _get_int() const =0;

  virtual Operand& back() = 0;
  virtual Operand& front() = 0;

  virtual const astexpr_u_ptr& get_u_ptr(const Operand &k) const = 0;
  virtual astexpr_u_ptr& get_u_ptr_nc(const Operand &k) = 0;

  virtual const astexpr_u_ptr& get_u_ptr() const = 0;
  virtual astexpr_u_ptr& get_u_ptr_nc() =0 ; // non constant
  virtual astexpr_s_ptr get_s_ptr() = 0;
  //virtual astexpr_s_ptr get_s_ptr_nc() = 0;

  virtual astexpr_ptr get_raw_ptr(const Operand &k) const=0;
  virtual astexpr_ptr get_raw_ptr() const=0;

  //-------------------------------------------
  virtual bool operator==(const AstExpr&) const=0;
  virtual bool operator==(const astexpr_ptr) const=0;

  virtual bool operator!=(const AstExpr&) const=0;
  virtual bool cmp_eql(const AstExpr&) const=0;
  //virtual bool cmp_eql(const OperandVariant&) const=0;
  //-------------------------------------------
  //virtual Operand& get_branch(const Operand&k) =0 ;
  //virtual bool add_branch(const Operand&k, const AstExpr& e, bool overwrite=false)=0;
  virtual bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) =0;
  virtual bool add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite=false) =0;
  virtual Operand& get_branch(const vector<string> &keys) =0;

  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const AstExpr& e);
  friend ostream& operator<<(ostream& os, const astexpr_u_ptr& vptr) ;
  //-------------------------------------------

};



