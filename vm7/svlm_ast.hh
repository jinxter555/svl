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
public:
  AstBinOp (unique_ptr<AstExpr> l, unique_ptr<AstExpr> r, AstOpCode op);
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::ast_binop_t;};
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  Operand& getv()  override { 
    cout << "bin op getv()!\n"; 
    return AstMap::getv();
    //return nil_operand;
  };
  void print() ;
};



class AstFunc: public AstMap {
private:
  string name;
  OperandType type_;
public:
  AstFunc(const Operand&,  astexpr_u_ptr) ; 
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
  AstCaller(const Operand&);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void print() const override;
  string get_current_module(astexpr_u_ptr& ctxt) ;
  //astexpr_u_ptr& get_frames(astexpr_u_ptr& ctxt) ;

  Operand& add_frame(astexpr_u_ptr& ctxt);
  Operand& remove_frame(astexpr_u_ptr& ctxt);


};

class AstAssign : public AstMap {
protected:
  OperandType type_;
public:
  AstAssign(OperandType t) : type_(t) {}
  virtual string name() = 0;
  virtual void assign(astexpr_u_ptr&, const Operand& ) = 0;
  int get_index_i(astexpr_u_ptr&) {return 0;};
  string get_index_s(astexpr_u_ptr&) {return "";};
};

class AstMvar : public AstAssign {
private:
  bool initiated=false;
public:
  AstMvar(const string&);
  string name() override final;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astexpr_u_ptr& ctxt) override;
  void assign(astexpr_u_ptr& ctxt, const Operand&) override final;
  void print() const override;
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
  void assign(astexpr_u_ptr& ctxt, const Operand&) override final;
  void print() const override;
};