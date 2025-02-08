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
  //Operand evaluate(unique_ptr<Tree>&) override;

  Operand eval(astnode_u_ptr &ctxt);

  bool add_symfunc(const string& mod, const string& func_name , astnode_u_ptr pl);



};  


class AstBinOp : public AstExpr {
private:
public:
  AstBinOp (astnode_u_ptr l, astnode_u_ptr r, AstOpCode op);
  Operand to_str() const override;
  Operand get_type() const override { return OperandType::ast_binop_t;};
  Operand evaluate(astnode_u_ptr &) override;
  astnode_u_ptr clone() const override {
    cout << "AstBinOp::clone()\n";
    return AstMap::clone();
  };
  void print() ;
};



class AstFunc: public AstExpr{
private:
  //string name;
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
//  string get_module() ; // if $module.var return module , if $var, return current_module
  Operand evaluate(astnode_u_ptr &) override;
  //astnode_u_ptr& get_frames(astnode_u_ptr& ctxt) ;

  Operand& add_frame(astnode_u_ptr& ctxt);
  Operand& remove_frame(astnode_u_ptr& ctxt);


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
  astnode_u_ptr clone() const override ;
};

class AstLvar : public AstAssign {
private:
  bool initiated=false;

public:
  AstLvar(const string&);
  AstLvar(const string&, astnode_u_ptr idx_key);
  string name() override final;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  Operand evaluate(astnode_u_ptr &) override;
  bool assign(astnode_u_ptr& ctxt, Operand&) override final;
  void print() const override;
};

// AstTuple contains variables whereas Tuple just a dervied list_t
class AstTuple : public AstAssign {
private:
  astnode_u_ptr elemptr(const Operand&);
public:
  AstTuple();
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
  AstFlow(ControlFlow);
  AstFlow(ControlFlow, astnode_u_ptr) ;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  Operand evaluate(astnode_u_ptr &) override;
};

//----------------------------- repeat expr
class AstRepeat : public AstExpr {
public:
  AstRepeat(astnode_u_ptr cond, astnode_u_ptr  body);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  Operand evaluate(astnode_u_ptr &) override;
};

//----------------------------- while expr
class AstWhile : public AstExpr {
public:
  AstWhile(astnode_u_ptr cond, astnode_u_ptr  body);
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  Operand evaluate(astnode_u_ptr &) override;
};


//----------------------------------------------------------------------- Case Expr Block
//----------------------------- Case Top
class AstCase : public AstExpr {
public:
  AstCase(astnode_u_ptr top, astnode_u_ptr  body); // top expression
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
  Operand evaluate(astnode_u_ptr &) override;
};

//----------------------------- Case Match: Virtual
class AstCaseMatch: public AstExpr {
public:                                                                                                                                                               
  AstCaseMatch(OperandType t) : AstExpr(t) { }                                                                                                                    
  virtual bool match(const astnode_u_ptr& top, astnode_u_ptr &ctxt) = 0 ;                                                                                        
  Operand get_type() const override {
    cout << "AstCaseMatch::get_type()!!!\n";
    return OperandType::nil_t;
  };
  void print() const override {
    cout << "AstCaseMatch::print()!!!\n";

  };
};

//----------------------------- Case Match Is
class AstCaseMatchIs: public AstCaseMatch {
public:                                                                                                                                                               
  AstCaseMatchIs(astnode_u_ptr is_, astnode_u_ptr body ) ;
  Operand evaluate(astnode_u_ptr &) override;
  bool match(const astnode_u_ptr& top, astnode_u_ptr &ctxt) override ;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
};

//----------------------------- Case Match When
class AstCaseMatchWhen: public AstCaseMatch {
public:
  AstCaseMatchWhen(astnode_u_ptr is_, astnode_u_ptr when_, astnode_u_ptr body);
  Operand evaluate(astnode_u_ptr &) override;
  bool match(const astnode_u_ptr& top, astnode_u_ptr &ctxt) override ;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
};

//----------------------------- Case Match Else
class AstCaseMatchElse: public AstCaseMatch {
public:                                                                                                                                                               
  AstCaseMatchElse(astnode_u_ptr body);
  Operand evaluate(astnode_u_ptr &) override;
  bool match(const astnode_u_ptr& top, astnode_u_ptr &ctxt) override ;                                                                                        
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;
};


//----------------------------------------------------------------------- SvlmBind
// if func doesn't exist in module
// look up symbols func. if it exists
// assign new 

class SvlmBind : public AstExpr {
public:
};

class Kernel : SvlmBind {
public:
  Operand evaluate(astnode_u_ptr &) override;
  Operand to_str() const override;
  Operand get_type() const override ;
  OperandType _get_type() const override;
  void print() const override;

};
