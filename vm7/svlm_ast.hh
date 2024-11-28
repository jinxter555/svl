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
//  void add_readline_cmds(const string& cmd);
//  vector<string> get_readline_cmds(const string& cmd);

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override { return "";};
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
  Operand evaluate(astexpr_u_ptr& ast_ctxt) override;
  Operand& getv()  override { 
    cout << "bin op getv()!\n"; 
    return AstMap::getv();
    //return nil_operand;
  };
  void print() ;
};


class AstAssign : public AstMap{ 
  OperandType type_;
public:
  AstAssign(OperandType t) : type_(t) { }
  virtual std::string name() =0;
  virtual void assign(astexpr_u_ptr& ast_ctxt) = 0;
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
  Operand evaluate(astexpr_u_ptr& ast_ctxt) override;
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
  Operand evaluate(astexpr_u_ptr& ast_ctxt) override;
  void print() const override;
};