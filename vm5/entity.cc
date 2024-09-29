#include "entity.hh"

entity_u_ptr *Entity::error=nullptr;

Entity::Entity(const Entity &v) {
    value_ = v.value_;
    type_ = v.type_;
} 

//------------------------------------- entity : list
ostream& operator<<(ostream& os, const Entity& e) {
  e.print();
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& vptr) {
  cout << *vptr;
  return os;
}
