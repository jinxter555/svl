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
Operand::Operand(const list_t &l )            : type_(OperandType::list_t) { value_ = move(clone_list(l));
}
Operand::Operand(list_t &&vptr ) : type_(OperandType::list_t) { value_ = move(vptr); };


//Operand::Operand(const map_t &v ) : type_(OperandType::map_t) { value_ = make_unique<Operand>() ; };

//------------------------------------
operand_u_ptr Operand::clone() const { return visit(Clone{}, value_); }

list_t Operand::clone_list(const list_t&l) {
  list_t new_list;
  for(auto &e : l) {
    new_list.push_back(  e.clone() );
  }
  return new_list;
}
list_t Operand::clone_list() {
  auto v = _get_variant();
  if(holds_alternative<list_t>(v)){
    return move(get<list_t>(v));
  }
  return {};
}
bool Operand::add(const Operand&v) {
  if(holds_alternative<list_t>(value_)){
    auto &l = get<list_t>(value_);
    return visit(Add{l}, v.value_);

  } else if (holds_alternative<Nil>(value_)){
    list_t l;
    bool result = visit(Add{l}, v.value_);
    value_ = move(l);
    return result;
  }

  return false;

}
//------------------------------------
//--------------------------------------
Operand& Operand::operator[] (const Operand& k) {
  return const_cast<Operand&>(as_const(*this)[k]); 
}
const Operand& Operand::operator[] (const Operand &k) const {
  if(holds_alternative<list_t>(value_)){
    auto &l = get<list_t>(value_);
    return visit(GetK{l}, k.value_);
  }
  return nil_operand;
}



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
Number Operand::_get_number() const { 
  if(holds_alternative<Number>(value_)) {
    return get<Number>(value_); 
  } else if(holds_alternative<string>(value_)) {
    auto strnum = get<string>(value_);
    if(strnum.find('.')!= string::npos) return Number(stod(strnum)); 
    else return Number(stol(strnum)); 
  }
  return get<Number>(_deref());

}

const Operand& Operand::get_value() const { return visit(Value{}, value_); }

operand_variant_t Operand::_get_variant() const {
  return visit(Variant(), value_);
//  return visit(Clone(), value_);
}
operand_variant_t Operand::_deref() const {
  return visit(DeRef{}, value_);
}

//------------------------------------
bool Operand::is_nil() const {
  if(type_ == OperandType::nil_t) return true; 
  return false; 
}

//------------------------------------
void Operand::print() const { cout << *this; }
//------------------------------------ Clone
template <typename T> 
operand_u_ptr Operand::Clone::operator()(const T& v) const { return make_unique<Operand>(v); }
operand_u_ptr Operand::Clone::operator()(const Nil v) const { return nullptr; }
operand_u_ptr Operand::Clone::operator()(const operand_ptr& v) const { return v->clone(); }
operand_u_ptr Operand::Clone::operator()(const operand_u_ptr& v) const {return v->clone(); } 
operand_u_ptr Operand::Clone::operator()(const operand_s_ptr& v) const { return v->clone(); } 
operand_u_ptr Operand::Clone::operator()(const list_t& l) const { 
  return make_unique<Operand>(move(clone_list(l)));
} 
//------------------------------------ Value
template <typename T> 
const Operand& Operand::Value::operator()(T &v) const  { return *(Operand*)this;}
const Operand& Operand::Value::operator()(const Nil) const {return nil_operand; }
const Operand& Operand::Value::operator()(operand_ptr& v) const  {return v->get_value(); }
const Operand& Operand::Value::operator()(operand_u_ptr& v) const {return v->get_value();}
const Operand& Operand::Value::operator()(operand_s_ptr& v) const {return v->get_value();}
//------------------------------------ Add
Operand::Add::Add(list_t &l) : l_(l) {}
template <typename T> 
bool Operand::Add::operator()(const T &v) { l_.push_back(v); return true; }
bool Operand::Add::operator()(const Nil v) { l_.push_back(nil); return true; }
bool Operand::Add::operator()(const operand_ptr& v) { l_.push_back(v); return true; }
bool Operand::Add::operator()(const operand_s_ptr& v) { l_.push_back(v); return true; }
bool Operand::Add::operator()(const operand_u_ptr& v) { l_.push_back(v->clone()); return true; }
bool Operand::Add::operator()(const list_t& l) { 
  l_.push_back(move(Operand::clone_list(l))); 
  return true;
}
//------------------------------------ GetK
Operand::GetK::GetK(const list_t &l) : l_(l){}
template <typename T> 
const Operand& Operand::GetK::operator()(const T& ) {return nil_operand; }
const Operand& Operand::GetK::operator()(const Nil) {return nil_operand;}
const Operand& Operand::GetK::operator()(const Number&n) {
  auto i = n.get_int();
  return l_[i];
}
const Operand& Operand::GetK::operator()(const operand_ptr& v)  {return nil_operand;}
const Operand& Operand::GetK::operator()(const operand_s_ptr& v) {return nil_operand;}
const Operand& Operand::GetK::operator()(const operand_u_ptr& v)  {return nil_operand;}
const Operand& Operand::GetK::operator()(const list_t& v)  {return nil_operand;} // maybe for with get_branch


//------------------------------------ Variant
template <typename T> 
operand_variant_t Operand::Variant::operator()(const T &v) const { return v; }
operand_variant_t Operand::Variant::operator()(const Nil v) const { return nil; }
operand_variant_t Operand::Variant::operator()(const operand_ptr& vptr) const { return vptr; }
operand_variant_t Operand::Variant::operator()(const operand_s_ptr& vptr) const { return vptr; }
operand_variant_t Operand::Variant::operator()(const operand_u_ptr& vptr) const { return vptr->clone(); }
// need to be clone 
operand_variant_t Operand::Variant::operator()(const list_t& l) const { return clone_list(l)  ; }
operand_variant_t Operand::Variant::operator()(const map_t& v) const { return nil; }
//------------------------------------ DeRef
template <typename T> 
operand_variant_t Operand::DeRef::operator()(const T& value) const { return value;}
operand_variant_t Operand::DeRef::operator()(const Nil) const { return nil; }
operand_variant_t Operand::DeRef::operator()(const operand_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const operand_s_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const operand_u_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const list_t& l) const { return clone_list(l); }

//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const Operand& v) {
  cout << v._to_str();
  return os;
}
