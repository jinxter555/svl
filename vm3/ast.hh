#pragma once
#include "tree.hh"

enum class BinOpcodeAST {
  INT_OP_INT,
  FLT_OP_FLT,
  INT_OP_FLT,
  FLT_OP_INT,
};

typedef struct {
  BinOpcodeAST op_type;
  char op;
} op_t;

class ExprAst : public TreeNode {
public:

  ExprAst(std::any d) : TreeNode(d) {}
  ExprAst() {}
  virtual ~ExprAst();
  virtual std::any evaluate() = 0;
  virtual void codegen(std::vector<std::string>& code) const = 0;
};


class NumberExprAst : public ExprAst {
public:
  NumberExprAst(std::any d) : ExprAst(d) {}
  std::any evaluate() override ;
  void codegen(std::vector<std::string> &code) const override;
private:
};

class BinOpExprAst : public ExprAst {
public:
  BinOpExprAst (std::shared_ptr<ExprAst> l, std::shared_ptr<ExprAst> r, op_t op);
  BinOpExprAst (std::shared_ptr<ExprAst> l, std::shared_ptr<ExprAst> r, BinOpcodeAST t, char o);
  void codegen(std::vector<std::string>& code) const override;
  std::any evaluate() override;

  template <typename T>
  std::any binop(T a, T b, char op);
  template <typename T, typename U>
  std::any binop(T a, U b, char op);
private:
};