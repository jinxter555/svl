#ifndef AST_HH
#define AST_HH
#include "tree.hh"
#include "vm_type.hh"
#include "lang.hh"
#include "universe.hh"
#include "number.hh"
#include "tuple.hh"
#include "atom.hh"
#include "operand.hh"


class SvlmLangContext;


class ExprAst : public TreeNode {
protected:
  std::vector<full_symbol_t> current_contexts; // where am i and who ami
  full_symbol_t current_context; // where am i and who ami
  std::shared_ptr<Tree> context_tree;
public:
  enum class ExprAstType {
     Print, ControlFlow, Operand, Number, Atom, Ident, Tuple, LTuple,
    Assign, Lvar, Gvar, Arg, List, Func, 
    Call, Case, CaseMatch, Flow, FlowMatch, FlowMatchWhen, Decl, BinOp, While, Repeat};

  ExprAst(std::any d) : TreeNode(d) {}
  ExprAst();
  virtual ~ExprAst();
  virtual ExprAstType whoami() = 0;
  virtual std::any evaluate(SvlmLangContext *slc) = 0;
  virtual std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) = 0;
  virtual void codegen(std::vector<std::string>& code) const = 0;
  virtual void print() = 0 ;
};

//----------------------------- Print expr
class PrintExprAst : public ExprAst { // to disable continue aka break loop for ListExprAst
public:
  PrintExprAst(std::shared_ptr<ExprAst> exp);
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string>& code) const override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  ExprAstType whoami() override { return ExprAstType::Print;}
};

//----------------------------- discontinue  

class ControlFlowExprAst : public ExprAst { // to disable continue aka break loop for ListExprAst
public:
  ControlFlowExprAst(ControlFlow cf); // break keyword 
  ControlFlowExprAst(ControlFlow cf, std::shared_ptr<ExprAst> exp); // break keyword 
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void codegen(std::vector<std::string>& code) const override;
  void print() override;
  ExprAstType whoami() override { return ExprAstType::ControlFlow;}
};


//----------------------------- Number Bin variable expr
class OperandExprAst : public ExprAst {
public:
  OperandExprAst(Operand o);
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override; 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  ExprAstType whoami() override { return ExprAstType::Operand;}
private:
};

//----------------------------- tuple expr
class ListExprAst;
class TupleExprAst : public ExprAst {
private:
  bool assign(SvlmLangContext *slc, std::shared_ptr<ListExprAst> l, std::vector<std::any> rtva);

public:
  bool evaluated = false;
  TupleExprAst(std::shared_ptr<ListExprAst> tlist);
  TupleExprAst(const Tuple &t);
  TupleExprAst(const Tuple &t, std::shared_ptr<ListExprAst> tlist);
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Tuple;}
  void print() override;
};
//----------------------------- Ident expr


class IdentExprAst : public ExprAst {
public:
  IdentExprAst(const std::string &name);
  std::string name();
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  ExprAstType whoami() override { return ExprAstType::Ident;}
private:
};

class AssignExprAst : public ExprAst { 
public:
  AssignExprAst(ExprAstType t) : ExprAst(t) { }
  virtual ~AssignExprAst() {}
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  virtual std::string name() =0;
  virtual void assign(SvlmLangContext *slc, std::any d) = 0;
  ExprAstType whoami() override { return ExprAstType::Assign;}
};

class GvarExprAst : public AssignExprAst {
public:
  GvarExprAst(const std::string &name);
  std::string name() override;
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {
    std::cout << "gvar uni_oip\n";
    return 0;
    } 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  void assign(SvlmLangContext *slc, std::any d) override;
  ExprAstType whoami() override { 
    //std::cout << "whoami, i am gvar\n";
    return ExprAstType::Gvar;}
private:
};

