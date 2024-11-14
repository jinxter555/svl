#pragma once
#include "que_node.hh"

class SvlmAst : Tree {
  friend class SvlmInteractive;
protected:
  //Operand control_flow = ControlFlow::run;
  bool interactive=false;

public:
  SvlmAst(const OperandType&t) : Tree(t) {};

  void add_program(const Operand&);
  void add_module(const Operand&);
  void add_class();
  void add_function();
  void add_mvar();
  void add_ovar();
  void add_lvar();
  void add_code(const Operand&, unique_ptr<AstExpr>);
//  void add_readline_cmds(const string& cmd);
//  vector<string> get_readline_cmds(const string& cmd);

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override { return "";};
  Operand get_type() const override { return OperandType::nil_t;};
  void print() const override {};
  void run_evaluate();
  astexpr_u_ptr evaluate_last_line();
};  


class AstBinOp : public AstMap {
public:
  AstBinOp (unique_ptr<AstExpr> l, unique_ptr<AstExpr> r, AstOpCode op);
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::map_t;};
  void print() ;
};