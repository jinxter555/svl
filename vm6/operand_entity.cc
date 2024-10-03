#include "entity.hh"

OperandEntity::OperandEntity()  {}
OperandEntity::OperandEntity(const Operand &v) : Entity(v) {}

entity_u_ptr OperandEntity::clone() const { 
  return make_unique<OperandEntity>(*this);
}

Operand OperandEntity::to_str() const {
  return Operand::to_str();
};

void OperandEntity::print() const {
//  cout << "opent print\n";
  cout << to_str();
};