class LvarExprAst : public AssignExprAst {
public:
  LvarExprAst(const std::string &name);
  std::string name() override;
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void codegen(std::vector<std::string> &code) const override;
  void assign(SvlmLangContext *slc, std::any d) override;
  void print() override;
  ExprAstType whoami() override { 
    //std::cout << "whoami, i am lvar\n";
    return ExprAstType::Lvar;}
private:
};


class ArgExprAst : public ExprAst {
public:
  ArgExprAst(arg_name_pos_t arg);
  ArgExprAst(std::string name, unsigned char pos);
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  std::string name();
  arg_name_pos_t arg();
  ExprAstType whoami() override { return ExprAstType::Arg;}
};


class DeclExprAst : public ExprAst {
public:
  DeclExprAst (std::shared_ptr<IdentExprAst> l, DeclOpcodeAST doa) ;
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  ExprAstType whoami() override { return ExprAstType::Decl;}
};

class BinOpExprAst : public ExprAst {
public:
  BinOpExprAst (std::shared_ptr<ExprAst> l, std::shared_ptr<ExprAst> r, ast_op op);
  //BinOpExprAst (std::shared_ptr<BinExprAst> l, std::shared_ptr<BinExprAst> r, ast_op op);
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 

  void codegen(std::vector<std::string>& code) const override;
  std::any evaluate(SvlmLangContext *slc) override;
  void print() override;
  ExprAstType whoami() override { return ExprAstType::BinOp;}
private:
};

class ListExprAst : public ExprAst {
public:
  ListExprAst() {}
  ListExprAst(std::any d);
  void add(std::shared_ptr<ExprAst> e);
  std::shared_ptr<ExprAst> get(int n);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any evaluate_last_line(SvlmLangContext *slc);
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 

  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::List;}
};

class FuncExprAst : public ExprAst {
public:
  FuncExprAst(std::string s, std::vector<std::string> args, std::shared_ptr<ListExprAst> body); 
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Func;}
};

class CallExprAst : public ExprAst {
private:
  void fcall_setup(SvlmLangContext *slc);
public:
  CallExprAst(std::string callee, std::shared_ptr<ListExprAst> args);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Call;}
};

//----------------------------- Switch Bin variable expr
class CaseExprAst : public ExprAst {
public:
  CaseExprAst (std::shared_ptr<ExprAst> top);

  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Case;}

};

//----------------------------- Case Bin variable expr
class CaseMatchExprAst : public ExprAst {
public:
  CaseMatchExprAst (std::shared_ptr<ExprAst> match, std::shared_ptr<ListExprAst> body, ast_op op);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::CaseMatch;}

};


//----------------------------- flow expr
class FlowExprAst : public ExprAst {
public:
  FlowExprAst (std::shared_ptr<ExprAst> top, std::shared_ptr<ListExprAst> body);

  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am Flow\n";
    return ExprAstType::Flow;}

};

//----------------------------- flow match expr
class FlowMatchExprAst : public ExprAst {
public:
  FlowMatchExprAst (std::shared_ptr<ExprAst> match, std::shared_ptr<ListExprAst> body, ast_op op);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am FlowMatch\n";
    return ExprAstType::FlowMatch;
    }

};
class FlowMatchWhenExprAst : public ExprAst {
public:
  FlowMatchWhenExprAst ( std::shared_ptr<AssignExprAst> assign_expr,
    std::shared_ptr<ExprAst> match, std::shared_ptr<ListExprAst> body);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { std::cout << "I am FlowMatch\n"; return ExprAstType::FlowMatchWhen; }


};

//----------------------------- while expr
class WhileExprAst : public ExprAst {
public:
  WhileExprAst (std::shared_ptr<ExprAst> cond, std::shared_ptr<ListExprAst> body);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am while\n";
    return ExprAstType::While;}
};

//----------------------------- repeat expr
class RepeatExprAst : public ExprAst {
public:
  RepeatExprAst (std::shared_ptr<ExprAst> cond, std::shared_ptr<ListExprAst> body);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am repeat\n";
    return ExprAstType::Repeat;}
};

#endif