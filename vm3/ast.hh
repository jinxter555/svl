#pragma once
#include <iostream>
#include <memory>
#include <vector>


template<typename T>
class Expr {
public:
  virtual ~Expr();
  virtual T evaluate() const = 0;
  virtual void codegen(std::vector<std::string>& code) const = 0;
};

template<typename T>
class NumberExpr : public Expr<T> {
public:
  NumberExpr(T v) : value(v) {}
  T evaluate() const override;
  void codegen(std::vector<std::string> &code) const override;
private:
  T value;
};

template<typename T>
class BinOpExpr : public Expr<T> {
public:
  //~BinOpExpr() {}
  BinOpExpr
  ( std::unique_ptr<Expr<T>> left
  , std::unique_ptr<Expr<T>> right
  , char o)
  : left(std::move(left))
  , right(std::move(right))
  , op(o) {}
  void codegen(std::vector<std::string>& code) const override;
  T evaluate(T) const override;
private:
  char op;
  std::unique_ptr<Expr<T>> left;
  std::unique_ptr<Expr<T>> right;
};
