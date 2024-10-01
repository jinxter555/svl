#pragma once
#include "ast_expr.hh"

class OperandEntity;

class AstOperand : public AstExpr{
public:
  AstOperand(const Operand &v);
  AstOperand(const OperandEntity &v) : AstExpr(v) {}
  void print() const override ;
  const astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt) override;
};

class AstNode {
public:
  AstNode() {}
};


/*
class AstMap : public AstNode{
public:
  AstMap();
  entity_ptr add_ptr(const string &k, entity_ptr vptr) ;
  Entity add(const string &k, const Entity &v) ;
  Entity add(const vector<string> &ks, const Entity &v) ;
  Entity get(const string &k);
  Entity set(const string &k, const Entity &v);
  entity_ptr get_ptr(const string &k) ;
  entity_ptr get_new_ptr(const string &k) ;
  Entity evaluate(Entity *ast_ctxt) override;
  void print() override;
  using Entity::whatami;
};

class AstRoot : public AstMap {
protected:
  entity_ptr root=nullptr;
public:
  AstRoot();
  AstRoot(AstMap m);
  Entity add(const vector<string> &ks, const Entity &v) ;


};
*/