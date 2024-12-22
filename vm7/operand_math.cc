#include "lang.hh"
#include "operand.hh"
//#include "entity.hh"
#include "ast.hh"

#define DEBUG_TRACE_FUNC
#include "scope_logger.hh"

//-----------------------------------------------------------------------
Operand Operand::operator+(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) { 
    cout << "error! " << *this << " + '" << other << "'\n";
    return Operand(OperandErrorCode::invalid_op_t);
  }

  switch(type_) {
  case OperandType::num_t:  {
    return  _get_number() + other._get_number();
    //cout << "operator: r" << r << "\n";
    //return r;
  }
  case OperandType::str_t: 
    return Operand(get<std::string>(value_) + get<std::string>(other.value_));
  case OperandType::uptr_t: 
    cout << "operator+ uptr_t\n";
    return Operand();
  default: 
    std::cout << "type int: " << static_cast<int>(type_) << "\n";
    throw std::runtime_error("Unsupported operation"); 
  }
}

  // Overload subtraction operator (similar approach)
Operand Operand::operator-(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) 
    throw std::runtime_error("Unsupported operation + for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return _get_number() - other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator*(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_)  {
    //cout << "this get_type: " << get_type() << "\n"; cout << "other get_type: " << other.get_type() << "\n";
    throw std::runtime_error("Unsupported operation * for unequal types"); 
  }

  switch(type_) {
  case OperandType::num_t: 
    return _get_number() * other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator/(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) 
    throw std::runtime_error("Unsupported operation / for unequal types"); 

  switch(type_) {
  case OperandType::num_t: 
    return _get_number() / other._get_number();
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__);
/*
  std::cout << "operand==(operand&)\n";
  cout << "*this: " << *this <<  " type: " << get_type() << "\n";
  cout << "other: " << other << " other type: " << other.get_type() << "\n";
  cout << "getv(): " << getv() << "\n";
  cout << "other.getv(): " << other.getv() << "\n";
*/

  auto other_type = other._get_type();

  if(type_ != other_type) {
    if(other_type ==OperandType::nil_t) return false;
    if(type_ == OperandType::nil_t) return false;
    return Operand(_get_value()) == Operand(other._get_value());
  }
  return visit(OperandCmpEql{}, value_, other.value_);
  
  /*
  switch(type_) {
  case OperandType::bool_t: 
    return get<bool>(value_) == get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) == get<Number>(other.value_);
  case OperandType::type_t: 
    return get<OperandType>(value_) == get<OperandType>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) == get<std::string>(other.value_);
  case OperandType::nil_t: {
    if(other.type_ == OperandType::nil_t) return true;
    return false;
  }
  case OperandType::list_t: {
    cout << "OperandType::list ==\n";
  }
  case OperandType::err_t: 
    return get<OperandErrorCode>(value_) == get<OperandErrorCode>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
  */

}
bool Operand::operator!=(const Operand& other) const {
  cout << "Operand::!=(Operand&)\n";
  return !(*this==other);
}

