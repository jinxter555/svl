#include "lang.hh"
#include "operand.hh"
#include "operand_vars.hh"

#define SLOG_DEBUG_TRACE_FUNC
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
    cout << "operator + uptr_t\n";
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
  case OperandType::num_t:  {
    Number other_num = other._get_number();
    if(other_num==0l) return nil;
    return _get_number() / other_num;
  }
  default: 
    throw std::runtime_error("Unsupported operation"); 
  }
}

bool Operand::operator==(const Operand& other) const {
  MYLOGGER(trace_function , "Operand::==(operand&)" ,__func__, SLOG_FUNC_INFO);
  MYLOGGER_MSG(trace_function, string("this.type: ")+ get_type()._to_str()  + string(" -vs- other.type: ") + other.get_type()._to_str(), SLOG_FUNC_INFO);
  /*
  cout << "Operand::==(const Operand&)\n";
  cout << "this: " << to_str()<<  ", other: " << other << "\n";
  cout << "type: " << get_type() << "other_type: " << other.get_type() << "\n";
  */

  bool result  = visit(CmpEql{}, value_, other.value_);
  if(result==true) return result;

  // get through the nested pointers using get_value and compare
  auto &a_rv = get_value(); auto &b_rv = other.get_value();
  result = visit(CmpEql{}, a_rv.value_,  b_rv.value_);
  return result;

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

Operand Operand::opfunc(const Operand& v, AstOpCode op) {
  cout << "Operand::opfunc()\n";
  cout << "Opcode: " << Operand(op)<< "\n";
  Operand other(v.clone());
  
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

//--------------------------------------------------------- CmpEql
bool Operand::CmpEql::operator()(const Nil a, const Nil b) const { return true; }

template <typename T> 
bool Operand::CmpEql::operator()(const T &a, const T &b) const { 
  //------------------------
  MYLOGGER(trace_function , "OperandCmpEql::()(T, T)" ,__func__, SLOG_FUNC_INFO);
  auto a_ov = TO_STR(a); auto b_ov = TO_STR(b);
  MYLOGGER_MSG(trace_function , string("a: ") + a_ov._to_str()+ string("==? b: ") + b_ov._to_str(), SLOG_FUNC_INFO+9);
  //------------------------
  //cout << "T == T?\n"; cout << "a: " << a << ", b: " << b << "\n";
  //------------------------
  return a==b;
}

bool Operand::CmpEql::operator()(const list_t&a, const list_t &b) const {
  MYLOGGER(trace_function , "OperandCmpEql::()(const list_t&, const list&)" ,__func__, SLOG_FUNC_INFO);
  auto a_ov = TO_STR(a); auto b_ov = TO_STR(b);
  MYLOGGER_MSG(trace_function , string("a: ") + a_ov._to_str()+ string(", b: ") + b_ov._to_str(), SLOG_FUNC_INFO+9);
  //cout << "list_t == list_t ?\n";

  s_integer s=a.size();

  if(s!=b.size()) return false;
  for(s_integer i=0; i<s; i++) {
    cout << "a[" << i << "]: " << a[i] << ", b[" << i << "]: " << b[i] << "\n";
    if(a[i].get_value() == b[i].get_value()) continue;
    return false;
  }
  return true;
}

template <typename T, typename U> 
bool Operand::CmpEql::operator()(const T &a, const U &b) const { 
  MYLOGGER(trace_function , "OperandCmpEql::()(T, U)" , __func__, SLOG_FUNC_INFO);
  //cout << "T == U?\n";
  return false; 
}