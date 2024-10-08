#pragma once
#include "entity.hh"

class QueNode 
: public MapEntity 
, public ListEntity {
public:
  //void add(const ListEntity&);
  QueNode() {}
  //--- list
  entity_u_ptr& operator[](int); //const entity_u_ptr& operator[](int) const;
  //--- map 
  entity_u_ptr& operator[](const string&); //const entity_u_ptr& operator[](const string&) const;

  void print_l() const;
  void print_m() const;

  using MapEntity::add;
  using MapEntity::set;
  using MapEntity::get;
  using MapEntity::to_str;

  entity_u_ptr clone() {return nullptr;} 
 // OperandEntity to_str() { return Operand("astnode123");}
  Operand get_type() { return Operand(OperandType::str_t);}
  void print() {};
  //const Entity&   get(int i) { return nil_entity;};
};

class AstExpr : public Primordial<AstExpr> {
protected:
  QueNode node;
public:
  AstExpr();
  AstExpr(const OperandType&);
  virtual astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt) = 0;
};

class AstOperand : public AstExpr {
public:
  AstOperand();
  AstOperand(const Operand&);
  int test_a();

  unique_ptr<AstExpr> clone() const override {};
  Operand to_str() const override {};
  Operand get_type() const override {};
  void print() const override {};
  astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt);
};