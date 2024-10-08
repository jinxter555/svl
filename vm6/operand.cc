#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"
#include "operand_tostr.hh"
#include "entity.hh"

Nil nil;
Operand nil_operand=Operand();

//Primordial::Primordial(OperandType t) : Primordial(t) {}

const string Operand::nil_str=string("nil");
  
Operand::Operand() 
  : Primordial(OperandType::nil_t)
  , value_(nil) {}
Operand::Operand(bool v)
  : Primordial(OperandType::bool_t)
  , value_(v) {}
Operand::Operand(s_integer v) 
  : Primordial(OperandType::num_t)
  , value_(Number(v)) {}
Operand::Operand(s_float v) 
  : Primordial(OperandType::num_t)
  , value_(Number(v)) {}
Operand::Operand(const Number& v) 
  : Primordial(OperandType::num_t)
  , value_(v) {}
Operand::Operand(OperandType v) 
  : Primordial(OperandType::type_t)
  , value_(v) {} //  meta program type of types
Operand::Operand(AstOpCode v) 
  : Primordial(OperandType::ast_op_t)
  , value_(v) {} 
Operand::Operand(OperandErrorCode v) 
  : Primordial(OperandType::err_t)
  , value_(v) {} 
Operand::Operand(OperandStatusCode v) 
  : Primordial(OperandType::status_t)
  , value_(v) {} //  just type
Operand::Operand(const string& v) 
  : Primordial(OperandType::str_t)
  , value_(v) {}
Operand::Operand(const char* v) 
  : Primordial(OperandType::str_t)
  , value_(string(v)) {}

Operand::Operand(const OperandVariant& v ) 
  : Primordial(visit(GetOperandType(), v)) {
  value_ = visit(GetOperandValue(), v); 
} 

Operand::Operand(entity_u_ptr &vptr) : Primordial(OperandType::uptr_t) { 
  value_= vptr->clone(); 
}
Operand::Operand(entity_u_ptr &&vptr) : Primordial(OperandType::uptr_t) { 
  value_= move(vptr);
}

Operand::Operand(const OperandType t, const OperandVariant& v) : Primordial(t){
   value_  = visit(GetOperandValue(), v);
}

//Operand::Operand(const Operand &v) : Primordial(v.Primordial), value_(visit(GetOperandValue(), v.value_)){}
//-----------------------------------------------------------------------
Operand Operand::clone_val() const {
  Operand nv;
  nv.type_= type_;
  nv.value_  = visit(GetOperandValue(), value_);
  return nv;

}
unique_ptr<Operand> Operand::clone() const {
  //return visit(GetOperandClone(), value_);
  return nullptr;
}
//-----------------------------------------------------------------------
OperandVariant Operand::_get_value() const {
  return visit(GetOperandValue(), value_);
};
OperandType Operand::_get_type() const { 
  return type_; //return( visit(GetOperandType(), value_));
};

Operand Operand::get_type() const {
  return type_; //return( visit(GetOperandType(), value_));
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
  return get<s_integer>(n.get_value()); 
}
s_float Operand::_get_float() const { 
  Number n = _get_number();
  return get<s_float>(n.get_value()); 
}
//-----------------------------------------------------------------------
/*
e_members_t& Operand::_get_members() {
  return get<e_members_t>(value_); 
};
e_children_t& Operand::_get_children() {
  return get<e_children_t>(value_); 
};
*/
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

void Operand::print() const {
  cout << *this;
}

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