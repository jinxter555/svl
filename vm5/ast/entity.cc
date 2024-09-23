#include "entity.hh"

//ostream& operator<<(ostream& os, const Entity& e);

const Entity &Entity::operator[](int i) const {

 return members[i];
};

Entity &Entity::operator[](int i) {
    return members[i];
};

ostream& operator<<(ostream& os, const Entity& e) {
  switch(e.e_type_) {
  case OperandType::list_t:
    cout << "it is a list!\n";
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
