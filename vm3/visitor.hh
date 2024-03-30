#pragma once
#include "ast.hh"
class NumberExpr;
class BinOpExpr;
class Visitor {
public:
  virtual ~Visitor() {}
  virtual void visit(NumberExpr* expr) = 0;
  virtual void visit(BinOpExpr* expr) = 0;
};