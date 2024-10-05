#include "entity.hh"

Entity::Entity() { value_ = nil; parent = nullptr; }

Entity::Entity(const OperandType t)  : Operand(t) {
  //value_=nil;
}

Entity::Entity(const Operand &v)  {
  type_ = v.type_;
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
VEntity::VEntity() {
  value_ = nil;
  parent = nullptr; 
}
VEntity::VEntity(const Operand& v) : Entity(v){
  cout << "i am in ventity\n";
  cout << v << "\n";

}