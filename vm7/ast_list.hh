#include "ast.hh"
#include "operand.hh"
#include <utility>

class AstList: public AstExpr{
protected:
  vector<Operand> list_;
  //Operand myself;
public:
  AstList();
  AstList(const AstList& l);

  //-------------------------------------------
  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr clone_usu() override;
  Operand clone_val() const override final;
  //-------------------------------------------

  astexpr_u_ptr evaluate(astexpr_u_ptr& ast_ctxt) override ;
  astexpr_u_ptr opfunc(astexpr_u_ptr other, AstOpCode op) override final;

  Operand& getv()  override final ;
  Operand& getv(const Operand &k)  override final ;
  Operand& getv(const string &k)  ;
  Operand& getv(int i)  ;

  Operand& back() override final;
  Operand& front() override final;

  const astexpr_u_ptr& get_u_ptr(const Operand &k) const override final;
  astexpr_u_ptr& get_u_ptr_nc(const Operand &k) override final;

  const astexpr_u_ptr& get_u_ptr(int i) const ;

  const astexpr_u_ptr& get_u_ptr() const override final;
  astexpr_u_ptr& get_u_ptr_nc() override final; // non constant

  astexpr_s_ptr get_s_ptr() override final;
  //astexpr_s_ptr get_s_ptr_nc() override final;

  AstExpr *get_raw_ptr(const Operand &k) const override final;
  AstExpr *get_raw_ptr(const string &k) const;
  AstExpr *get_raw_ptr(int i) const;
  AstExpr *get_raw_ptr() const override final;


  //-------------------------------------------
  Operand& operator[] (const Operand& k) override final;
  const Operand& operator[] (const Operand &k) const override final;

  Operand& operator[] (int index) ;
  const Operand& operator[] (int index) const ;

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
  bool add_branch(const vector<string> &keys, const Operand& operand, bool overwrite=false) override final;
  bool add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite=false) override final;
  Operand& get_branch(const vector<string> &keys) override final;
  //-------------------------------------------
  vector<string> _get_keys() const override final;
   s_integer _get_int()   const override final {return 0l; };

  s_integer size() const override;
  Operand to_str() const override ;
  Operand get_type() const override;
  OperandType _get_type() const override;

  void print() const override;
};