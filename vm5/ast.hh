#pragma once
#include "operand_entity.hh"
#include "list_entity.hh"
#include "map_entity.hh"

class AstNode : public ListEntity, public MapEntity, public OperandEntity {
public:
  AstNode() {}
  AstNode(const  OperandEntity &v)  : OperandEntity(v) {}
  AstNode(const  ListEntity &l)  : ListEntity(l) {}
  AstNode(const  MapEntity &m)  : MapEntity(m) {}
  //-------------------------------------------
};


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

class AstOperand : public AstExpr{
public:
  AstOperand(const Operand &v);
  AstOperand(const OperandEntity &v) : AstExpr(v) {}
  void print() const override ;
  const astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt) override;
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