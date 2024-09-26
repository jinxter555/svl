#pragma once
#include "lang.hh"
#include "operand.hh"

class Entity : public Operand {
protected:
  vector<entity_u_ptr> members;
  // unordered_map<string, entity_u_ptr> children;
  entity_s_ptr  parent;
public:
  static Entity entity_undef_error; static Entity entity_mem_error;
  Entity() {}
  Entity(const OperandType &t)  { type_ = t; }
  Entity(const Operand &v) : Operand(v) {}
  Entity(const Entity &v) ;
  entity_u_ptr clone() const;
  entity_u_ptr clone_operand() const;
  //-------------------------------------------
  const Operand _get_operand() const { return *this; }
  
  void list_print() const;
  void map_print() const;
  //-------------------------------------------
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------
  using Operand::get_type;
  using Operand::get_value;
  using Operand::_get_number;
  using Operand::_get_int;
  using Operand::_get_float;
  using Operand::_get_str;

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