#pragma once
#include "entity.hh"

class AstNode 
: public OperandEntity
, public ListEntity
, public MapEntity {
public:
  //void add(const ListEntity&);
  AstNode() : OperandEntity() {}
  AstNode(const OperandEntity &v) : OperandEntity(v) {}
  void add(const OperandEntity&);
  //--- list
  entity_u_ptr& operator[](int); //const entity_u_ptr& operator[](int) const;
  //--- map 
  entity_u_ptr& operator[](const string&); //const entity_u_ptr& operator[](const string&) const;

  void print_l() const;
  void print_m() const;
  using ListEntity::add;
  using ListEntity::set;
  using MapEntity::add;
  using MapEntity::set;
};

class AstExpr {
protected:
  AstNode node;
public:

};