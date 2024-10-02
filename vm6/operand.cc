#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"
#include "operand_tostr.hh"
#include "entity.hh"

Nil nil;
const string Operand::nil_str=string("nil");
//Operand(int value) ; //Operand(float value) ;
  
Operand::Operand() { value_ = nil; }
Operand::Operand(bool v) : value_(v) {}
Operand::Operand(s_integer v) : value_ (Number(v)) {}
Operand::Operand(s_float v) : value_(Number(v)) {   }
Operand::Operand(const Number& v) : value_(v) {     ;}

Operand::Operand(OperandType v) : value_(v) {} //  meta program type of types
Operand::Operand(AstOpCode v) : value_(v) {} //  just type
Operand::Operand(OperandErrorCode v) : value_(v) {} //  just type
Operand::Operand(OperandStatusCode v) : value_(v) {} //  just type

Operand::Operand(const OperandVariant& v ) { value_ = visit(GetOperandValue(), v); } 
Operand::Operand(const string& v) : value_(v) {}
Operand::Operand(const char* v) : value_(string(v)) {}

Operand::Operand(entity_u_ptr vptr)   { value_= move(vptr); }
Operand::Operand(list_u_ptr vptr)   { value_= move(vptr); }
//-----------------------------------------------------------------------
OperandType Operand::_get_type() const { 
  return( visit(GetOperandType(), value_));
};

Operand Operand::get_type() const {
  return( visit(GetOperandType(), value_));
}

//---------------------------  for cout print out or other viewers
Operand Operand::get_str() const {
  return to_str();
}
Operand Operand::to_str() const {
  return Operand(
    visit(OperandToStringVisitor(), value_)
  );
}
//---------------------------  for cout print out or other viewers
const string Operand::_get_str() const { 
  return  _to_str();
}
const string Operand::_to_str() const { 
  //OperandType type = visit(GetOperandType(), value_);
   if (holds_alternative<string>(value_))
    return get<string>(value_); 
  return to_str()._to_str();
}
//---------------------------  for cout print out or other viewers
Number Operand::_get_number() const { 
  return get<Number>(value_); 
}
s_integer Operand::_get_int() const { 
  Number n = _get_number(); 
  return get<s_integer>(n.get_data()); 
}
s_float Operand::_get_float() const { 
  Number n = _get_number();
  return get<s_float>(n.get_data()); 
}
//-----------------------------------------------------------------------
e_members_t& Operand::_get_members() {
  return get<e_members_t>(value_); 

};
//-----------------------------------------------------------------------
Operand Operand::whatami() const {
  Operand w = get_type();
  if(_get_type() == OperandType::err_t) {
    OperandErrorCode err = get<OperandErrorCode>(value_);
    return w +  Operand(": ")._to_str() + OperandToStringVisitor()(err);
  }
  return w;
}

//-----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Operand& operand) {
  cout << operand._to_str();
  return os;
}

//-----------------------------------------------------------------------
template <typename T>
OperandVariant GetOperandValue::operator()(T value) const { return value; }
OperandVariant GetOperandValue::operator()(const entity_u_ptr& v) const { return v->clone(); }
OperandVariant GetOperandValue::operator()(const list_u_ptr& v) const { return v->clone(); }
OperandVariant GetOperandValue::operator()(Entity *v) const { return v->clone(); }  
OperandVariant GetOperandValue::operator()(const e_members_t& v) const { 
  return false;
}

//-----------------------------------------------------------------------
OperandType GetOperandType::operator()(const Nil& v) const  { return OperandType::nil_t; }
OperandType GetOperandType::operator()(const bool v) const  { return OperandType::bool_t; }
OperandType GetOperandType::operator()(const entity_u_ptr& v) const { return OperandType::ptr_t;}
OperandType GetOperandType::operator()(const list_u_ptr& v) const { return OperandType::ptr_t;}
OperandType GetOperandType::operator()(Entity *v) const { return OperandType::ptr_t;}
OperandType GetOperandType::operator()(const e_members_t& v) const { return OperandType::list_t; }
OperandType GetOperandType::operator()(const string& v) const { return OperandType::str_t; }
OperandType GetOperandType::operator()(const Number& v) const { return OperandType::num_t; }
OperandType GetOperandType::operator()(const AstOpCode& v) const { return OperandType::ast_op_t; }
OperandType GetOperandType::operator()(const OperandType& v) const { return OperandType::type_t; }
OperandType GetOperandType::operator()(const OperandStatusCode& v) const { return OperandType::status_t; }
OperandType GetOperandType::operator()(const OperandErrorCode& v) const { return OperandType::err_t; }