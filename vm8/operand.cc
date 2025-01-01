#include <iostream>
#include "operand.hh"

#define TO_STR(m) ((Operand::ToString *) this)->Operand::ToString::operator()(m);

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"


Nil nil;
const Operand nil_operand=Operand();
const list_t nil_list = {};
const map_t nil_map= {};
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
Operand::Operand(const list_t &l )            : type_(OperandType::list_t) { value_ = move(clone_list(l));}
Operand::Operand(const map_t &m )            : type_(OperandType::map_t) { value_ = move(clone_map(m));}

Operand::Operand(list_t &&vptr ) : type_(OperandType::list_t) { value_ = move(vptr); };


//Operand::Operand(const map_t &v ) : type_(OperandType::map_t) { value_ = make_unique<Operand>() ; };

//------------------------------------ Clone() s
operand_u_ptr Operand::clone() const { return visit(Clone{}, value_); }

//------------------------------------
list_t Operand::clone_list(const list_t&l) {
  MYLOGGER(trace_function, "Operand::clone_list(list_t&)", __func__, SLOG_FUNC_INFO);
  list_t new_list;
  for(auto &e : l) {
    new_list.push_back(  e.clone() );
  }
  return new_list;
}

list_t Operand::clone_list() {
  MYLOGGER(trace_function, "Operand::clone_list()", __func__, SLOG_FUNC_INFO);
  auto v = _get_variant();
  if(holds_alternative<list_t>(v)){
    return move(get<list_t>(v));
  }
  return {};
}

//------------------------------------

map_t Operand::clone_map(const map_t&map_) {
  MYLOGGER(trace_function, "Operand::clone_map(map_t&)", __func__, SLOG_FUNC_INFO);
  map_t new_map;
  for (auto const& [key, val] : map_) {
    new_map[key] = val.clone();
  }
  return new_map;
}

map_t Operand::clone_map() {
  MYLOGGER(trace_function, "Operand::clone_map()", __func__, SLOG_FUNC_INFO);
  auto v = _get_variant();
  if(holds_alternative<map_t>(v)){
    return move(get<map_t>(v));
  }
  return {};
}

