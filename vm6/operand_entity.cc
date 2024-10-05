#include "entity.hh"

OperandEntity nil_entity;

OperandEntity::OperandEntity()  {}
OperandEntity::OperandEntity(const Operand &v) : value_(v), type_(v.type_) { }
OperandEntity OperandEntity::operator=(const OperandEntity &v) { 
  value_ = v.value_;
  type_ =  v.type_;
  return *this; 
}

entity_u_ptr OperandEntity::clone() const { 
  return make_unique<OperandEntity>(*this);
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

s_integer OperandEntity::_get_int() const { return value_._get_int(); }
s_float OperandEntity::_get_float() const { return value_._get_float(); }

Operand OperandEntity::_get_operand() const { 
  return visit(GetOperandValue(), value_.value_); 
}
OperandEntity OperandEntity::get_type() const {
  return Operand(type_);
};