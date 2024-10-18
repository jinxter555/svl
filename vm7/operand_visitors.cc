#include "operand.hh"

//-----------------------------------------------------------------------
OperandType GetOperandType::operator()(const Nil& v) const  { return OperandType::nil_t; }
OperandType GetOperandType::operator()(const bool v) const  { return OperandType::bool_t; }

OperandType GetOperandType::operator()(const AstOpCode& v) const { return OperandType::ast_op_t; }
OperandType GetOperandType::operator()(const OperandType& v) const { return OperandType::type_t; }
OperandType GetOperandType::operator()(const OperandStatusCode& v) const { return OperandType::status_t; }
OperandType GetOperandType::operator()(const OperandErrorCode& v) const { return OperandType::err_t; }

OperandType GetOperandType::operator()(const Number& v) const { return OperandType::num_t; }
OperandType GetOperandType::operator()(const string& v) const { return OperandType::str_t; }

OperandType GetOperandType::operator()(const astexpr_u_ptr& v) const { return OperandType::ptr_t;}