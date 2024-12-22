#pragma once
#include "que_node.hh"

class SvlmAst : Tree {
  friend class SvlmInteractive;
protected:
  //Operand control_flow = ControlFlow::run;
  bool interactive=false;

public:
  SvlmAst(const OperandType&t);

  void add_program(const Operand&);
  void add_module(const Operand&, astexpr_u_ptr);
  void add_class();
  void add_function();
  void add_mvar();
  void add_ovar();
  void add_lvar();
  void add_code(const Operand&, unique_ptr<AstExpr>);

  Operand& get_module_subnode(const Operand&, const OperandType t);

  astexpr_u_ptr& get_context() ;
  astexpr_u_ptr& get_frames() ;
  Operand& get_current_frame() ;

  string get_current_module() ;
//  void add_readline_cmds(const string& cmd);
//  vector<string> get_readline_cmds(const string& cmd);

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::nil_t;};
  OperandType _get_type() const override { return OperandType::nil_t;};
  void print() const override {};
  void run_evaluate();
  Operand evaluate_last_line();
};  


//class AstBinOp : public AstExpr {
class AstBinOp : public AstMap {
private:
  OperandType type_;
public:
  AstBinOp (unique_ptr<AstExpr> l, unique_ptr<AstExpr> r, AstOpCode op);
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::ast_binop_t;};
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  const Operand& getv()  const override { 
    cout << "bin op getv()!\n"; 
    return AstMap::getv();
  };
  void print() ;
};



class AstFunc: public AstMap {
private:
  string name;
  OperandType type_;
public:
  AstFunc(const Operand&,  astexpr_u_ptr, astexpr_u_ptr) ; 
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void print() const override;
};


class AstPrint : public AstMap { 
private:
  OperandType type_;
public:
  AstPrint(astexpr_u_ptr);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void print() const override;
};

class AstCaller : public AstMap {
private:
  OperandType type_;
  bool evaluated=false;
public:
  AstCaller(const Operand&, astexpr_u_ptr);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void print() const override;
  //string get_current_module(astexpr_u_ptr& ctxt) ; // get current module from frame only
  string get_module() ; // if $module.var return module , if $var, return current_module
  //astexpr_u_ptr& get_frames(astexpr_u_ptr& ctxt) ;

  Operand& add_frame(astexpr_u_ptr& ctxt);
  Operand& remove_frame(astexpr_u_ptr& ctxt);


};

class AstAssign : public AstMap {
protected:
  OperandType type_;
  OperandType scale_;
public:
  AstAssign(OperandType t, OperandType s=OperandType::scalar_t) : type_(t), scale_(s) {}
  virtual string name() = 0;
  //virtual void assign(astexpr_u_ptr&, Operand& ) = 0;
  virtual bool assign(astexpr_u_ptr&, Operand& ) = 0;
  s_integer get_index_i(astexpr_u_ptr&) ;
  string get_index_s(astexpr_u_ptr&) ;
};

class AstMvar : public AstAssign {
private:
  bool initiated=false;
  //Operand &variable;
public:
  AstMvar(const string&);
  AstMvar(const string&, astexpr_u_ptr idx_key);
  string name() override final;
  string get_module() ; // if $module.var return module , if $var, return current_module
  Operand to_str() const override;
  Operand get_type() const override ;
  Operand get_scale() {return scale_; };
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  const Operand& getv() const override;
  bool assign(astexpr_u_ptr& ctxt, Operand& ) override final;
  void print() const override;
  astexpr_u_ptr clone() const override; 
};

class AstLvar : public AstAssign {
private:
  bool initiated=false;

public:
  AstLvar(const string&);
  string name() override final;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  bool assign(astexpr_u_ptr& ctxt, Operand&) override final;
  void print() const override;
};
class AstTuple : public AstAssign {
private:
  astexpr_u_ptr elemptr(const Operand&);
public:
  AstTuple(astexpr_u_ptr);
  string name() override final;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  bool assign(astexpr_u_ptr& ctxt, Operand&) override final;
  void print() const override;

  astexpr_u_ptr clone() const override; 
  astexpr_u_ptr clone_usu() override;
};

class AstFlow : public AstExpr {
protected:
  OperandType type_;
public:
  AstFlow(OperandType t) : type_(t) {}
  virtual string name() = 0;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void print() const override;
};
