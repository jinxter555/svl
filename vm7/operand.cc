#include <variant>
#include <string>
#include <stdexcept>
#include <iostream>
#include <utility>
#include "operand.hh"
#include "operand_tostr.hh"
#include "ast_map.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"


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
  value_ = visit(OperandValue(), v); 
} 

Operand::Operand(astexpr_ptr ptr) 
: AstExpr(OperandType::ptr_t)
, value_(ptr) {
  cout << "initialize Operand(AstExpr*): get_type(): " << get_type() << "\n";;
  cout << "*ptr: " << *ptr << "\n";;
  cout << "getv(): " << getv() << "\n";;
}



Operand::Operand(svlm_ast_ptr ptr) 
: AstExpr(OperandType::svlm_ast_ptr_t)
, value_(ptr) {}


Operand::Operand(astexpr_s_ptr& vptr) : value_(vptr), AstExpr(OperandType::sptr_t) { 
}

Operand::Operand(astexpr_u_ptr &vptr) : AstExpr(OperandType::uptr_t) { 
  if(vptr==nullptr) {
    type_ = OperandType::nil_t;
    value_ = nil;
  } else {
    type_ = vptr->type_;
    value_= vptr->clone(); 
  }
}

Operand::Operand(astexpr_u_ptr &&vptr) 
//: AstExpr(OperandType::uptr_t) 
{ 
  if(vptr==nullptr) {
    type_ = OperandType::nil_t;
    value_ = nil;
  } else {
    //type_ = vptr->type_;
    //cout << "memory clone addr!" << *vptr << "\n";
    type_ = OperandType::uptr_t;
    value_= move(vptr);
  }
}

Operand::Operand(const OperandType t, const OperandVariant& v) : AstExpr(t){
  value_  = visit(OperandValue(), v);
}


//Operand::Operand(const Operand &v) : AstExpr(v.type_), value_(visit(OperandValue(), v.value_)){}
//Operand::Operand(const AstExpr &v) : AstExpr(v.type_) { value_ = visit(OperandValue(), v); }

//-----------------------------------------------------------------------
Operand Operand::clone_val() const {
  /*
  cout << "Operand::clone_val()\n";
  Operand nv;
  nv.type_= type_;
  nv.value_  = visit(OperandValue(), value_);
  return nv;
  */
  MYLOGGER(trace_function
  , "Operand::clone_val()"
  ,__func__);
  return visit(OperandValue(), value_);
}

unique_ptr<AstExpr> Operand::clone() const {
  return visit(OperandClone(), value_);
}


astexpr_u_ptr Operand::evaluate(astexpr_u_ptr& ctxt) {
  /*
  auto &ptr = get_u_ptr();
  if(ptr==nullptr) return clone();
  return ptr->evaluate(ctxt);
  //return getv().clone();
  */
  return visit(OperandEvaluate(ctxt), value_);

}
//--------------------------------------
//--------------------------------------
Operand& Operand::operator[] (const Operand& k) {
  return const_cast<Operand&>(as_const(*this)[k]); 
}
const Operand& Operand::operator[] (const Operand &k) const {
  //cout <<  "Operand::[" << k << "] const\n";
  auto &ptr = get_u_ptr();
  //if(ptr==nullptr) return nil_operand;
  if(ptr==nullptr) {
    cout << "ptr is null!\n";
    return nil_operand;
  }
  return (*ptr)[k];
}

//-----------------------------------------------------------------------
AstExpr *Operand::get_raw_ptr() const {
  return get_u_ptr().get();
}
AstExpr *Operand::get_raw_ptr(const Operand &k) const {
  string k_str; s_integer k_i;
   if (holds_alternative<string>(k.value_)) {
    k_str = k._get_str();
    return get_raw_ptr(k_str);
   }
   if (holds_alternative<Number>(k.value_)) {
    auto &ptr = get_u_ptr();
    k_i =  k._get_int();
    return get_raw_ptr(k_i);
   }
   return nullptr;
}

AstExpr *Operand::get_raw_ptr(s_integer i) const {
  auto ptr = get_u_ptr().get();
  if(ptr==nullptr) return nullptr;
  return ptr->get_raw_ptr(i);
}
AstExpr *Operand::get_raw_ptr(const string &k) const {
  auto ptr = get_u_ptr().get();
  if(ptr==nullptr) return nullptr;
  return ptr->get_raw_ptr(k);
}

