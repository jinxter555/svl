#include "operand.hh"
#include <iostream>

Nil nil;
const Operand nil_operand=Operand();
ostream& operator<<(ostream& os, const Operand& v);

Operand::Operand()                  : type_(OperandType::nil_t),  value_(nil) {}
Operand::Operand(const Nil&n)       : type_(OperandType::nil_t), value_(nil) {}
Operand::Operand(const s_float v)   : type_(OperandType::num_t),  value_(v) {}
Operand::Operand(const s_integer v) : type_(OperandType::num_t), value_(v) {}
Operand::Operand(const Number& v)   : type_(OperandType::num_t), value_(v) {}
Operand::Operand(const char*v)      : type_(OperandType::str_t), value_(string(v)) {}
Operand::Operand(const string& v)   : type_(OperandType::str_t), value_(v) {}
Operand::Operand(const bool v)      : type_(OperandType::bool_t), value_(v) {}
Operand::Operand(const OperandType &v)        : type_(OperandType::type_t), value_(v){};
Operand::Operand(const AstOpCode& v)          : type_(OperandType::ast_op_t), value_(v) {};
Operand::Operand(const OperandErrorCode &v)   : type_(OperandType::err_t),    value_(v) {};
Operand::Operand(const OperandStatusCode &v)  : type_(OperandType::status_t), value_(v) {};
Operand::Operand(const ControlFlow &v )       : type_(OperandType::control_t), value_(v) {};
Operand::Operand(const operand_u_ptr&v )      : type_(OperandType::uptr_t), value_(move(v->clone())) {};
Operand::Operand(operand_u_ptr&&v )           : type_(OperandType::uptr_t), value_(move(v)) {};
Operand::Operand(const operand_s_ptr& v)      : type_(OperandType::sptr_t), value_(move(v->clone())) {};
Operand::Operand(const operand_ptr v)         : type_(OperandType::ptr_t),  value_(move(v->clone())) {};
Operand::Operand(const list_t &v ) : type_(OperandType::list_t) { value_ = make_unique<Operand>() ; };
Operand::Operand(const map_t &v ) : type_(OperandType::map_t) { value_ = make_unique<Operand>() ; };

//------------------------------------
operand_u_ptr Operand::clone() const { return visit(Clone{}, value_); }
//------------------------------------
Operand Operand::to_str() const { return visit(ToString{}, value_); }

string Operand::_to_str() const { 
  if (holds_alternative<string>(value_)) 
    return get<string>(value_); 
  return to_str()._to_str();
}
//------------------------------------
Operand Operand::get_type() const { return _get_type(); }
//Operand     Operand::get_opcode()     const { return _get_opcode(); }
//---------------------------  
OperandType Operand::_get_type() const { return type_; };
//AstOpCode   Operand::_get_opcode()    const { return visit(OpCode{}, value_); }
//------------------------------------
const Operand& Operand::get_value() const { return visit(Value{}, value_); }
//------------------------------------
void Operand::print() const { cout << *this; }
//------------------------------------
template <typename T> 
operand_u_ptr Operand::Clone::operator()(const T& v) const { return make_unique<Operand>(v); }
operand_u_ptr Operand::Clone::operator()(const operand_ptr& v) const { return v->clone(); }
operand_u_ptr Operand::Clone::operator()(const operand_u_ptr& v) const {return v->clone(); } 
operand_u_ptr Operand::Clone::operator()(const operand_s_ptr& v) const { return v->clone(); } 
operand_u_ptr Operand::Clone::operator()(const Nil v) const { return nullptr; }
//------------------------------------
template <typename T> 
const Operand& Operand::Value::operator()(T &v) const  { return *(Operand*)this;}
const Operand& Operand::Value::operator()(const Nil) const {return nil_operand; }
const Operand& Operand::Value::operator()(operand_ptr& v) const  {return v->get_value(); }
const Operand& Operand::Value::operator()(operand_u_ptr& v) const {return v->get_value();}
const Operand& Operand::Value::operator()(operand_s_ptr& v) const {return v->get_value();}
//------------------------------------

//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const Operand& v) {
  cout << v._to_str();
  return os;
}

ostream& operator<<(ostream& os, const operand_u_ptr& ptr) {
  if(ptr==nullptr) { cout << "operand_u_ptr is null\n"; } 
  else ptr->print();
  return os;
}
ostream& operator<<(ostream& os, const operand_s_ptr& ptr) {
  if(ptr==nullptr) { cout << "operand_s_ptr is null\n"; } 
  else ptr->print();
  return os;
}
ostream& operator<<(ostream& os, const operand_ptr& ptr) {
  if(ptr==nullptr) { cout << "operand_ptr is null\n"; } 
  else ptr->print();
  return os;
}

