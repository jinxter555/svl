#include "operand.hh"
#include <iostream>

Nil nil;
const Operand nil_operand=Operand();
ostream& operator<<(ostream& os, const Operand& v);

Operand::Operand() {value_=nil;}
Operand::Operand(const Nil&n) {value_=nil;}
Operand::Operand(const s_float v) : value_(v) {}
Operand::Operand(const s_integer v) : value_(v) {}
Operand::Operand(const Number& v) : value_(v) {}
Operand::Operand(const char*v) : value_(string(v)) {}
Operand::Operand(const string& v) : value_(v) {}
Operand::Operand(const bool v) : value_(v) {}
Operand::Operand(const OperandType &v)  : value_(v){};
Operand::Operand(const AstOpCode& v) : value_(v) {};
Operand::Operand(const OperandErrorCode &v): value_(v) {};
Operand::Operand(const OperandStatusCode &v): value_(v) {};
Operand::Operand(const ControlFlow &v ) : value_(v) {};
Operand::Operand(operand_u_ptr&v ) : value_(move(v->clone())) {};
Operand::Operand(operand_u_ptr&&v ) : value_(move(v)) {};
Operand::Operand(operand_s_ptr v) : value_(move(v->clone())) {};
Operand::Operand(operand_ptr v) : value_(move(v->clone())) {};

Operand::Operand(const list_t &v ) { value_ = make_unique<Operand>() ; };
Operand::Operand(const map_t &v ) { value_ = make_unique<Operand>() ; };

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

