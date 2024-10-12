#pragma once
#include "entity.hh"

class QueNode 
: public MapEntity 
, public ListEntity {
private:

  Entity *add_raw_node();
public:
  //void add(const ListEntity&);
  QueNode() {}

  void print_l() const;
  void print_m() const;

  using MapEntity::add;
  using MapEntity::set;
  using MapEntity::get;
  using MapEntity::to_str;

  entity_u_ptr clone() ;
 // OperandEntity to_str() { return Operand("astnode123");}
  Operand get_type() { return Operand(OperandType::str_t);}
  void print() {};


  const Operand& get_branch(const vector<string> &keys);
  const Operand& add_branch(const vector<string> &keys);
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

  unique_ptr<AstExpr> clone() const override {return nullptr;};
  Operand to_str() const override { return "";};
  Operand get_type() const override { return OperandType::nil_t;};
  void print() const override {};
  astexpr_u_ptr& evaluate(astexpr_u_ptr& ast_ctxt);
};