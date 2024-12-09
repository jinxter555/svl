#pragma once
#include "ast.hh"
#include "operand.hh"

class AstMap: public AstExpr{
  friend class SvlmAst;
  friend class Tree;
protected:
  //unordered_map<string, Operand> map_;
  Operand myself;
  map<string, Operand> map_;
public:
  AstMap();

  astexpr_u_ptr clone() const override; 
  Operand evaluate(astexpr_u_ptr& ast_ctxt) override ;
  Operand& getv()  override ;
  Operand& getv(const Operand &k)  override final ;
  Operand& getv(const string &k) ;

  Operand& back() override final;
  Operand& front() override final;

  Operand clone_val() const override final;
  Operand& operator[] (const Operand& k) override final;
  const Operand& operator[] (const Operand &k) const override final;

  //-------------------------------------------
  const astexpr_u_ptr& get_u_ptr(const Operand &k) const override final;
  const astexpr_u_ptr& get_u_ptr(const string&) const ;
  astexpr_u_ptr& get_u_ptr_nc(const Operand &k) override final;

  const astexpr_u_ptr& get_u_ptr() const override final;
  astexpr_u_ptr& get_u_ptr_nc() override final; // non constant
  astexpr_s_ptr get_s_ptr() override final;
  //astexpr_s_ptr get_s_ptr_nc() override final;

  AstExpr *get_raw_ptr(const Operand &k) const override final;
  AstExpr *get_raw_ptr(const string &k) const ;
  AstExpr *get_raw_ptr() const override final;
  //-------------------------------------------
  bool add(const AstExpr &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr)override final  ;  // for list
  //-------------------------------------------
  bool add(const Operand &k, const AstExpr& v, bool overwrite=false) override final ;
  bool add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false) override final ;

  bool add(const string &k, const AstExpr& v, bool overwrite=false) ;
  bool add(const string &k, astexpr_u_ptr&& vptr, bool overwrite=false);
  //-------------------------------------------
  bool set(const Operand &k, const AstExpr& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;

  bool set(const string &k, const AstExpr& v) ;
  bool set(const string &k, astexpr_u_ptr&& vptr) ;

  //-------------------------------------------
  bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) override final;
  bool add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite=false) override final;
  Operand& get_branch(const vector<string> &keys) override final;
  Operand& get_branch2(const vector<string> &keys) ;
  //-------------------------------------------
  bool has_key(const Operand &k) const;
  bool has_key(const string &k) const ;

  s_integer size() const override;
  Operand to_str() const override ;
  Operand get_type() const override;
  OperandType _get_type() const override;

  //AstList get_keys() const;
  vector<string> _get_keys() const override final;

  void print() const override;
};