//------------------------------------
bool Operand::add(const Operand&v) {
  MYLOGGER(trace_function, "Operand::add()", __func__, SLOG_FUNC_INFO);
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

bool Operand::add(const Operand &k, const Operand &v, bool overwrite) {
  MYLOGGER(trace_function, "Operand::add(Operand&, OPerand&, b)", __func__, SLOG_FUNC_INFO);
  auto &map_ = get_value_nc()._get_map_nc();

  if(_get_type() != OperandType::map_t) return false;

  auto k_str = k._to_str();
  if(overwrite == true) {
    map_[k_str] = v.clone();
    return true;
  } else {
    if(has_key(k_str)) {return false;}
    map_[k_str] = v.clone();
    return true;
  }
  return false;
}

//--------------------------------------
Operand& Operand::operator[] (const Operand& k) {
  MYLOGGER(trace_function, "Operand::[](Operand &k)", __func__, SLOG_FUNC_INFO );

  auto &rv = const_cast<Operand&>(as_const(*this)[k]); 

  if(rv.is_nil()) { auto &map_ =  _get_map_nc(); return map_[k._to_str()]; }
  return rv;

}
const Operand& Operand::operator[] (const Operand &k) const {
  MYLOGGER(trace_function, "Operand::[](Operand &k) const", __func__, 1);
  //cout << "Operand::[]";
  return  visit(GetK(), value_, k.value_);
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

Operand& Operand::get_value_nc() { 
  return const_cast<Operand&>(as_const(get_value())); 
}
const Operand& Operand::get_value() const { 
  return visit(Value{*this}, value_); 
}

//------------------------------------
list_t& Operand::_get_list_nc() { 
  return const_cast<list_t&>(as_const(_get_list())); 
}
const list_t& Operand::_get_list() const { 
  auto &v = get_value();
  if(holds_alternative<list_t>(v.value_)){
    auto &l = get<list_t>(v.value_);
    return l;
  }
  return nil_list;
}

//------------------------------------
map_t& Operand::_get_map_nc() { 
  return const_cast<map_t&>(as_const(_get_map())); 
}

const map_t& Operand::_get_map() const { 
  auto &v = get_value();
  if(holds_alternative<map_t>(v.value_)){
    auto &map_ = get<map_t>(v.value_);
    return map_;
  }
  return nil_map;
}

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
bool Operand::has_key(const Operand &ko)  const {
  auto k = ko._to_str();
  auto &map_ = _get_map();
  if(map_.size() == 0)  return false;
  if (map_.find(k) != map_.end())  {
    return true;
  }
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
operand_u_ptr Operand::Clone::operator()(const list_t& l) const { return make_unique<Operand>(move(clone_list(l))); } 
operand_u_ptr Operand::Clone::operator()(const map_t& m) const { return make_unique<Operand>(move(clone_map(m))); } 

//------------------------------------ Value
Operand::Value::Value(const Operand&v) : parent_v(v) {}
template <typename T>  
const Operand& Operand::Value::operator()(T &v) const  { return parent_v; } 
const Operand& Operand::Value::operator()(const Nil) const { return nil_operand; }
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
bool Operand::Add::operator()(const map_t& l) { 
  l_.push_back(move(Operand::clone_map(l))); 
  return true;
}
//------------------------------------ GetK
//------------------------- GetK - list_t
template <typename T, typename U> 
const Operand& Operand::GetK::operator()(const T& v, const U& k ) {return nil_operand; }
template <typename T> 
const Operand& Operand::GetK::operator()(const list_t& l, const T&k ) {return nil_operand; }
const Operand& Operand::GetK::operator()(const list_t& l, const Nil) {return nil_operand;}
const Operand& Operand::GetK::operator()(const list_t& l, const Number&n) {
  auto i = n.get_int();
  return l[i];
}
const Operand& Operand::GetK::operator()(const list_t& l, const operand_ptr& k)  {
  auto &kv = k->get_value();
  if(kv.is_nil()) return nil_operand;
  return l[kv._get_number().get_int()];
}
const Operand& Operand::GetK::operator()(const list_t& l, const operand_s_ptr& k) { return Operand::GetK::operator()(l, k.get()); }
const Operand& Operand::GetK::operator()(const list_t& l, const operand_u_ptr& k)  { return Operand::GetK::operator()(l, k.get()); }
const Operand& Operand::GetK::operator()(const list_t& l, const list_t& v)  {return nil_operand;} // maybe for with get_branch

//------------------------- GetK - map_t
template <typename T> 
const Operand& Operand::GetK::operator()(const map_t& m, const T&k ) {
  MYLOGGER(trace_function, "Operand::()(map_t, <T>&k)", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::()(map_t, <T>&k)\n";
  //auto ms = TO_STR(m);
  return nil_operand; 
}

const Operand& Operand::GetK::operator()(const map_t& m, const Nil) {
  MYLOGGER(trace_function, "Operand::()(map_t, Nil)", __func__, SLOG_FUNC_INFO);
  cout << "m. Nil\n";
  return nil_operand;
}

const Operand& Operand::GetK::operator()(const map_t& m, const string&s) {
  MYLOGGER(trace_function, "Operand::()(map_t, string&)", __func__, SLOG_FUNC_INFO);
  //cout << "m.at("<< s <<")\n";
  if (m.find(s) != m.end())  {
    return m.at(s);
  } 
  //cout << "key " << s << " not found \n";
  MYLOGGER_MSG(trace_function, s + string(", key not found!"), SLOG_FUNC_INFO);
  return nil_operand;
}

const Operand& Operand::GetK::operator()(const map_t& m, const operand_ptr& k)  {
  MYLOGGER(trace_function, "Operand::()(map_t, operand_ptr&)", __func__, SLOG_FUNC_INFO);
  auto ms = TO_STR(m);
  MYLOGGER_MSG(trace_function, string("map_t: ") + ms._to_str(), SLOG_FUNC_INFO);
  //cout << "Operand::()(map_t, operand_u_ptr&)\n";

  auto &kv = k->get_value();

  if(kv.is_nil()) return nil_operand;
  if(k->_get_type() == OperandType::str_t) return m.at(kv._to_str());
  return operator()(m, kv.value_);
}

const Operand& Operand::GetK::operator()(const map_t& m, const operand_s_ptr& k) { 
  MYLOGGER(trace_function, "Operand::()(map_t, operand_s_ptr&)", __func__, SLOG_FUNC_INFO);
  return Operand::GetK::operator()(m, k.get()); 
}
const Operand& Operand::GetK::operator()(const map_t& m, const operand_u_ptr& k)  { 
  MYLOGGER(trace_function, "Operand::()(map_t, operand_u_ptr&)", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::()(map_t, operand_u_ptr&)\n";
  return  Operand::GetK::operator()(m, k.get()); 
}
const Operand& Operand::GetK::operator()(const map_t& m, const map_t& v)  {
  cout << "m.m\n";
  return nil_operand;
} // maybe for with get_branch


//------------------------------------ Variant
template <typename T> 
operand_variant_t Operand::Variant::operator()(const T &v) const { return v; }
operand_variant_t Operand::Variant::operator()(const Nil v) const { return nil; }
operand_variant_t Operand::Variant::operator()(const operand_ptr& vptr) const { return vptr; }
operand_variant_t Operand::Variant::operator()(const operand_s_ptr& vptr) const { return vptr; }
operand_variant_t Operand::Variant::operator()(const operand_u_ptr& vptr) const { return vptr->clone(); }
// need to be clone 
operand_variant_t Operand::Variant::operator()(const list_t& l) const { return clone_list(l)  ; }
operand_variant_t Operand::Variant::operator()(const map_t& m) const { return clone_map(m); }
//------------------------------------ DeRef
template <typename T> 
operand_variant_t Operand::DeRef::operator()(const T& value) const { return value;}
operand_variant_t Operand::DeRef::operator()(const Nil) const { return nil; }
operand_variant_t Operand::DeRef::operator()(const operand_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const operand_s_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const operand_u_ptr& v) const  { if(v==nullptr) return nil; return  v->_deref(); }
operand_variant_t Operand::DeRef::operator()(const list_t& l) const { return clone_list(l); }
operand_variant_t Operand::DeRef::operator()(const map_t& m) const { return clone_map(m); }

//--------------------------------------------------------- 
ostream& operator<<(ostream& os, const Operand& v) {
  cout << v._to_str();
  return os;
}