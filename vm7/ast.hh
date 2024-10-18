#pragma once
#include "lang.hh"

class AstExpr : public Primordial<AstExpr> {
protected:
  astexpr_u_ptr nil_ast_ptr=nullptr;
public:
  AstExpr();
  AstExpr(const OperandType);
  virtual astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  

  virtual bool add(const Operand &v) =0;  // for list
  virtual bool add(astexpr_u_ptr &&vptr) =0;  // for list

  //-------------------------------------------
  virtual bool add(const Operand &k, const Operand& v)=0;
  virtual bool add(const Operand &k, astexpr_u_ptr&& vptr)=0;

  virtual bool set(const Operand &k, const Operand& v) = 0;
  virtual bool set(const Operand &k, astexpr_u_ptr&& vptr) = 0;

  virtual const Operand& getv(const Operand &k) = 0;
  virtual const astexpr_u_ptr& getptr(const Operand &k) = 0;



  //-------------------------------------------
  //friend ostream& operator<<(ostream& os, const Entity& e);
  //friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------

};

class AstList: public AstExpr{
protected:
  vector<astexpr_u_ptr> list_;
public:
  AstList();
  AstList(const AstList& l);
  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) override ;
  const Operand& getv(const Operand &k)  override final ;
  const astexpr_u_ptr& getptr(const Operand &k) override final;

  //-------------------------------------------
  bool add(const Operand &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr)override final  ;  // for list
  //-------------------------------------------
  bool add(const Operand &k, const Operand& v) override final ;
  bool add(const Operand &k, astexpr_u_ptr&& vptr) override final ;
  //-------------------------------------------
  bool set(const Operand &k, const Operand& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;


  s_integer size() const;
  Operand to_str() const override ;
  Operand get_type() const override;

  void print() const override;


};

class AstMap: public AstExpr{
protected:
  unordered_map<string, astexpr_u_ptr> map_;
public:
  AstMap();

  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) override ;
  const Operand& getv(const Operand &k)  override final ;
  const astexpr_u_ptr& getptr(const Operand &k) override final;

  //-------------------------------------------
  bool add(const Operand &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr)override final  ;  // for list
  //-------------------------------------------
  bool add(const Operand &k, const Operand& v) override final ;
  bool add(const Operand &k, astexpr_u_ptr&& vptr) override final ;
  //-------------------------------------------
  bool set(const Operand &k, const Operand& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;


};