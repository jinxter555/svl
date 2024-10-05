#include "entity.hh"

OperandEntity::OperandEntity()  {}
OperandEntity::OperandEntity(const Operand &v) : Entity(v) {}
OperandEntity OperandEntity::operator=(const OperandEntity &v) { 
  set(v); 
  return *this; 
}

void OperandEntity::set(const OperandEntity &v) {
  value_ = visit(GetOperandValue(), v.value_); 
}

entity_u_ptr OperandEntity::clone() const { 
  return make_unique<OperandEntity>(*this);
}

Operand OperandEntity::_get_operand() const { 
  Operand nv; //nv.value_ = visit(GetValue(), this->value_); 
  nv.value_ = visit(GetOperandValue(), this->value_); 
  return nv;
}

const string OperandEntity::_to_str() const {
  return Operand::_to_str();
}
OperandEntity OperandEntity::to_str() const {
  if (holds_alternative<string>(value_))
    return *this;
  return OperandEntity(Operand::to_str());
};

void OperandEntity::print() const {
//  cout << "opent print\n";
  cout << _to_str();
};