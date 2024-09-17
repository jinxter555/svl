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
enum class ExprAstType {
  Print, ControlFlow, Operand, Ident, Tuple, Map, Tree,
  Assign, Lvar, Gvar, List, Func,
  Callee, Case, CaseMatch, CaseMatchIs, CaseMatchWhen, CaseMatchElse, Decl, BinOp, While, Repeat};


class ExprAst : public TreeNode {
protected:
  std::vector<full_symbol_t> current_contexts; // where am i and who ami
  full_symbol_t current_context; // where am i and who ami
  std::shared_ptr<Tree> context_tree;
public:
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
  //bool assign(SvlmLangContext *slc, std::shared_ptr<ListExprAst> l, std::vector<std::any> rtva);
public:
  bool evaluated = false;
  TupleExprAst(std::shared_ptr<ListExprAst> tlist);
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override;
  bool assign(SvlmLangContext *slc, const Operand& right_hand);
  ExprAstType whoami() override { return ExprAstType::Tuple;}
  void print() override;
};
//----------------------------- Ident expr


class IdentExprAst : public ExprAst {
public:
  IdentExprAst(const std::string &name);
  std::string name();
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override;
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

  int get_index_i(SvlmLangContext *slc);
  std::string get_index_s(SvlmLangContext *slc);
};

class GvarExprAst : public AssignExprAst {
public:
  GvarExprAst(const std::string &name);
  GvarExprAst(const std::string &name, VarTypeEnum scale_type);
  GvarExprAst(const std::string &name, std::shared_ptr<ExprAst> idx_key, VarTypeEnum scale);
  std::string name() override;
  std::any evaluate(SvlmLangContext *slc) override ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {
    std::cout << "gvar uni_op\n";
    return 0;
    } 
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  void assign(SvlmLangContext *slc, std::any d) override;
  ExprAstType whoami() override { 
    //std::cout << "whoami, i am gvar\n";
    return ExprAstType::Gvar;}
};

class LvarExprAst : public AssignExprAst {
public:
  LvarExprAst(const std::string &name);
  LvarExprAst(const std::string &name, std::shared_ptr<ExprAst> idx_key, VarTypeEnum scale);
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
  ListExprAst() : ExprAst(ExprAstType::List) {}
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

class MapExprAst : public ExprAst{
private:
  bool evaluated = false;
public:
  MapExprAst() : ExprAst(ExprAstType::Map) {}
  void add( const std::string &key, std::shared_ptr<ExprAst> e);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Map;}
};

class TreeExprAst : public ExprAst{
public:
  TreeExprAst() ;
  TreeExprAst(std::shared_ptr<OperandExprAst> cmd) ;
  TreeExprAst(std::shared_ptr<OperandExprAst> cmd, std::shared_ptr<ExprAst> e) ;

  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { return ExprAstType::Tree;}
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
  ExprAstType whoami() override { return ExprAstType::Callee;}
};


//----------------------------- flow expr
class CaseExprAst : public ExprAst {
public:
  CaseExprAst (std::shared_ptr<ExprAst> top, std::shared_ptr<ListExprAst> body);

  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am Case\n";
    return ExprAstType::Case;}

};

class CaseMatchExprAst : public ExprAst {
public:
  CaseMatchExprAst(ExprAstType t) : ExprAst(t) { }
  virtual bool match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) = 0 ;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  ExprAstType whoami() override { 
    return ExprAstType::CaseMatch;
  }
};
//----------------------------- flow match IS expr
class CaseMatchIsExprAst : public CaseMatchExprAst {
public:
  CaseMatchIsExprAst (std::shared_ptr<ExprAst> is, std::shared_ptr<ListExprAst> cbody);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { 
    std::cout << "I am CaseMatchIs\n";
    return ExprAstType::CaseMatchIs;
  }
  bool match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) override ;

};
//----------------------------- flow match When expr
class CaseMatchWhenExprAst : public CaseMatchExprAst {
public:
  CaseMatchWhenExprAst(
    std::shared_ptr<ExprAst> is,
    std::shared_ptr<ExprAst> when, 
    std::shared_ptr<ListExprAst> body);
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
  ExprAstType whoami() override { std::cout << "I am CaseMatchWhen\n"; return ExprAstType::CaseMatchWhen; }

  bool match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) override ;

};

class CaseMatchElseExprAst : public CaseMatchExprAst {
public:
  CaseMatchElseExprAst (std::shared_ptr<ListExprAst> body);
  bool match(std::shared_ptr<ExprAst> top, SvlmLangContext *slc) override ;
  std::any evaluate(SvlmLangContext *slc) override;
  std::any uni_op(SvlmLangContext *slc, std::shared_ptr<ExprAst> r, ast_op op) override {return 0;} 
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
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