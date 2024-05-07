#ifndef AST_HH
#define AST_HH
#include "tree.hh"
#include "vm_type.hh"
#include "lang.hh"
#include "universe.hh"


class SvlmLangContext;
class ExprAst : public TreeNode {
protected:
  std::vector<full_symbol_t> current_contexts; // where am i and who ami
  full_symbol_t current_context; // where am i and who ami
  std::shared_ptr<Tree> context_tree;
public:

  ExprAst(std::any d) : TreeNode(d) {}
  ExprAst();
  virtual ~ExprAst();
  virtual std::any evaluate(SvlmLangContext *slc) = 0;
  virtual void codegen(std::vector<std::string>& code) const = 0;
  virtual void print() = 0 ;
};


class NumberExprAst : public ExprAst {
public:
  NumberExprAst(std::any d) : ExprAst(d) {}
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
private:
};

class IdentExprAst : public ExprAst {
public:
  IdentExprAst(std::string s);
  std::string name();
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
private:
};

class GvarExprAst : public ExprAst {
public:
  GvarExprAst(std::string s);
  std::string name();
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
private:
};

class LvarExprAst : public ExprAst {
public:
  LvarExprAst(std::string s) : ExprAst(s) {}
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
private:
};

class ArgExprAst : public ExprAst {
public:
  ArgExprAst(arg_name_pos_t arg);
  ArgExprAst(std::string name, unsigned char pos);
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
  std::string name();
  arg_name_pos_t arg();
};

class DeclExprAst : public ExprAst {
public:
  DeclExprAst (std::shared_ptr<IdentExprAst> l, DeclOpcodeAST doa) ;
  std::any evaluate(SvlmLangContext *slc) override ;
  void codegen(std::vector<std::string> &code) const override;
  void print() override;
};

class BinOpExprAst : public ExprAst {
public:
  BinOpExprAst (std::shared_ptr<ExprAst> l, std::shared_ptr<ExprAst> r, op_t op);
  BinOpExprAst (std::shared_ptr<ExprAst> l, std::shared_ptr<ExprAst> r, BinOpcodeAST t, char o);

  void codegen(std::vector<std::string>& code) const override;
  std::any evaluate(SvlmLangContext *slc) override;

  template <typename T>
  std::any binop(T a, T b, char op);
  template <typename T, typename U>
  std::any binop(T a, U b, char op);

  void print() override;
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

  void print() override;
  void codegen(std::vector<std::string> &code) const override;
};

class FuncExprAst : public ExprAst {
public:
  FuncExprAst(int i) ; // init function name
  FuncExprAst(std::string s, std::vector<std::string> args, std::shared_ptr<ListExprAst> body); 

  ; // init function name


  void add_args(std::shared_ptr<ListExprAst> lea); // list of IdentExprAst
  void add_body(std::shared_ptr<ListExprAst> lea); // function body, list of code
  std::any evaluate(SvlmLangContext *slc) override;
  void print() override;
  void codegen(std::vector<std::string> &code) const override;
};


#endif
