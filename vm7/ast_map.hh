#pragma once
#include "ast.hh"
#include "operand.hh"

class AstMap: public AstExpr{
  friend class SvlmAst;
  friend class Tree;
protected:
  //unordered_map<string, Operand> map_;
  map<string, Operand> map_;
public:
  AstMap();

  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) override ;
  Operand& getv()  override final ;
  Operand& getv(const Operand &k)  override final ;
  Operand& getv(const string &k) ;

  //-------------------------------------------
  astexpr_u_ptr& get_u_ptr(const Operand &k) override final;
  astexpr_u_ptr& get_u_ptr(const string&) ;
  AstExpr *get_raw_ptr(const Operand &k) override final;
  AstExpr *get_raw_ptr(const string &k);
  //-------------------------------------------
  bool add(const AstExpr &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr)override final  ;  // for list
  //-------------------------------------------
  Operand& add(const Operand &k, const AstExpr& v, bool overwrite=false) override final ;
  Operand& add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false) override final ;

  Operand& add(const string &k, const AstExpr& v, bool overwrite=false) ;
  Operand& add(const string &k, astexpr_u_ptr&& vptr, bool overwrite=false);
  //-------------------------------------------
  bool set(const Operand &k, const AstExpr& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;

  bool set(const string &k, const AstExpr& v) ;
  bool set(const string &k, astexpr_u_ptr&& vptr) ;

  //-------------------------------------------
  bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) ;
  bool add_branch2(const vector<string> &keys, const Operand& operand, bool overwrite=false) ;
  //-------------------------------------------
  bool has_key(const Operand &k) ;
  bool has_key(const string &k) ;

  s_integer size() const override;
  Operand to_str() const override ;
  Operand get_type() const override;

  //AstList get_keys() const;
  vector<string> _get_keys() const override final;

  void print() const override;
};