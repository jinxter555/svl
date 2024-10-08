#include "entity.hh"

Entity::Entity() : Primordial(OperandType::nil_t) {}
Entity::Entity(const OperandType &t) : Primordial(t) {}

ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& ptr) {
  //cout << "ptr:";
  ptr->print();
  return os;
}
