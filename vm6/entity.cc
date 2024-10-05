#include "entity.hh"

Entity::Entity() { value_ = Operand();}

Entity::Entity(const Operand &v)   {
  //value_ = visit(GetOperandValue(), v.value_);
  value_ = v;
  type_ = v.type_;
} 

Entity::Entity(const Entity &v) { 
  //value_ = visit(GetOperandValue(), v.value_.value_);
  value_ = v.value_;
  type_ = v.type_;
} 

ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& ptr) {
  //cout << "ptr:";
  ptr->print();
  return os;
}

s_integer Entity::_get_int() const { return value_._get_int(); }
s_float Entity::_get_float() const { return value_._get_float(); }
string Entity::_to_str() const { return value_._to_str(); }
Operand Entity::_get_operand() const { return value_; };
OperandEntity Entity::get_type() const { 
  return Operand(type_); 
};

//----------------------------
VEntity::VEntity()  {}
VEntity::VEntity(const Operand& v) : Entity(v){}