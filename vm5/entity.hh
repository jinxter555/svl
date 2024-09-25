#pragma once
#include "lang.hh"
#include "operand.hh"


class Entity : public Operand {
protected:
  vector<Entity> members;

  map<string, entity_ptr> children;
  entity_ptr  parent;
public:
  static Entity entity_undef_error;
  Entity() {}
  Entity(const OperandType &t)  { type_ = t; }
  Entity(const Operand &v) : Operand(v) {}

  //Operand get_operand() { return *this; }
  const Operand get_operand() const { return *this; }

  void list_print() const;
  void map_print() const;

  friend ostream& operator<<(ostream& os, const Entity& e);

  //-------------------------------------------
  using Operand::type_print;
  using Operand::type_get;

  using Operand::type_str;
  using Operand::err_str;
  using Operand::ast_op_str;
  using Operand::whatami;

  //-------------------------------------------



  using Operand::operator+;
  using Operand::operator-;
  using Operand::operator*;
  using Operand::operator/;

  using Operand::operator==;
  using Operand::operator!=;
  using Operand::operator>=;
  using Operand::operator<=;
  using Operand::operator<;
  using Operand::operator>;

  using Operand::operator&&;
  using Operand::operator||;
  using Operand::operator!;
};
