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
Operand::Operand(s_integer v) : value_ (v) {type_ = OperandType::s_int_t;}
Operand::Operand(s_float v) : value_(v) {   type_ = OperandType::s_float_t;}
Operand::Operand(OperandType t) : type_(t) {} //  meta program type of types
Operand::Operand(AstOp v) : type_(OperandType::ast_op_t), value_(v) {} //  just type
Operand::Operand(OperandErrorCode v) : type_(OperandType::err_t), value_(v) {} //  just type
Operand::Operand(OperandStatusCode v) : value_(v) {} //  just type
Operand::Operand(const string& v) : value_(v), type_(OperandType::str_t) {}
Operand::Operand(const char* v) : value_(string(v)) { type_ = OperandType::str_t; }
//Operand::Operand(const entity_u_ptr &vptr)   { //value_= make_unique<Entity>(*vptr); }

//-----------------------------------------------------------------------
Operand Operand::get_str() const {
  return to_str();
}
Operand Operand::to_str() const {
  return Operand(
    variant_visit(OperandToStringVisitor(), value_)
  );
}
//---------------------------  for cout print out or other viewers
const string Operand::_get_str() const { 
  return  _to_str();
}
const string Operand::_to_str() const { 
  if(type_==OperandType::str_t) { 
    return variant_get<string>(value_); 
  }
  if(type_==OperandType::nil_t) return nil_str;
  return to_str()._to_str();
}
//---------------------------  for cout print out or other viewers
s_integer Operand::_get_int() const { return variant_get<s_integer>(value_); }
s_float Operand::_get_float() const { return variant_get<s_float>(value_); }
//-----------------------------------------------------------------------
std::ostream& operator<<(std::ostream& os, const Operand& operand) {
  cout << operand._to_str();
  return os;
}