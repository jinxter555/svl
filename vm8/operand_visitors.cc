#include "operand.hh"
#include "operand_vars.hh"

//----------------------------------------------------------------------- Type
OperandType Operand::Type::operator()(const Nil& v) const  { return OperandType::nil_t; }
OperandType Operand::Type::operator()(const bool v) const  { return OperandType::bool_t; }

OperandType Operand::Type::operator()(const AstOpCode& v) const { return OperandType::ast_op_t; }
OperandType Operand::Type::operator()(const ControlFlow& v) const { return OperandType::control_t; }
OperandType Operand::Type::operator()(const OperandType& v) const { return OperandType::type_t; }
OperandType Operand::Type::operator()(const OperandStatusCode& v) const { return OperandType::status_t; }
OperandType Operand::Type::operator()(const OperandErrorCode& v) const { return OperandType::err_t; }

OperandType Operand::Type::operator()(const Number& v) const { return OperandType::num_t; }
OperandType Operand::Type::operator()(const string& v) const { return OperandType::str_t; }

OperandType Operand::Type::operator()(const astexpr_u_ptr& v) const { return OperandType::ast_uptr_t;}
OperandType Operand::Type::operator()(const operand_u_ptr& v) const { return OperandType::uptr_t;}
OperandType Operand::Type::operator()(const operand_s_ptr& v) const { return OperandType::sptr_t;}
OperandType Operand::Type::operator()(const operand_ptr& v) const { return OperandType::ptr_t;}
OperandType Operand::Type::operator()(const list_t& v) const { return OperandType::list_t;}
OperandType Operand::Type::operator()(const map_t& v) const { return OperandType::map_t;}

//----------------------------------------------------------------------- Type