#include <iostream>
#include <stdexcept>
#include "operand.hh"

//#include "operand_vars.hh"
//#define TO_STR(m) ((Operand::ToString *) this)->Operand::ToString::operator()(m);

#define SLOG_DEBUG_TRACE_FUNC
#include "scope_logger.hh"



extern const Nil nil={};
extern const Operand nil_operand=Operand();
extern const list_t nil_list = {};
extern const map_t nil_map= {};
extern const int i_var =123;

#include "operand_getk.hh"

ostream& operator<<(ostream& os, const Operand& v);

Operand::Operand()                  : type_(OperandType::nil_t),  value_(nil) {}
Operand::Operand(const Nil&n)       : type_(OperandType::nil_t), value_(nil) {}
Operand::Operand(const s_float v)   : type_(OperandType::num_t),  value_(v) {}
Operand::Operand(const s_integer v) : type_(OperandType::num_t), value_(v) {}
Operand::Operand(const Number& v)   : type_(OperandType::num_t), value_(v) {}
Operand::Operand(const char*v)      : type_(OperandType::str_t), value_(string(v)) {}
Operand::Operand(const string& v)   : type_(OperandType::str_t), value_(v) {}
Operand::Operand(const bool v)      : type_(OperandType::bool_t), value_(v) {}
Operand::Operand(const OperandType &v)        : type_(OperandType::type_t), value_(v){}
Operand::Operand(const AstOpCode& v)          : type_(OperandType::ast_op_t), value_(v) {}
Operand::Operand(const OperandErrorCode &v)   : type_(OperandType::err_t),    value_(v) {}
Operand::Operand(const OperandStatusCode &v)  : type_(OperandType::status_t), value_(v) {}
Operand::Operand(const ControlFlow &v )       : type_(OperandType::control_t), value_(v) {}
Operand::Operand(const operand_u_ptr&v )      : type_(OperandType::uptr_t), value_(move(v->clone())) {}
Operand::Operand(operand_u_ptr&&v )           : type_(OperandType::uptr_t), value_(move(v)) {}
Operand::Operand(const operand_s_ptr& v)      : type_(OperandType::sptr_t), value_(move(v->clone())) {}
Operand::Operand(const operand_ptr v)         : type_(OperandType::ptr_t),  value_(move(v->clone())) {}
Operand::Operand(const list_t &l )            : type_(OperandType::list_t) { value_ = move(clone_list(l));}
Operand::Operand(const map_t &m )            : type_(OperandType::map_t) { value_ = move(clone_map(m));}

Operand::Operand(list_t &&vptr ) : type_(OperandType::list_t) { value_ = move(vptr); }

