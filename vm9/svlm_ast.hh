#pragma once
#include "ast_node.hh"
#include "operand.hh"
#include "ast_map.hh"
#include "ast_list.hh"

class Tree : public Primordial<Tree>{
  friend class SvlmAst;
protected:
  AstMap root;
public:
  Tree(const OperandType&t) : Primordial(t) {};
  s_integer size() const override {return 0;};
  //virtual Operand evaluate(unique_ptr<Tree>&) =0;

};

class SvlmAst : public Tree {
  friend class SvlmInteractive;
protected:

  //Operand control_flow = ControlFlow::run;
  bool interactive=false;

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

  Operand& get_module_subnode(const Operand&, const OperandType t);

  astnode_u_ptr& get_context() ;
  astnode_u_ptr& get_frames() ;
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
  Operand evaluate_prompt_line();
  //Operand evaluate(unique_ptr<Tree>&) override;

};  


class AstBinOp : public AstExpr {
private:
public:
  AstBinOp (unique_ptr<AstNode> l, unique_ptr<AstNode> r, AstOpCode op);
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::ast_binop_t;};
  Operand evaluate(astnode_u_ptr &) override;
  void print() ;
};



class AstFunc: public AstExpr{
private:
  string name;
public:
  AstFunc(const Operand&,  astnode_u_ptr, astnode_u_ptr) ; 
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astnode_u_ptr &) override;
  void print() const override;
};


class AstPrint : public AstExpr { 
private:
public:
  AstPrint(astnode_u_ptr);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astnode_u_ptr &) override;
  void print() const override;
};

class AstCaller : public AstExpr {
private:
  bool evaluated=false;
public:
  AstCaller(const Operand&, astnode_u_ptr);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  //string get_current_module(astnode_u_ptr& ctxt) ; // get current module from frame only
  string get_module() ; // if $module.var return module , if $var, return current_module
  Operand evaluate(astnode_u_ptr &) override;
  //astnode_u_ptr& get_frames(astnode_u_ptr& ctxt) ;

  Operand& add_frame(unique_ptr<AstNode>& ctxt);
  Operand& remove_frame(unique_ptr<AstNode>& ctxt);


};

class AstAssign : public AstExpr {
protected:
  OperandType scale_;
public:
  AstAssign(OperandType t, OperandType s=OperandType::scalar_t) : AstExpr(t), scale_(s) {}
  virtual string name() = 0;
  //virtual void assign(astnode_u_ptr&, Operand& ) = 0;
  virtual bool assign(astnode_u_ptr&, Operand& ) = 0;
  s_integer get_index_i(astnode_u_ptr&) ;
  string get_index_s(astnode_u_ptr&) ;
};

class AstMvar : public AstAssign {
private:
  bool initiated=false;
  //Operand &variable;
public:
  AstMvar(const string&);
  AstMvar(const string&, astnode_u_ptr idx_key);
  string name() override final;
  string get_module() ; // if $module.var return module , if $var, return current_module
  Operand to_str() const override;
  Operand get_type() const override ;
  Operand get_scale() {return scale_; };
  OperandType _get_type() const override;
  Operand evaluate(astnode_u_ptr &) override;
  bool assign(astnode_u_ptr& ctxt, Operand& ) override final;
  void print() const override;
  //astnode_u_ptr clone() const override; 
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
  Operand evaluate(astnode_u_ptr &) override;
  bool assign(astnode_u_ptr& ctxt, Operand&) override final;
  void print() const override;
};

class AstTuple : public AstAssign {
private:
  astnode_u_ptr elemptr(const Operand&);
public:
  AstTuple(astnode_u_ptr);
  string name() override final;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astnode_u_ptr &) override;
  bool assign(astnode_u_ptr& ctxt, Operand&) override final;
  astnode_u_ptr clone() const override;
  void print() const override;

};

class AstFlow : public AstExpr {
public:
  AstFlow(OperandType t) ;
  virtual string name() = 0;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  Operand evaluate(astnode_u_ptr &) override;
};
