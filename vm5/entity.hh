#pragma once
#include "lang.hh"
#include "operand.hh"

class ListEntity;
class MapEntity;

class Entity : public Operand {
  friend ListEntity; 
  friend MapEntity;
protected:
  vector<entity_u_ptr> members;
  unordered_map<string, entity_u_ptr> children;
  entity_s_ptr  parent;
  Operand operation_status; // errors operating on members or children 

public:
  static entity_u_ptr *error;

  Entity() {}
  Entity(const OperandType &t)  { type_ = t; }
  Entity(const Operand &v) : Operand(v) {}
  Entity(const Entity &v) ;
  const Operand _get_operand() const { return *this; }
  
  //-------------------------------------------
  virtual entity_u_ptr clone() const = 0;

  virtual const Entity& add(const Entity& v)=0;
  virtual const entity_u_ptr& add(entity_u_ptr &vptr) =0;    // for list

  virtual const Entity& add(const Entity &k, entity_u_ptr& vptr)=0 ;  // for bison and ast to add 
  virtual const Entity& add(const Entity &k, const Entity& v)=0;   // for map

  virtual const Entity& get(const Entity &k) = 0;
  virtual const Entity& set(const Entity &k, const Entity &v) = 0;
  virtual const Entity& set(const Entity &k, entity_u_ptr &vptr) = 0;

  virtual const ListEntity& get_list(const Entity &k) = 0;
  virtual const MapEntity&  get_map(const Entity &k) = 0;
  virtual Operand to_str() const = 0;

  virtual void print() const =0;

  //-------------------------------------------
  
  friend ostream& operator<<(ostream& os, const Entity& e);
  friend ostream& operator<<(ostream& os, const entity_u_ptr& vptr) ;
  //-------------------------------------------
/*
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
 */ 
//-------------------------------------------
/*
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
*/
};