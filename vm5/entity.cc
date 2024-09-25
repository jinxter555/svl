#include "entity.hh"

Entity Entity::entity_undef_error=Operand(OperandErrorCode::undefined_t);

//------------------------------------- entity : list
void Entity::list_print() const {
    int i, s = members.size();
    if(s==0) {cout << "[]"; return;}

    cout << "[";
    for(i=0; i<s-1; i++) { cout << members[i] << ","; }
    cout << members[i] << "]";
}

//------------------------------------- entity : map 
void Entity::map_print() const {
  for(auto const& [key, val] : children) {
    cout << key << ": " << *val << "\n";
  }
}

ostream& operator<<(ostream& os, const Entity& e) {
  switch(e.type_get()) {
  case OperandType::list_t:
    //cout << "it is a list!\n";
    e.list_print();
    break;
  case OperandType::map_t:
    cout << "it is a map!\n";
    e.map_print();
    break;
  default: 
    cout << e.get_operand();
    break;
  }
  return os;
}