//------------------------------------ vec 
Operand::Operand(const vec_num_t& l) {
  list_t new_list;
  for(auto e: l) new_list.push_back(e);
  value_ = move(new_list);
}
Operand::Operand(const vec_str_t& l) {
  list_t new_list;
  for(auto e: l) new_list.push_back(e);
  value_ = move(new_list);
}

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
  ToString tstr;
  auto s = tstr.ToString::operator()(map_)._to_str();
  MYLOGGER_MSG(trace_function,  string("cloning map_: ") + s,  SLOG_FUNC_INFO+1);

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
  MYLOGGER(trace_function, "Operand::add(Operand&, Operand&, bool)", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::Add(Operand&, Operand&, bool)\n";
  auto &map_ = _get_map_nc();

  //if(map_ == nil_map) return false;

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
bool Operand::addk(const Operand &k, const Operand &v, bool overwrite) {
  auto &m=_get_map_nc();
  visit(AddK(m, overwrite), k.value_, v.value_);
  return false;
}

//--------------------------------------
Operand& Operand::operator[] (const Operand& k) {
  MYLOGGER(trace_function, "Operand::[](Operand &k)", __func__, SLOG_FUNC_INFO );

  auto &rv = const_cast<Operand&>(as_const(*this)[k]); 

  if(rv.is_nil()) { 
    auto &map_ =_get_map_nc();
    return map_[k._to_str()];
  }
  return rv;

}
const Operand& Operand::operator[] (const Operand &k) const {
  MYLOGGER(trace_function, "Operand::[](Operand &k) const", __func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function,  string("k: ") + k._to_str() , SLOG_FUNC_INFO+1);

/*
  cout << "Operand::[]";
  cout << "k:" <<  k << "\n";
  cout << "k.type:" <<  k.get_type() << "\n";
*/
  if(k._get_type()== OperandType::list_t) {}
  auto &rv = get_value(); 
  auto &rk = k.get_value();
  //return  visit(GetK(), value_, k.value_);
  return  visit(GetK(), value_, rk.value_);
  //return  visit(GetK(), rv.value_, k.value_);
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

//s_integer Operand::_get_int() const { return _get_number().get_int(); }

Operand& Operand::get_value_nc() { 
  return const_cast<Operand&>(as_const(get_value())); 
}
const Operand& Operand::get_value() const { 
  MYLOGGER(trace_function, "Operand::get_value()", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::get_value()\n";
  //cout << "get_type: " << get_type() << "\n";
  //return visit(Value{*this}, value_); 
  return *_vrptr();
}

//------------------------------------
list_t& Operand::_get_list_nc() { 
  return const_cast<list_t&>(as_const(_get_list())); 
}
const list_t& Operand::_get_list() const { 
  return visit(List(), value_);
  /*
  auto dv = _deref();
  if(holds_alternative<list_t>(dv)){
    auto &l = get<list_t>(dv);
    return l;
  }
  return nil_list;
  */
}

s_integer Operand::_get_list_size() const { return _get_list().size(); }
s_integer Operand::_get_map_size() const { return _get_map().size(); }

//------------------------------------
map_t& Operand::_get_map_nc() { 
  MYLOGGER(trace_function, "Operand::_get_map_nc()", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::_get_map_nc()\n";
  return const_cast<map_t&>(as_const(_get_map())); 
}

const map_t& Operand::_get_map() const { 
  MYLOGGER(trace_function, "Operand::_get_map()", __func__, SLOG_FUNC_INFO);
  //cout << "Operand::_get_map()\n";
  return visit(Map(), value_);

}

operand_variant_t Operand::_get_variant() const {
  MYLOGGER(trace_function, "Operand::_get_variant()", __func__, SLOG_FUNC_INFO);
  return visit(Variant(), value_);
}
operand_variant_t Operand::_deref() const {
  MYLOGGER(trace_function, "Operand::_deref()", __func__, SLOG_FUNC_INFO);
  return visit(DeRef{}, value_);
}
operand_ptr Operand::_vrptr() const {
  MYLOGGER(trace_function, "Operand::_vrptr()", __func__, SLOG_FUNC_INFO);
  switch(_get_type()) {
  case OperandType::ptr_t:
  case OperandType::uptr_t:
  case OperandType::sptr_t:
    //return visit(Vrptr(this), value_);
    return visit(Vrptr(), value_);
  }
  return (Operand*)this;
}

operand_ptr Operand::get_raw_ptr() const {
  auto rptr = visit(Rptr(), value_);
  if(rptr==nullptr)
    return (operand_ptr)this;
  return rptr;
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

//------------------------------------ Vrptr ptr value
template <typename T> 
operand_ptr Operand::Vrptr::operator()(const T& value) const { return nullptr; }
operand_ptr Operand::Vrptr::operator()(const Nil) const { return nullptr; }
operand_ptr Operand::Vrptr::operator()(const operand_ptr& vptr) const  { return vptr->_vrptr(); }
operand_ptr Operand::Vrptr::operator()(const operand_s_ptr& vptr) const { return vptr->_vrptr();}
operand_ptr Operand::Vrptr::operator()(const operand_u_ptr& vptr) const  { return vptr->_vrptr(); }

//------------------------------------ Rptr raw ptr 
template <typename T> 
const operand_ptr Operand::Rptr::operator()(const T& v) const { return nullptr; }
const operand_ptr Operand::Rptr::operator()(const Nil v) const { return nullptr; }
const operand_ptr Operand::Rptr::operator()(const operand_ptr& vptr) const { return vptr; }
const operand_ptr Operand::Rptr::operator()(const operand_s_ptr& vptr) const { return vptr.get(); }
const operand_ptr Operand::Rptr::operator()(const operand_u_ptr& vptr) const { return vptr.get(); }

//------------------------------------ Map
const map_t& Operand::Map::operator()(const map_t &m) const  { 
  MYLOGGER(trace_function, "Operand::Map::()(map_t)", __func__, SLOG_FUNC_INFO+2);
  return m;} 

template <typename T>  
const map_t& Operand::Map::operator()(const T &v) const  { 
  MYLOGGER(trace_function, "Operand::Map::()(<T>)", __func__, SLOG_FUNC_INFO+2);
  return nil_map; } 

const map_t& Operand::Map::operator()(const Nil) const { 
  MYLOGGER(trace_function, "Operand::Map::()(Nil)", __func__, SLOG_FUNC_INFO+2);
  return nil_map;}

const map_t& Operand::Map::operator()(const operand_ptr& v) const  {
  MYLOGGER(trace_function, "Operand::Map::()(operand_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_map();}

const map_t& Operand::Map::operator()(const operand_u_ptr& v) const {
  MYLOGGER(trace_function, "Operand::Map::()(operand_u_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_map();}

const map_t& Operand::Map::operator()(const operand_s_ptr& v) const {
  MYLOGGER(trace_function, "Operand::Map::()(operand_s_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_map(); }

//------------------------------------ List
const list_t& Operand::List::operator()(const list_t &m) const  { 
  MYLOGGER(trace_function, "Operand::List::()(list_t)", __func__, SLOG_FUNC_INFO+2);
  return m;} 

template <typename T>  
const list_t& Operand::List::operator()(const T &v) const  { 
  MYLOGGER(trace_function, "Operand::List::()(<T>)", __func__, SLOG_FUNC_INFO+2);
  return nil_list; } 

const list_t& Operand::List::operator()(const Nil) const { 
  MYLOGGER(trace_function, "Operand::List::()(Nil)", __func__, SLOG_FUNC_INFO+2);
  return nil_list;}

const list_t& Operand::List::operator()(const operand_ptr& v) const  {
  MYLOGGER(trace_function, "Operand::List::()(operand_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_list();}

const list_t& Operand::List::operator()(const operand_u_ptr& v) const {
  MYLOGGER(trace_function, "Operand::List::()(operand_u_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_list();}

const list_t& Operand::List::operator()(const operand_s_ptr& v) const {
  MYLOGGER(trace_function, "Operand::List::()(operand_s_ptr&)", __func__, SLOG_FUNC_INFO+2);
  return v->_get_list(); }



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
  MYLOGGER(trace_function, "OS<<(Operand&)", __func__, SLOG_FUNC_INFO+20);
  cout << v._to_str();
  return os;
}


//------------------------------------ AddK
Operand::AddK::AddK(map_t &m, bool ow) : map_(m), overwrite(ow) {}

template <typename T, typename U> 
bool Operand::AddK::operator()(const T&k, const U& v) {
  return false;
}

template <typename T> 
bool Operand::AddK::operator()(const list_t& k, const T& v) { 
  cout <<  "Operand::AddK::operator()(list_t&, <T&>v, bool)\n";
  s_integer i=0,s = k.size(); 
  operand_ptr current_map_ptr;

  if(s <=0) {
    cerr << "multi-dimensional map lookup error index " << k << " out of bound!";
    return false;
  }
  auto &first_i  = k[0];

  try {
    auto &first_v = map_.at(first_i._to_str());
    current_map_ptr = first_v.get_raw_ptr();
  }catch(const out_of_range &e) {
    if(!overwrite) return false;
    map_t new_map={};
    map_.insert({first_i._to_str(),  move(new_map)});
    current_map_ptr = map_.at(first_i._to_str()).get_raw_ptr();
  }

  for(s_integer i=1; i<s; i++) {
    auto &index = k[i];
    if(current_map_ptr->has_key(index)) {
      if(!overwrite) return false;
      current_map_ptr = (*current_map_ptr)[index].get_raw_ptr();
    } else {
      map_t new_map={};
      current_map_ptr->add(index,  move(new_map), overwrite);
      current_map_ptr = (*current_map_ptr)[index].get_raw_ptr();
    }
  }
  //*current_map_ptr = v.clone();
  *current_map_ptr = v;
  return true;

}
template <typename T> 
bool Operand::AddK::operator()(const string& k_str, const T& v) { 
  if(overwrite == true) {
    map_[k_str] = v;
    return true;
  } else {
    if(!map_[k_str].is_nil()) {return false;}
    map_[k_str] = v;
    return true;
  }
  return false;
}
bool Operand::AddK::operator()(const Nil, const Nil) { return false; }
bool Operand::AddK::has_key(const Operand&k) const {
  return has_key(k._to_str());
}
bool Operand::AddK::has_key(const string&k) const {
  if(map_.size() == 0)  return false;
  if (map_.find(k) != map_.end())  {
    return true;
  }
  return false;
}