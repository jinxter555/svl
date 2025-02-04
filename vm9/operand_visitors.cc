#include "operand.hh"
#include "operand_vars.hh"
#include <utility>

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//----------------------------------------------------------------------- Type
OperandType Operand::Type::operator()(const Nil& v) const  { return OperandType::nil_t; }
OperandType Operand::Type::operator()(const bool v) const  { return OperandType::bool_t; }

OperandType Operand::Type::operator()(const AstOpCode& v) const { return OperandType::ast_op_t; }
OperandType Operand::Type::operator()(const ControlFlow& v) const { return OperandType::control_flow_t; }
OperandType Operand::Type::operator()(const OperandType& v) const { return OperandType::type_t; }
OperandType Operand::Type::operator()(const OperandStatusCode& v) const { return OperandType::status_t; }
OperandType Operand::Type::operator()(const OperandErrorCode& v) const { return OperandType::err_t; }

OperandType Operand::Type::operator()(const Number& v) const { return OperandType::num_t; }
OperandType Operand::Type::operator()(const string& v) const { return OperandType::str_t; }

OperandType Operand::Type::operator()(const astnode_u_ptr& v) const { return OperandType::uptr_t;}
OperandType Operand::Type::operator()(const astnode_s_ptr& v) const { return OperandType::sptr_t;}
OperandType Operand::Type::operator()(const astnode_ptr& v) const { return OperandType::ptr_t;}
OperandType Operand::Type::operator()(const svlm_ast_ptr& v) const { return OperandType::svlm_ast_ptr_t;}

//-----------------------------------------------------------------------  OpCode
Operand     Operand::get_opcode()     const { return _get_opcode(); }
AstOpCode   Operand::_get_opcode()    const { return visit(OpCode{}, value_); }
//------------------------------------ 
template <typename T> 
AstOpCode Operand::OpCode::operator()(T& v) const { return AstOpCode::noop; }
AstOpCode Operand::OpCode::operator()(const AstOpCode v) const { return v; }
AstOpCode Operand::OpCode::operator()(const Nil) const {  return AstOpCode::noop; }


//----------------------------------------------------------------------- Vrptr
// recursive pointer until finds it
astnode_ptr Operand::_vrptr() const {
  MYLOGGER(trace_function, "Operand::_vrptr()", __func__, SLOG_FUNC_INFO+39);
  //switch(_get_type()) {

  switch(type_) {
  case OperandType::ptr_t:
  case OperandType::uptr_t:
  case OperandType::sptr_t:
    return visit(Vrptr(), value_);
  }
  //auto vptr=   visit(Vrptr(), value_); if(vptr==nullptr)
  return (astnode_ptr)this;
}
//---
template <typename T> 
astnode_ptr Operand::Vrptr::operator()(const T& value) const { return nullptr; }
astnode_ptr Operand::Vrptr::operator()(const Nil) const { return nullptr; }
astnode_ptr Operand::Vrptr::operator()(const astnode_ptr& vptr) const  { 
  if(vptr==nullptr) return nullptr;
  return vptr->_vrptr(); 
}
astnode_ptr Operand::Vrptr::operator()(const astnode_s_ptr& vptr) const { 
  if(vptr==nullptr) return nullptr;
  return vptr->_vrptr();
}
astnode_ptr Operand::Vrptr::operator()(const astnode_u_ptr& vptr) const  { 
  if(vptr==nullptr) return nullptr;
  return vptr->_vrptr(); 
}

//----------------------------------------------------------------------- Uptr
/*
struct Uptr {
template <typename T> 
const operand_u_ptr& operator()(const T& v) const;
const operand_u_ptr& operator()(const operand_ptr& v) const;
const operand_u_ptr& operator()(const operand_u_ptr& v) const;
const operand_u_ptr& operator()(const operand_s_ptr& v) const;
};
*/
const astnode_u_ptr& Operand::get_u_ptr() const {
 return visit(Uptr(), value_);
}
astnode_u_ptr& Operand::get_u_ptr_nc() { 
  return const_cast<astnode_u_ptr&>(as_const(this->get_u_ptr())); 
}


template <typename T> 
const astnode_u_ptr& Operand::Uptr::operator()(const T& v) const { return nil_ast_ptr; }
const astnode_u_ptr& Operand::Uptr::operator()(const Nil) const { return nil_ast_ptr; }
const astnode_u_ptr& Operand::Uptr::operator()(const astnode_u_ptr& v) const { return v; }
const astnode_u_ptr& Operand::Uptr::operator()(const astnode_s_ptr& v) const{ return v->get_u_ptr(); }
const astnode_u_ptr& Operand::Uptr::operator()(const astnode_ptr& v) const{ return v->get_u_ptr(); }


//----------------------------------------------------------------------- Rptr
//------------------------------------ 
astnode_ptr Operand::get_raw_ptr() const {
  auto rptr = visit(Rptr(), value_);
  if(rptr==nullptr)
    return (operand_ptr)this;
  return rptr;
}
template <typename T> 
const astnode_ptr Operand::Rptr::operator()(const T& v) const { return nullptr; }
const astnode_ptr Operand::Rptr::operator()(const Nil v) const { return nullptr; }
const astnode_ptr Operand::Rptr::operator()(const astnode_ptr& vptr) const { return vptr; }
const astnode_ptr Operand::Rptr::operator()(const astnode_s_ptr& vptr) const { return vptr.get(); }
const astnode_ptr Operand::Rptr::operator()(const astnode_u_ptr& vptr) const { return vptr.get(); }

//----------------------------------------------------------------------- Variant
operand_variant_t Operand::_get_variant() const {
  MYLOGGER(trace_function , "Operand::_get_variant()" ,__func__, SLOG_FUNC_INFO);
  return visit(Variant(), value_);
};
//------------------------------------ 
template <typename T> 
operand_variant_t Operand::Variant::operator()(const T &v) const { return v; }
operand_variant_t Operand::Variant::operator()(const Nil v) const { return nil; }
operand_variant_t Operand::Variant::operator()(const astnode_ptr& vptr) const { 
  //if(vptr==nullptr){cerr << "Operand::Variant::operator(astnode_s_ptr&) null!\n"; return nil;}
  if(vptr==nullptr){return nil;}
  return vptr;
//  return vptr->clone(); 
}
operand_variant_t Operand::Variant::operator()(const astnode_s_ptr& vptr) const { 
  //if(vptr==nullptr){cerr << "Operand::Variant::operator(astnode_s_ptr&) null!\n"; return nil;}
  if(vptr==nullptr){return nil;}
  return vptr;
//  return vptr->clone(); 
}
operand_variant_t Operand::Variant::operator()(const astnode_u_ptr& vptr) const { 
  //if(vptr==nullptr){cerr << "Operand::Variant::operator(astnode_u_ptr&) null!\n"; return nil;}
  if(vptr==nullptr){return nil;}
  return vptr->clone(); 
}