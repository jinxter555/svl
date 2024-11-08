#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include "operand.hh"
#include "operand_tostr.hh"


Nil nil;
Operand nil_operand=Operand();


const string Operand::nil_str=string("nil");
  
Operand::Operand() 
  : AstExpr(OperandType::nil_t)
  , value_(nil) {}
Operand::Operand(const Nil& n) 
  : AstExpr(OperandType::nil_t)
  , value_(nil) {}
Operand::Operand(bool v)
  : AstExpr(OperandType::bool_t)
  , value_(v) {}
Operand::Operand(s_integer v) 
  : AstExpr(OperandType::num_t)
  , value_(Number(v)) {}
Operand::Operand(s_float v) 
  : AstExpr(OperandType::num_t)
  , value_(Number(v)) {}
Operand::Operand(const Number& v) 
  : AstExpr(OperandType::num_t)
  , value_(v) {}
Operand::Operand(OperandType v) 
  : AstExpr(OperandType::type_t)
  , value_(v) {} //  meta program type of types
Operand::Operand(ControlFlow v) 
  : AstExpr(OperandType::control_t)
  , value_(v) {} //  meta program type of types
Operand::Operand(AstOpCode v) 
  : AstExpr(OperandType::ast_op_t)
  , value_(v) {} 
Operand::Operand(OperandErrorCode v) 
  : AstExpr(OperandType::err_t)
  , value_(v) {} 
Operand::Operand(OperandStatusCode v) 
  : AstExpr(OperandType::status_t)
  , value_(v) {} //  just type
Operand::Operand(const string& v) 
  : AstExpr(OperandType::str_t)
  , value_(v) {}
Operand::Operand(const char* v) 
  : AstExpr(OperandType::str_t)
  , value_(string(v)) {}

Operand::Operand(const OperandVariant& v ) 
  : AstExpr(visit(GetOperandType(), v)) {
  value_ = visit(GetOperandValue(), v); 
} 

Operand::Operand(astexpr_u_ptr &vptr) : AstExpr(OperandType::uptr_t) { 
  if(vptr==nullptr) {
    type_ = OperandType::nil_t;
    value_ = nil;
  } else
    value_= vptr->clone(); 
}
Operand::Operand(astexpr_u_ptr &&vptr) : AstExpr(OperandType::uptr_t) { 
  value_= move(vptr);
}

Operand::Operand(const OperandType t, const OperandVariant& v) : AstExpr(t){
  value_  = visit(GetOperandValue(), v);
}


//Operand::Operand(const Operand &v) : AstExpr(v.type_), value_(visit(GetOperandValue(), v.value_)){}
//Operand::Operand(const AstExpr &v) : AstExpr(v.type_) { value_ = visit(GetOperandValue(), v); }

//-----------------------------------------------------------------------
Operand Operand::clone_val() const {
  Operand nv;
  nv.type_= type_;
  nv.value_  = visit(GetOperandValue(), value_);
  return nv;
}

unique_ptr<AstExpr> Operand::clone() const {
  return visit(GetOperandClone(), value_);
}

astexpr_u_ptr Operand::evaluate(astexpr_u_ptr& ast_ctxt) {
  return clone();
}
//-----------------------------------------------------------------------
Operand& Operand::getv() {
  return *this;
}
//-----------------------------------------------------------------------
AstExpr *Operand::get_raw_ptr(const Operand &k) {
  string k_str; s_integer k_i;
   if (holds_alternative<string>(k.value_)) {
    k_str = k._get_str();
    return get_raw_ptr(k_str);
   }
   if (holds_alternative<Number>(k.value_)) {
    auto ptr = _get_astexpr_raw_ptr();
    k_i =  k._get_int();
    return ptr->get_raw_ptr(k_i);
   }
   return nullptr;
}

AstExpr *Operand::get_raw_ptr(const string &k) {
  auto ptr = _get_astexpr_raw_ptr();
  if(ptr==nullptr) return nullptr;
  return ptr->get_raw_ptr(k);
}

AstExpr* Operand::_get_astexpr_raw_ptr() {
  return visit(GetOperand_astexpr_ptr(), value_);
}

//-----------------------------------------------------------------------
OperandVariant Operand::_get_value() const {
  return visit(GetOperandValue(), value_);
};
OperandType Operand::_get_type() const { 
  return type_; 
};

Operand Operand::get_type() const {
  return type_; 
}
vector<string> Operand::_get_keys() const {
  auto node = visit(GetOperand_astexpr_ptr(), value_);
  if(node == nullptr) return {};
  return node->_get_keys(); 
}

s_integer Operand::size() const {return 0;}
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
string Operand::_get_str() const { 
  return  _to_str();
}
string Operand::_to_str() const { 
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
OperandVariant GetOperandValue::operator()(const astexpr_u_ptr& v) const { return v->clone(); }

//-----------------------------------------------------------------------
template <typename T>
operand_u_ptr GetOperandClone::operator()(T value) const { 
  return make_unique<Operand>(value); 
}
operand_u_ptr GetOperandClone::operator()(const astexpr_u_ptr& v) const { 
  return make_unique<Operand>(v->clone()); 
}
//-------------------------------
template <typename T>
AstExpr* GetOperand_astexpr_ptr::operator()(T value) const { return nullptr; }
AstExpr* GetOperand_astexpr_ptr::operator()(const astexpr_u_ptr& v) const  { return v.get(); }

//-------------------------------
//-------------------------------------------
bool Operand::add(const AstExpr &v) {
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(v);
}  
bool Operand::add(astexpr_u_ptr &&vvptr) {
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(move(vvptr));
} 

//-------------------------------------------
bool Operand::add(const Operand &k, const AstExpr& v, bool overwrite) {
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(k, v, overwrite);
}

bool Operand::add(const Operand &k, astexpr_u_ptr&& vvptr, bool overwrite) {
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(k, move(vptr), overwrite);
}
//-------------------------------------------
bool Operand::set(const Operand &k, const AstExpr& v) {
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->set(k, v);
}
bool Operand::set(const Operand &k, astexpr_u_ptr&& vvptr){
  auto &vptr = _get_astexpr_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->set(k, move(vvptr));
}
//-------------------------------------------

Operand& Operand::getv(const Operand &k)  {
  auto &ptr = _get_astexpr_u_ptr();
  if(ptr == nil_ast_ptr) nil_operand;
  return ptr->getv(k);
}
astexpr_u_ptr& Operand::get_u_ptr(const Operand &k) {
  auto &ptr = _get_astexpr_u_ptr();
  if(ptr==nil_ast_ptr) return nil_ast_ptr;
  return ptr->get_u_ptr(k);
}

astexpr_u_ptr& Operand::_get_astexpr_u_ptr() {
  return get_u_ptr();
}
astexpr_u_ptr& Operand::get_u_ptr() {
  if (holds_alternative<astexpr_u_ptr>(value_)) 
    return get<astexpr_u_ptr>(value_); 
  return nil_ast_ptr;
}
