#include "entity.hh"


const Entity &Entity::operator[](int i) const { 
  return members[i]; 
};
Entity &Entity::operator[](int i) {
  return members[i]; 
};

void Entity::list_add(Entity e) {
  members.push_back(e);
};

void Entity::list_print() const {
    int i, s = members.size();

    cout << "[";
    for(i=0; i<s-1; i++) { cout << members[i] << ","; }
    cout << members[i] << "]";
}




ostream& operator<<(ostream& os, const Entity& e) {
  switch(e.type_get()) {
  case OperandType::list_t:
    //cout << "it is a list!\n";
    e.list_print();
    break;
  case OperandType::map_t:
    cout << "it is a map!\n";
    break;
  default: 
    cout << e.get_operand();
    break;
  }
  return os;
}
