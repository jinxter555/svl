#pragma once
#include <iostream>
#include <memory>
#include <vector>


template<typename T>
class ExprAst {
public:
  virtual ~ExprAst();
  virtual T evaluate() const = 0;
  virtual void codegen(std::vector<std::string>& code) const = 0;
};

template<typename T>
class NumberExprAst : public ExprAst<T> {
public:
  NumberExprAst(T v) : value(v) {}
  T evaluate() const override;
  void codegen(std::vector<std::string> &code) const override;
private:
  T value;
};

template<typename T>
class BinOpExprAst : public ExprAst<T> {
public:
  //~BinOpExpr() {}
  BinOpExprAst
  ( std::unique_ptr<ExprAst<T>> left
  , std::unique_ptr<ExprAst<T>> right
  , char o)
  : left(std::move(left))
  , right(std::move(right))
  , op(o) {}
  void codegen(std::vector<std::string>& code) const override;
  T evaluate(T) const override;
private:
  char op;
  std::unique_ptr<ExprAst<T>> left;
  std::unique_ptr<ExprAst<T>> right;
};
