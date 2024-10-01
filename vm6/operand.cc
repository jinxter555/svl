#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"
#include "operand_tostr.hh"
#include "entity.hh"

const string Operand::nil_str=string("nil");
//Operand(int value) ; //Operand(float value) ;
  
Operand::Operand() { type_ = OperandType::nil_t; }
Operand::Operand(bool v) : value_(v), type_(OperandType::bool_t) {}
Operand::Operand(s_integer v) : value_ (Number(v)) {type_ = OperandType::num_t;}
Operand::Operand(s_float v) : value_(Number(v)) {   type_ = OperandType::num_t;}
Operand::Operand(const Number& v) : value_(v) {     type_ = OperandType::num_t;}
Operand::Operand(OperandType t) : type_(t) {} //  meta program type of types
Operand::Operand(OperandType t, const OperandVariant& v ) : type_(t) { 
  value_ = visit(GetOperandValue(), v); 
  } 
Operand::Operand(AstOp v) : type_(OperandType::ast_op_t), value_(v) {} //  just type
Operand::Operand(OperandErrorCode v) : type_(OperandType::err_t), value_(v) {} //  just type
Operand::Operand(OperandStatusCode v) : value_(v) {} //  just type
Operand::Operand(const string& v) : value_(v), type_(OperandType::str_t) {}
Operand::Operand(const char* v) : value_(string(v)) { type_ = OperandType::str_t; }
Operand::Operand(entity_u_ptr vptr)   { value_= move(vptr); }

//-----------------------------------------------------------------------

void Operand::set_type(const OperandType &t) { type_= t; };
OperandType Operand::_get_type() const { return type_;};

Operand Operand::get_type() const {
  return(
    Operand(OperandType::type_t, _get_type())
  );
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
  if(type_==OperandType::str_t) { 
    return get<string>(value_); 
  }
  if(type_==OperandType::nil_t) return nil_str;
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
Operand Operand::whatami() const {
  Operand w = OperandToStringVisitor()(type_);
  if(type_ == OperandType::err_t) {
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

template <typename T>
OperandVariant GetOperandValue::operator()(T value) const { return value; }
OperandVariant GetOperandValue::operator()(const entity_u_ptr& v) const { return v->clone(); }                                                                                                                                                                      
OperandVariant GetOperandValue::operator()(Entity *v) const { return v->clone(); }  

/*
template <typename T>
OperandVariant Operand::GetValue::operator()(T value) const { return value; }
OperandVariant Operand::GetValue::operator()(const entity_u_ptr& v) const { return v->clone(); }                                                                                                                                                                      
OperandVariant Operand::GetValue::operator()(Entity *v) const { return v->clone(); }  

OperandVariant Operand::GetValue::operator()(const string &s) const { return s; }
OperandVariant Operand::GetValue::operator()(const Number &n) const {return n; }
OperandVariant Operand::GetValue::operator()(const OperandStatusCode n) const {return n; }
OperandVariant Operand::GetValue::operator()(const OperandErrorCode n) const {return n; }
OperandVariant Operand::GetValue::operator()(const OperandType n) const {return n; }
OperandVariant Operand::GetValue::operator()(bool n) const {return n; }
OperandVariant Operand::GetValue::operator()(AstOp n) const {return n; }
*/
