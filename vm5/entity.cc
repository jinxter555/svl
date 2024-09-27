#include "entity.hh"

//Entity Entity::entity_undef_error=Operand(OperandErrorCode::undefined_t);
//Entity Entity::entity_mem_error=Operand(OperandErrorCode::mem_alloc_t);

//------------------------------------- entity : unique ptr 
/*
entity_u_ptr Entity::clone() const {
//  return make_unique<Entity>(*this);
 //return make_unique<Entity>(this->_get_operand());
// auto n = make_unique<Entity>();
}

entity_u_ptr Entity::clone_operand() const {
  return make_unique<Entity>(this->_get_operand());
}*/

Entity::Entity(const Entity &v) {
  //cout << "entity::entity(): \n";
/*
  switch(v.get_type()){
  case OperandType::list_t:{
    for(auto &e : v.members) {
      members.push_back(e->clone()); }
    type_ = OperandType::list_t;
    return; }
  case OperandType::map_t: { 
    for (auto const& [key, val] : v.children) {
      children[key] = val->clone(); }
    type_ = OperandType::map_t;
    return; }
  default: 
  }*/
    value_ = v.value_;
    type_ = v.type_;
} 

//------------------------------------- entity : list
void Entity::list_print() const {
    int i, s = members.size();
    if(s==0) {cout << "[]"; return;}

    cout << "[";
    for(i=0; i<s-1; i++) { cout << *members[i] << ","; }
    cout << *members[i] << "]";
}

//------------------------------------- entity : map 
void Entity::map_print() const {
/*
  for(auto const& [key, val] : children) {
    cout << key << ": " << *val << "\n";
  }
*/
}
ostream& operator<<(ostream& os, const Entity& e) {
  switch(e.get_type()) {
  case OperandType::list_t:
    //cout << "it is a list size: " << e.members.size() << "\n";
    e.list_print();
    break;
  case OperandType::map_t:
    // cout << "it is a map!\n";
    e.map_print();
    break;
  default: 
    cout << e._get_operand();
    break;
  }
  return os;
}

ostream& operator<<(ostream& os, const entity_u_ptr& vptr) {
  cout << *vptr;
  return os;
}