svlm_ast_ptr Operand::get_svlm_ptr() {
   if (holds_alternative<svlm_ast_ptr>(value_)) {
    return get<svlm_ast_ptr>(value_);
   }
   return nullptr;
}

//-----------------------------------------------------------------------
OperandVariant Operand::_get_value() const {
  return visit(OperandValue(), value_);
};
OperandType Operand::_get_type() const { 
  //cout << "i am in _get_type(): " << Operand(type_) << "\n";
  //cout << "i am in _get_type() int: " << int(type_) << "\n";
  return type_; 
};

Operand Operand::get_type() const {
  return _get_type(); 
}
Operand Operand::get_opcode() const {
  return _get_opcode();
}
AstOpCode Operand::_get_opcode() const {
  //cout << "get_opcode, type: " << get_type() << "\n";
  return get<AstOpCode>(value_);
}
vector<string> Operand::_get_keys() const {
  auto &node = visit(OperandUPtr(), value_);
  if(node.get() == nullptr) return {};
  if(node==nil_ast_ptr) return {};
  return node->_get_keys(); 
}

s_integer Operand::size() const {
  auto &ptr = get_u_ptr();
  if(ptr==nil_ast_ptr) return 0;
  return ptr->size();
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
// needs rewrite to use visitor for speed
Number Operand::_get_number() const { 
  if(holds_alternative<astexpr_u_ptr>(value_)) {
    auto &ptr = get<astexpr_u_ptr>(value_); 
    auto rptr =(Operand*) ptr.get();
    return rptr->_get_number();
  } else if(holds_alternative<Number>(value_)) {
    return get<Number>(value_); 
  } else if(holds_alternative<string>(value_)) {
    auto strnum = get<string>(value_);
    if(strnum.find('.')!= string::npos) return Number(stod(strnum)); 
    else return Number(stol(strnum)); 
  }
  return 0l;
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


//-------------------------------------------
bool Operand::add(const AstExpr &v) {
  /*
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(v);
  */
 return visit(OperandAdd(v), value_);
}  
bool Operand::add(astexpr_u_ptr &&vvptr) {
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(move(vvptr));
} 

//-------------------------------------------
bool Operand::add(const Operand &k, const AstExpr& v, bool overwrite) {
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  return vptr->add(k, v, overwrite);
}

bool Operand::add(const Operand &k, astexpr_u_ptr&& vvptr, bool overwrite) {
  auto &vptr = get_u_ptr();
  if(vptr==nullptr) return false;
  if(vvptr==nullptr) return false;
  return vptr->add(k, move(vvptr), overwrite);
}
bool Operand::add_branch(const vector<string> &keys, const Operand& operand, bool overwrite)  {
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  auto ptr =(AstMap*) vptr.get();
  return ptr->add_branch(keys, operand, overwrite);
}
bool Operand::add_branch(const vector<string> &keys, astexpr_u_ptr&& vvptr , bool overwrite) {
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return false;
  auto ptr =(AstMap*) vptr.get();
  return ptr->add_branch(keys, move(vvptr), overwrite);
}
Operand& Operand::get_branch(const vector<string> &keys) {
  auto &vptr = get_u_ptr();
  if(vptr==nil_ast_ptr) return nil_operand;
  auto ptr =(AstMap*) vptr.get();
  return ptr->get_branch(keys);
}
//-------------------------------------------
bool Operand::set(const Operand &k, const AstExpr& vptr) {
  //cout << "in operand::set &v!\n";
  return visit(OperandSet(k, vptr.clone()), value_);
}

bool Operand::set(const Operand &k, astexpr_u_ptr&& vvptr){
  return visit(OperandSet(k, move(vvptr)), value_);
}
//-----------------------------------------------------------------------
Operand& Operand::getv() {
  //cout << "Operand::getv(): type " << get_type() << "\n";
  return visit(OperandGetv(*this), value_);
}

//-------------------------------------------
Operand& Operand::getv(const Operand &k)  {
  //cout <<  "Operand::getv(" << k << ")\n";
  return visit(OperandGetv_k(k), value_);
}

astexpr_u_ptr& Operand::get_u_ptr_nc(const Operand&k) { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr(k))); 
}
const astexpr_u_ptr& Operand::get_u_ptr(const Operand &k) const {
  //auto &ptr = _get_astexpr_u_ptr();
  auto &ptr = get_u_ptr();
  if(ptr==nil_ast_ptr) return nil_ast_ptr;
  return ptr->get_u_ptr(k);
}