bool Operand::operator>=(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
    //throw std::runtime_error("Unsupported operation >= for unequal types"); 
    return false;
  }

  switch(type_) {
  case OperandType::num_t: 
    return get<Number>(value_) >= get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) >= get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<=(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
    //throw std::runtime_error("Unsupported operation <= for unequal types"); 
    return false;
  }
  switch(type_) {
  case OperandType::num_t: 
    return get<Number>(value_) <= get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) <= get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator<(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
    //throw std::runtime_error("Unsupported operation < for unequal types"); 
    return false;
  }
  switch(type_) {
  case OperandType::num_t: 
    return get<Number>(value_) < get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) < get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator>(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();
  if(type_ != other_type_) {
    //throw std::runtime_error("Unsupported operation > for unequal types"); 
    return false;
  }
  switch(type_) {
  case OperandType::num_t: 
    return get<Number>(value_) > get<Number>(other.value_);
  case OperandType::str_t: 
    return get<std::string>(value_) > get<std::string>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator!() const {
  auto type_ = _get_type();
  switch(type_) {
  case OperandType::bool_t: 
    return !get<bool>(value_);
  case OperandType::num_t: 
    return !get<Number>(value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator&&(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_) {
    throw std::runtime_error("Unsupported operation && for unequal types"); 
  }
  switch(type_) {
  case OperandType::bool_t: 
    return get<bool>(value_) && get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) && get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::operator||(const Operand& other) const {
  auto type_ = _get_type();
  auto other_type_ = other._get_type();

  if(type_ != other_type_)  {
    throw std::runtime_error("Unsupported operation || for unequal types"); 
  }

  switch(type_) {
  case OperandType::bool_t: 
    return get<bool>(value_) || get<bool>(other.value_);
  case OperandType::num_t: 
    return get<Number>(value_) || get<Number>(other.value_);
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

Operand Operand::opfunc(const AstExpr& v, AstOpCode op) {
  Operand other(v.clone_val());
  
  // if(type_ != other.type_) throw std::runtime_error("Unsupported operation > for unequal types"); 

  switch(op){
  case AstOpCode::plus:   return *this + other;
  case AstOpCode::minus:  return *this - other; 
  case AstOpCode::mul:    return *this * other; 
  case AstOpCode::div:    return *this / other;
  case AstOpCode::eql:    return *this == other;
  case AstOpCode::neql:   return *this != other;
  case AstOpCode::gt:     return *this > other;
  case AstOpCode::lt:     return *this < other;
  case AstOpCode::lteq:   return *this <= other;
  case AstOpCode::gteq:   return *this >= other;
  case AstOpCode::and_:   return *this && other;
  case AstOpCode::or_:    return *this && other;
  case AstOpCode::not_:   return *this && other;
  default:                return false;
  }
  return false;
}




bool Operand::operator==(const AstExpr &other) const { 
  //visit(OperandCmpEql(), value_, other_vptr->value_);
  cout << "Operand::==(astexpr_u_ptr)\n";
  return cmp_eql(other);
}
bool Operand::operator!=(const AstExpr &other) const { 
  cout << "Operand::!=(astexpr_u_ptr)\n";
  return !cmp_eql(other);
}


bool Operand::cmp_eql(const AstExpr&other) const { 
  MYLOGGER(trace_function , "Operand::cmp_eql(astexpr_u_ptr)", __func__);
  cout << "Operand::cmp_eql(astexpr_u_ptr)\n";
  return this->getv() == other.getv();
}


//--------------
template <typename T, typename U> bool OperandCmpEql::operator()(const T &a, const U &b) {
  MYLOGGER(trace_function , "OperandCmpEql::()(T, U)" ,__func__);
  //cout << "T == U?\n";
  return false; 
};
template <typename T> bool OperandCmpEql::operator()(const T &a, const T &b) { 
  MYLOGGER(trace_function , "OperandCmpEql::()(T, T)" ,__func__);
  //cout << "T == T?\n";
  return a==b; 
};
bool OperandCmpEql::operator()(const Nil a, const Nil b){ 
  MYLOGGER(trace_function , "OperandCmpEql::()(Nil, Nil)" ,__func__);
  //cout << "nil== nil\n"; 
  return true; 
}

/*
//bool OperandCmpEql::operator()(const Nil& a, const Nil& b){ cout << "nil== nil\n"; return true; }


template <typename T> bool OperandCmpEql::operator()(const astexpr_u_ptr& a, const T& b){ 
  cout << "uptr == Operand(T)?\n";
  //return visit(OperandCmpEql{}, a->_get_value() , b);
  //return visit(OperandCmpEql{}, a->_get_value() , b);
  return a->cmp_eql(Operand(b));
  //return false;
}
bool OperandCmpEql::operator()(const astexpr_u_ptr& a, const Number& b){
  cout << "uptr == Number?\n";
  return a->cmp_eql(Operand(b));
}

bool OperandCmpEql::operator()(const astexpr_u_ptr& a, const astexpr_u_ptr& b ){ 
  cout << "uptr == uptr?\n";
  return a->getv() == b->getv();
}
bool OperandCmpEql::operator()(const astexpr_s_ptr& a, const astexpr_s_ptr& b ){ 
  cout << "sptr == sptr?\n";
  return false;
}
bool OperandCmpEql::operator()(const astexpr_ptr& a, const astexpr_ptr& b){
  cout << "ptr == ptr?\n";
  return false;
}
*/