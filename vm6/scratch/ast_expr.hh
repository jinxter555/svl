#ifndef _AST_EXPR_H
#define _AST_EXPR_H
#pragma once
#include "entity.hh"

class AstExpr;
using astexpr_u_ptr = unique_ptr<AstExpr>;

class OperandEntity;
class AstExpr {
protected:
  entity_u_ptr node;
public:
  AstExpr() {};
  AstExpr(const Operand &v);
  AstExpr(const OperandEntity &v);
  AstExpr(const ListEntity &v);
  AstExpr(const MapEntity &v) ;
  //virtual AstType whoami() = 0;
  virtual const astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt) = 0;
  //virtual void codegen(std::vector<std::string>& code) const = 0;
  virtual void print() const = 0 ;
};

#endif