#include "ast.hh"

class AstList: public AstExpr{
protected:
  vector<Operand> list_;
public:
  AstList();
  AstList(const AstList& l);
  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) override ;
  Operand& getv()  override final ;
  Operand& getv(const Operand &k)  override final ;
  Operand& getv(int i)  ;
  astexpr_u_ptr& get_u_ptr(const Operand &k) override final;
  astexpr_u_ptr& get_u_ptr(int i) ;

  AstExpr *get_raw_ptr(const Operand &k) override final;
  AstExpr *get_raw_ptr(int i);

  //-------------------------------------------
  bool add(const AstExpr &v) override final ;  // for list
  bool add(astexpr_u_ptr &&vptr)override final  ;  // for list
  //-------------------------------------------
  bool add(const Operand &k, const AstExpr& v, bool overwrite=false) override final ;
  bool add(const Operand &k, astexpr_u_ptr&& vptr, bool overwrite=false) override final ;
  //-------------------------------------------
  bool set(const Operand &k, const AstExpr& v) override final ;
  bool set(const Operand &k, astexpr_u_ptr&& vptr) override final ;

  //-------------------------------------------
  vector<string> _get_keys() const override final;

  s_integer size() const override;
  Operand to_str() const override ;
  Operand get_type() const override;

  void print() const override;
};