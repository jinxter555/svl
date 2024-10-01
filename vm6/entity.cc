#include "entity.hh"


Entity::Entity() { parent = nullptr; }
Entity::Entity(const Operand &v) : Operand(v) { parent = nullptr; } 
Entity::Entity(const Entity &v) { parent = nullptr; } 
//------------------------------------- entity : list
ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& ptr) {
  return os;
}
