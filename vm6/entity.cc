#include "entity.hh"


Entity::Entity() { parent = nullptr; }
//Entity::Entity(const Operand &v) : Operand(v) { 
Entity::Entity(const Operand &v)  {
  //value_ = visit(GetValue(), v.value_);
  value_ = visit(GetOperandValue(), v.value_);
  type_  = v.type_;
  parent = nullptr;
} 
Entity::Entity(const Entity &v) { parent = nullptr; } 

Operand Entity::_get_operand() { 
  Operand nv= type_;
  //nv.value_ = visit(GetValue(), this->value_); 
  nv.value_ = visit(GetOperandValue(), this->value_); 
  return nv;
}
//------------------------------------- entity : list
ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& ptr) {
  return os;
}

