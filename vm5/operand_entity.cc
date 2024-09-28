#include "operand_entity.hh"

OperandEntity OperandEntity::undef_error=Operand(OperandErrorCode::undefined_t);
OperandEntity OperandEntity::mem_error=Operand(OperandErrorCode::mem_alloc_t);
entity_u_ptr OperandEntity::error=nullptr;

OperandEntity::OperandEntity() : Entity(OperandType::nil_t){}
OperandEntity::OperandEntity(const Operand &v) : Entity(v) {}

entity_u_ptr OperandEntity::clone() const { 
  return make_unique<OperandEntity>(*this);
}


void OperandEntity::print() const {
  //cout << _get_operand();
  cout << Operand::_to_str();
};