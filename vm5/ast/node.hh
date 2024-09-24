#include "entity.hh"

class Node : public Entity {
  void add(string k, entity_ptr vptr) {
    children[k] = vptr;
  }
  void add_data(string k, Entity e) {


  }
};