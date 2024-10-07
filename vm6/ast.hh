#pragma once
#include "entity.hh"

class AstNode : public MapEntity {
public:
  //void add(const ListEntity&);
  AstNode() {}
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

class AstExpr : public AstNode {
public:
  int a();
  virtual astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt);
};

class AstOperand : public AstExpr {
public:
  AstOperand();
  AstOperand(const Operand&);

  astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt);
};