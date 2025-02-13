#pragma once
#include "ast_map.hh"

class Tree : public Primordial<Tree>{
  friend class SvlmAst;
protected:
  AstMap root;
public:
  Tree(const OperandType&t) : Primordial(t) {};
  s_integer size() const override {return 0;};
  //virtual Operand evaluate(unique_ptr<Tree>&) =0;

};

namespace vslast {
  class SvlmScanner;
  class SvlmParser ;
};


class SvlmAst : public Tree {
  friend class SvlmInteractive;
protected:

  //Operand control_flow = ControlFlow::run;
  bool interactive=false;
  vslast::SvlmScanner *svlm_scanner_ptr ;
  vslast::SvlmParser *svlm_parser_ptr ;
  //SvlmLibLoader libs;

public:
  SvlmAst(const OperandType&t);

  void add_program(const Operand&);
  void add_module(const Operand&, list_u_ptr clist );
  void add_class();
  void add_function();
  void add_mvar();
  void add_ovar();
  void add_lvar();
  void add_code(const Operand&, list_u_ptr clist);

  AstMap& get_root();

  Operand& get_module_subnode(const Operand&, const OperandType t);

  astnode_u_ptr& get_context() ;
  astnode_u_ptr& get_processes() ;
  astnode_u_ptr& get_process(s_integer) ;

  // ctxt is process 
  astnode_u_ptr& get_frames(astnode_u_ptr& ctxt); 
  Operand& get_current_frame(astnode_u_ptr& ctxt) ;
  string get_current_module(astnode_u_ptr &ctxt) ;

  ControlFlow pop_control_flow(astnode_u_ptr &ctxt);
  void push_control_flow(astnode_u_ptr &ctxt);



//  void add_readline_cmds(const string& cmd);
//  vector<string> get_readline_cmds(const string& cmd);

  unique_ptr<Tree> clone() const override {return nullptr;};
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::nil_t;};
  OperandType _get_type() const override { return OperandType::nil_t;};
  void print() const override {};
  void run_evaluate();
  Operand evaluate_prompt_line();
  Operand evaluate_prompt_line(astnode_u_ptr& ctxt);

  virtual Operand evaluate(astnode_u_ptr&ctxt) {return Operand();};

  Operand eval(astnode_u_ptr &ctxt);

  bool add_symfunc(const string& mod, const string& func_name , astnode_u_ptr pl);



};  

