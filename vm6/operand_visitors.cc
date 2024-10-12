#include "operand_visitors.hh"

//-----------------------------------------------------------------------
template <typename T>
OperandVariant GetOperandValue::operator()(T value) const { return value; }
OperandVariant GetOperandValue::operator()(const entity_u_ptr& v) const { return v->clone(); }

/*
OperandVariant GetOperandValue::operator()(const list_u_ptr& v) const { return v->clone(); }
OperandVariant GetOperandValue::operator()(Entity *v) const { return v->clone(); }  
OperandVariant GetOperandValue::operator()(const e_members_t& v) const { return false; }
OperandVariant GetOperandValue::operator()(const e_children_t& v) const { return false; }
*/
//-----------------------------------------------------------------------
template <typename T>
operand_u_ptr GetOperandClone::operator()(T value) const { 
  return make_unique<T>(value); 
}
operand_u_ptr GetOperandClone::operator()(const entity_u_ptr& v) const { 
  return make_unique<Operand>(v->clone()); 
}

//-----------------------------------------------------------------------
OperandType GetOperandType::operator()(const Nil& v) const  { return OperandType::nil_t; }
OperandType GetOperandType::operator()(const bool v) const  { return OperandType::bool_t; }

OperandType GetOperandType::operator()(const AstOpCode& v) const { return OperandType::ast_op_t; }
OperandType GetOperandType::operator()(const OperandType& v) const { return OperandType::type_t; }
OperandType GetOperandType::operator()(const OperandStatusCode& v) const { return OperandType::status_t; }
OperandType GetOperandType::operator()(const OperandErrorCode& v) const { return OperandType::err_t; }

OperandType GetOperandType::operator()(const Number& v) const { return OperandType::num_t; }
OperandType GetOperandType::operator()(const string& v) const { return OperandType::str_t; }

OperandType GetOperandType::operator()(const entity_u_ptr& v) const { return OperandType::ptr_t;}
/*
OperandType GetOperandType::operator()(const list_u_ptr& v) const { return OperandType::ptr_t;}
OperandType GetOperandType::operator()(Entity *v) const { return OperandType::ptr_t;}
OperandType GetOperandType::operator()(const e_members_t& v) const { return OperandType::list_t; }
OperandType GetOperandType::operator()(const e_children_t& v) const { return OperandType::map_t; }
*/