#include "entity.hh"


Entity::Entity() { 
  value_ = nil;
  parent = nullptr; 
}

Entity::Entity(const Operand &v)  {
  value_ = visit(GetOperandValue(), v.value_);

  parent = nullptr;
} 

Entity::Entity(const Entity &v) { 
  parent = nullptr; 
  value_ = visit(GetOperandValue(), v.value_);
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

//----------------------------
VEntity::VEntity() { }
VEntity::VEntity(const Operand& v) : Entity(v){}