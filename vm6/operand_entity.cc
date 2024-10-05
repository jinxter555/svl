#include "entity.hh"

OperandEntity::OperandEntity()  {}
OperandEntity::OperandEntity(const Operand &v) : Entity(v) {}
OperandEntity OperandEntity::operator=(const OperandEntity &v) { 
  value_ = v.value_;
  type_ =  v.type_;
  return *this; 
}

void OperandEntity::set(const OperandEntity &v) {
  value_ = visit(GetOperandValue(), value_.value_); 
  type_ = v.type_; 
}

entity_u_ptr OperandEntity::clone() const { 
  return make_unique<OperandEntity>(*this);
}

Operand OperandEntity::_get_operand() const { 
  return visit(GetOperandValue(), value_.value_); 
}

const string OperandEntity::_to_str() const {
  return value_._to_str();
}
OperandEntity OperandEntity::to_str() const {
  if (holds_alternative<string>(value_.value_))
    return *this;
  return OperandEntity(value_.to_str());
};

void OperandEntity::print() const {
//  cout << "opent print\n";
  cout << _to_str();
};
OperandEntity OperandEntity::opfunc(const OperandEntity& other, AstOpCode op) {
  return value_.opfunc(other.value_, op);
}