const astexpr_u_ptr& Operand::get_u_ptr() const {
 return visit(OperandUPtr(), value_);
}

astexpr_u_ptr& Operand::get_u_ptr_nc() { 
  return const_cast<astexpr_u_ptr&>(as_const(this->get_u_ptr())); 
}

//-------------------
astexpr_s_ptr Operand::get_s_ptr() {
  return visit(OperandSPtr(), value_);
}
astexpr_u_ptr Operand::clone_usu() {
  return visit(OperandUsu(), value_);
  //return nullptr;
}

//-----------------------------------------------------------------------
Operand& Operand::front() {
  if(type_==OperandType::uptr_t) {
    auto &ptr = get_u_ptr();
    if(ptr==nil_ast_ptr) return nil_operand;
    return ptr->front();
  } else
    return nil_operand;
}
Operand& Operand::back() {
  if(type_==OperandType::uptr_t) {
    auto &ptr = get_u_ptr();
    if(ptr==nil_ast_ptr) return nil_operand;
    return ptr->back();
  } else
    return nil_operand;
}


//-----------------------------------------------------------------------
template <typename T>
OperandVariant OperandValue::operator()(T v) const { return v; }
OperandVariant OperandValue::operator()(const astexpr_u_ptr& vptr) const { 
  if(vptr==nullptr) return nil;
  return vptr->clone(); 
}
OperandVariant OperandValue::operator()(const astexpr_s_ptr& vptr) const { 
  if(vptr==nullptr) return nil;
  return vptr;
}
//-----------------------------------------------------------------------
template <typename T>
AstOpCode GetOperandAstOpCode::operator()(T vptr) const { return AstOpCode::noop; }
AstOpCode GetOperandAstOpCode::operator()(const AstOpCode& vptr) const { return vptr; }

//------------------------------------------ Operand Clone
template <typename T>
operand_u_ptr OperandClone::operator()(T v) const { return make_unique<Operand>(v); }
operand_u_ptr OperandClone::operator()(const astexpr_u_ptr& vptr) const { return make_unique<Operand>(vptr->clone()); }
operand_u_ptr OperandClone::operator()(const astexpr_s_ptr& vptr) const { return make_unique<Operand>(vptr); }

//------------------------------------------ Operand Evaluate
template <typename T> 
astexpr_u_ptr OperandEvaluate::operator()(T v) const { return make_unique<Operand>(v); }
astexpr_u_ptr OperandEvaluate::operator()(astexpr_ptr vptr) { return vptr->evaluate(ctxt); }
astexpr_u_ptr OperandEvaluate::operator()(astexpr_s_ptr& vptr) { return vptr->evaluate(ctxt); }
astexpr_u_ptr OperandEvaluate::operator()(astexpr_u_ptr& vptr) { return vptr->evaluate(ctxt); }
OperandEvaluate::OperandEvaluate(astexpr_u_ptr&c) : ctxt(c) {}


//------------------------------------------ Operand Getv
template <typename T> 
Operand& OperandGetv::operator()(T &v) { return value_; }
Operand& OperandGetv::operator()(astexpr_ptr& vptr) { return vptr->getv(); }
Operand& OperandGetv::operator()(astexpr_u_ptr& vptr) { return vptr->getv(); }
Operand& OperandGetv::operator()(astexpr_s_ptr& vptr) { return vptr->getv(); }
OperandGetv::OperandGetv(Operand& v) : value_(v) { }

//------------------------------------------ Operand Shared Ptr
template <typename T> 
astexpr_s_ptr OperandSPtr::operator()(T& v) { return nullptr; }
astexpr_s_ptr OperandSPtr::operator()(astexpr_s_ptr& v) { return v; }
astexpr_s_ptr OperandSPtr::operator()(astexpr_u_ptr& v) { return v->get_s_ptr(); }
astexpr_s_ptr OperandSPtr::operator()(astexpr_ptr& v) { return v->get_s_ptr(); }

