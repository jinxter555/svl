#include "entity.hh"

//Entity::Entity() : value_(nil) {}
//Entity::Entity(const Operand &v)  { value_ = visit(GetOperandValue(), v.value_); }

ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& ptr) {
  //cout << "ptr:";
  ptr->print();
  return os;
}