//------------------------------------------ Operand Unique Ptr
template <typename T> 
const astexpr_u_ptr& OperandUPtr::operator()(const T& v) const { return nil_ast_ptr; }
const astexpr_u_ptr& OperandUPtr::operator()(const astexpr_u_ptr& v) const { return v; }
const astexpr_u_ptr& OperandUPtr::operator()(const astexpr_s_ptr& v) const{ return v->get_u_ptr(); }
const astexpr_u_ptr& OperandUPtr::operator()(const astexpr_ptr& v) const{ return v->get_u_ptr(); }


//------------------------------------------ Operand List Add
template <typename T> 
bool OperandAdd::operator()(T& v) { return false; }
bool OperandAdd::operator()(astexpr_ptr& v) { return v->add(value_);}
bool OperandAdd::operator()(astexpr_s_ptr& v) { return v->add(value_);}
bool OperandAdd::operator()(astexpr_u_ptr& v) { return v->add(value_); }
OperandAdd::OperandAdd(const AstExpr&v) : value_(v) {}

//------------------------------------------ Operand Map Add
template <typename T> 
bool OperandAddK::operator()(T& v) { return false; }
bool OperandAddK::operator()(astexpr_ptr& v) { return v->add(key_, value_, overwrite);}
bool OperandAddK::operator()(astexpr_s_ptr& v) { return v->add(key_, value_, overwrite);}
bool OperandAddK::operator()(astexpr_u_ptr& v) { return v->add(key_, value_); }
OperandAddK::OperandAddK(const Operand &k, const AstExpr&v, bool ovw) : key_(k), value_(v), overwrite(ovw) {}

//------------------------------------------ Operand Usu unique shared unique
template <typename T> 
operand_u_ptr OperandUsu::operator()(T v) {
  //cout << "OperandUsu:: <T> v!\n";
  return
  make_unique<Operand>(
    make_shared<Operand>(
      make_unique<Operand>(v)
    )
  );
}
operand_u_ptr OperandUsu::operator()(const astexpr_u_ptr& vptr) {
  //cout << "OperandUsu:: astexpr_u_ptr!\n";
  //auto &v = vptr->getv();
  auto s_vptr = vptr->get_s_ptr();

  if(s_vptr != nullptr) {
    return make_unique<Operand>(s_vptr);
  } else {
    return make_unique<Operand>(
      make_shared<Operand>(
        make_unique<Operand>(vptr->clone())
      )
    );
  }
}
operand_u_ptr OperandUsu::operator()(const astexpr_s_ptr& vptr) {
  //cout << "OperandUsu:: astexpr_s_ptr!\n";
  return make_unique<Operand>(vptr);
}
//------------------------------------------ Operand Map set
template <typename T> 
bool OperandSet::operator()(T& v) { return false; }
bool OperandSet::operator()(astexpr_ptr& v) { 
  cout << "in set ptr!\n";
  return v->set(key_, move(vptr));
}
bool OperandSet::operator()(astexpr_s_ptr& v) { 
  cout << "in set s_ptr!\n";
  return v->set(key_, move(vptr));
}
bool OperandSet::operator()(astexpr_u_ptr& v) { 
  cout << "in set u_ptr!\n";
  return v->set(key_, move(vptr)); 
}
OperandSet::OperandSet(const Operand &k, astexpr_u_ptr v) :  key_(k) , vptr(move(v)){ }

//------------------------------------------ Ast Get
template <typename T> 
Operand& OperandGetv_k::operator()(T& v) { return nil_operand; }
Operand& OperandGetv_k::operator()(astexpr_ptr& v) { return v->getv(key_); }
Operand& OperandGetv_k::operator()(astexpr_s_ptr& v) { return v->getv(key_); }
Operand& OperandGetv_k::operator()(astexpr_u_ptr& v) { return v->getv(key_); }
OperandGetv_k::OperandGetv_k(const Operand &k) : key_(k) {}

//------------------------------------------ Operand opfunc
astexpr_u_ptr Operand::opfunc(astexpr_u_ptr other, AstOpCode op) {
  return make_unique<Operand>(opfunc(other->getv(), op));
}